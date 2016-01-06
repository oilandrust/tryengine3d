#include "Transform.h"
#include "includeGL.h"
#include "GameObject.h"

const RTTI Transform::TYPE("Transform", &Object::TYPE);

Transform::Transform():	
gameObject(0), 
parent(0), 
position(0),
worldPosition(0),
scaling(1), 
worldScaling(1),
eulerAngles(0),
worldEulerAngles(0)
{
	transformMatrix = identity_Mat4x4f();
	worldTransformMatrix = identity_Mat4x4f();
	rotationMatrix = identity_Mat3x3f();
	worldRotationMatrix = identity_Mat3x3f();
}

Transform::Transform(const Transform& other):
gameObject(0), 
parent(0), 
position(0),
worldPosition(other.worldPosition),
scaling(other.scaling), 
worldScaling(other.worldScaling),
eulerAngles(other.eulerAngles),
worldEulerAngles(other.worldEulerAngles),
transformMatrix(other.transformMatrix),
worldTransformMatrix(other.worldTransformMatrix),
rotationMatrix(other.rotationMatrix),
worldRotationMatrix(other.worldRotationMatrix)
{
}

Transform::~Transform(){
	for(size_t i = 0; i < this->children.size(); i++){
		if(this->children[i])
			delete this->children[i]->getGameObject();
	}
}

Transform::Transform(Vec3f const& pos):gameObject(NULL), parent(NULL), position(pos), scaling(1,1,1), eulerAngles(0,0,0){
	transformMatrix = identity_Mat4x4f();
	worldTransformMatrix = identity_Mat4x4f();
	rotationMatrix = identity_Mat3x3f();
	worldRotationMatrix = identity_Mat3x3f();
	_updateWorldPosition();
	_updateTransformMatrix();
}

void Transform::addChild(Transform * child){
	if(child){
		child->setParent(this);
	}
    children.push_back(child);
	child->_updateWorldPosition();
	child->_updateWorldRotationMatrix();
}

void Transform::attachChild(Transform * child){
    children.push_back(child);
}

Transform::ChildrenIterator Transform::getChildrenIteratorBegin()const{
	return children.begin();
}
Transform::ChildrenIterator Transform::getChildrenIteratorEnd()const{
	return children.end();
}

void Transform::setParent(Transform * par){
    if(parent != 0)
        parent->removeChild(this);
    parent = par;
}

Transform* Transform::getParent(){
	return parent;
}

size_t Transform::getChildCount() const{
	return children.size();
}

Transform* Transform::getChild(size_t index){
	if( index < this->children.size() )
		return children[index];
	else 
		return 0;
}


int Transform::getChildIndex(Transform * child)const{
	for(size_t i = 0; i < getChildCount(); i++){
		if(children[i] == child)
			return i;
	}
	return -1;
}

void Transform::removeChild(Transform* child){
    std::vector<Transform*>::iterator it;
	bool has = false;
    for(it = children.begin(); it != children.end(); ++it){
		if(*it == child){
			has = true;
            break;
		}
    }
	if(has)
		children.erase(it);
}

void Transform::removeChild(size_t index){
	if(index < 0 || index > getChildCount())
		return;

	std::vector<Transform*>::iterator it = children.begin();
	children.erase(it+index);
}

void Transform::setGameObject(GameObject* object){
	assert(this->gameObject == 0);
    this->gameObject = object;
}

GameObject* Transform::getGameObject()const{
	return gameObject;
}


Vec3f Transform::getPosition()const{
	return position;
}
Vec3f Transform::getScale()const{
	return scaling;
}
Vec3f Transform::getRotation()const{
	return eulerAngles;
}
Vec3f Transform::getWorldPosition()const{
	return worldPosition;
}

Vec3f Transform::getForward()const{
	return worldRotationMatrix[2];
}
Vec3f Transform::getUp()const{
	return worldRotationMatrix[1];
}
Vec3f Transform::getRight()const{
	return worldRotationMatrix[0];
}

Mat3x3f Transform::getRotationMatrix()const{
	return worldRotationMatrix;
}
Mat3x3f Transform::getWorldRotationMatrix()const{
	return worldRotationMatrix;
}
Mat4x4f Transform::getWorldTransformMatrix()const{
	return worldTransformMatrix;
}
Mat4x4f Transform::getWorldInverseTransformMatrix()const{
	Mat4x4f InvRotMat;
	transpose( 
				Mat4x4f(Vec4f(worldRotationMatrix[0],0),
					   Vec4f(worldRotationMatrix[1],0),
					   Vec4f(worldRotationMatrix[2],0),
					   Vec4f(0,0,0,1) ),
			InvRotMat);
	
	Mat4x4f invTrans = identity_Mat4x4f();
	invTrans[3] = Vec4f( -worldPosition, 1);

	Mat4x4f invTransform = invTrans * InvRotMat;

	return invTransform;
}
Mat4x4f Transform::getWorldViewMatrix()const{
	Mat4x4f rotMat;
	transpose( 
			Mat4x4f(Vec4f(-worldRotationMatrix[0],0),
					Vec4f(worldRotationMatrix[1],0),
					Vec4f(-worldRotationMatrix[2],0),
					Vec4f(0,0,0,1) ),
		rotMat);
	
	Mat4x4f translateMatrix = identity_Mat4x4f();
	translateMatrix[3] = Vec4f( -worldPosition, 1);

	Mat4x4f cameraTransformMat = translateMatrix * rotMat;
	
	return cameraTransformMat;
}
Mat4x4f Transform::getWorldInverseViewMatrix() const{
	Mat4x4f rotInv = Mat4x4f(Vec4f(-worldRotationMatrix[0],0),
						Vec4f(worldRotationMatrix[1],0),
						Vec4f(-worldRotationMatrix[2],0),
						Vec4f(0,0,0,1) );

	Mat4x4f transInv = identity_Mat4x4f();
	transInv[3] = Vec4f( worldPosition, 1);

	
	Mat4x4f cameraTransformMat = rotInv * transInv;

	return cameraTransformMat;
}

void Transform::applyTransform()const{
	glMultMatrixf(transformMatrix.get());   
}
void Transform::applyWorldTransform()const{
	if(parent)
		parent->applyWorldTransform();
	applyTransform();
}
void Transform::applyViewTransform()const{
	glMultMatrixf(getWorldViewMatrix().get());
}

void Transform::setPosition(const Vec3f& pos){
	position = Vec3f(pos[0],pos[1],pos[2]);
	_updateWorldPosition();
	_updateTransformMatrix();
}
void Transform::setScale(const Vec3f& scal){
	scaling = scal;
	_updateTransformMatrix();
}
void Transform::setRotation(const Vec3f& rot){
	eulerAngles[0] = fmodf(rot[0],360);
	eulerAngles[1] = fmodf(rot[1],360);
	eulerAngles[2] = fmodf(rot[2],360);

	rotationMatrix = rotation_Mat3x3f(XAXIS,M_PI*eulerAngles[0]/180);
	rotationMatrix *= rotation_Mat3x3f(YAXIS,M_PI*eulerAngles[1]/180);
	rotationMatrix *= rotation_Mat3x3f(ZAXIS,M_PI*eulerAngles[2]/180);

	_updateWorldRotationMatrix();
	_updateTransformMatrix();
	for(size_t i = 0; i < children.size(); i++)
		children[i]->_updateWorldPosition();
}

void Transform::translate(float x, float y, float z){
	translate(Vec3f(x,y,z));
}
void Transform::translate(const Vec3f& translation){
	position += translation;
	_updateWorldPosition();
	_updateTransformMatrix();
}
void Transform::scale(float x, float y, float z){
	scale(Vec3f(x,y,z));
}
void Transform::scale(const Vec3f& scale){
	scaling *= scale;
	_updateTransformMatrix();
}
void Transform::rotate(float yaw, float pitch, float roll, SpaceOfReferenceEnum reference){
	rotate(Vec3f(yaw ,pitch ,roll),reference);
}
void Transform::rotate(const Vec3f& euler_angles, SpaceOfReferenceEnum reference){
	eulerAngles += euler_angles;
	setRotation(eulerAngles);

}

void Transform::rotate(const Vec3f& axis, float angle){
	float uxuy = axis[0]*axis[1];
	float uxuz = axis[0]*axis[2];
	float uyuz = axis[1]*axis[2];
	float radAngle = (float)M_PI*angle/180;
	Mat3x3f uTensu( Vec3f(axis[0]*axis[0],uxuy,uxuz),
					Vec3f(uxuy,axis[1]*axis[1],uyuz),
					Vec3f(uxuz,uyuz,axis[2]*axis[2])
					);
	Mat3x3f skewSymu( Vec3f(0,axis[2],-axis[1]),
					  Vec3f(-axis[2],0,axis[0]),
					  Vec3f(axis[1],-axis[0],0)
					);

	Mat3x3f rotMat = uTensu + cosf(radAngle)*(identity_Mat3x3f()-uTensu)+sinf(radAngle)*skewSymu;
	
	rotMat = rotationMatrix*rotMat;

	_updateWorldRotationMatrix();
}
//Look at a specific point, up vector oriented toward world positive z direction (y if looking in z direction)
void Transform::lookAt(const Vec3f& targetPoint){
	if(targetPoint != worldPosition){
		Vec3f fwd = normalize(targetPoint - worldPosition);

		rotationMatrix[2] = fwd;
		if(!(fwd[0]==0 && fwd[1]==0))
			rotationMatrix[1] = normalize(Vec3f(0,0,1)-dot(Vec3f(0,0,1),fwd)*fwd);
		else
			rotationMatrix[1] = Vec3f(0,1,0);
		rotationMatrix[0] = cross(rotationMatrix[1],fwd);

		_updateWorldRotationMatrix();
	}
}

void Transform::_updateWorldPosition(){
	if(parent)
		worldPosition = parent->getWorldPosition() + /*parent->getScale()**/parent->getRotationMatrix()*position;
	else
		worldPosition = position;
	_updateWorldTransformMatrix();
	for(size_t i = 0; i < children.size(); i++)
		children[i]->_updateWorldPosition();
}

void Transform::_updateWorldRotationMatrix(){
	if(parent)
		worldRotationMatrix = rotationMatrix*parent->getWorldRotationMatrix();
	else
		worldRotationMatrix = rotationMatrix;
	_updateTransformMatrix();
	for(size_t i = 0; i < children.size(); i++)
		children[i]->_updateWorldRotationMatrix();
}
void Transform::_updateWorldTransformMatrix(){
	if(parent)
		worldTransformMatrix =  transformMatrix*parent->getWorldTransformMatrix();
	else
		worldTransformMatrix = transformMatrix;
	for(size_t i = 0; i < children.size(); i++)
			children[i]->_updateWorldTransformMatrix();
}
void Transform::_updateTransformMatrix(){
	transformMatrix = Mat4x4f(Vec4f(scaling[0],0,0,0),Vec4f(0,scaling[1],0,0),Vec4f(0,0,scaling[2],0),Vec4f(0,0,0,1)) *
		Mat4x4f(Vec4f(rotationMatrix[0],0),Vec4f(rotationMatrix[1],0),Vec4f(rotationMatrix[2],0),Vec4f(0,0,0,1)) *
		Mat4x4f(Vec4f(1,0,0,0),	Vec4f(0,1,0,0), Vec4f(0,0,1,0),Vec4f(position,1));

	_updateWorldTransformMatrix();
}