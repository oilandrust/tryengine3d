#include "MeshRenderer.h"
#include "Renderable.h"
#include "Material.h"
#include "GameObject.h"
#include "Transform.h"
#include "Light.h"
#include "Camera.h"
#include "Scene.h"
#include "Screen.h"
#include "GLSLShader.h"
#include "ParticleSystem.h"
#include "TriMesh.h"

using namespace TR3D;


#include <stack>
#include <gl/glu.h>

GLuint Scene::shadowMap = 0;
Mat4x4f Scene::projShadowMatrix = Mat4x4f(0);

Scene::Scene(): sceneRoot(NULL),useShadows(true){

	glGenTextures(1,&shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0,
		GL_DEPTH_COMPONENT,GL_UNSIGNED_BYTE, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glEnable(GL_TEXTURE_2D);

}

void Scene::clear(){
	transforms.clear();
	lights.clear();
	cameras.clear();
	matSortedBatches.clear();
	shadowCasters.clear();

    sceneRoot = 0;
	mainCamera = 0;
}
void Scene::useShadow(bool use){
	useShadows = use;
}
void Scene::render(){

	GameObject* camObject = Camera::getMainCamera()->getGameObject();

	
	if(useShadows && !lights.empty()){
		//RENDER THE SHADOW MAP;
		if(shadowCasters.size() > 0)
			for(size_t i = 0; i < lights.size(); i++){
				make_proj_shadow_texture(lights[i]);
			}
		//COMPUTE PROJ SHADOW MATRIX
		Mat4x4f B = Mat4x4f( Vec4f(0.5f,0   ,   0,0),
									Vec4f(0   ,0.5f,   0,0),
									Vec4f(0   ,0   ,0.5f,0),
									Vec4f(0.5f,0.5f,0.5f,1));
		
		Mat4x4f Pp;
		glGetFloatv(GL_PROJECTION_MATRIX,Pp.get());
		Mat4x4f Vp = lights[0]->getTransform()->getWorldViewMatrix();
		Mat4x4f Ve_1 = camObject->getTransform()->getWorldInverseViewMatrix();
		
		projShadowMatrix =  Ve_1 * Vp * Pp *B;
		
	}

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );

	glClearColor(0,0,0,1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	camObject->getTransform()->applyViewTransform();
	  
	applyLightsStates();
/*
	for(size_t i = 0; i < renderQueue.size(); i++){

		glPushMatrix();
		if( renderQueue[i]->getType().getName() == "ParticleSystem" ){
			Mat4x4f trans = identity_Mat4x4f();
			trans[3] = Vec4f(renderQueue[i]->getGameObject()->getTransform()->getWorldPosition()
				+   static_cast<ParticleSystem*>(renderQueue[i])->getPosition()
				,1);
			glMultMatrixf(trans.get());
		}else
			
		renderQueue[i]->render();
		glPopMatrix();
	}
*/
	map<Material*, vector<Renderable*> >::iterator itr = matSortedBatches.begin();
	for(; itr != matSortedBatches.end(); ++itr){
		Material* mat = itr->first;
		mat->setMaterialState(true);

		for(vector<Renderable*>::iterator rend = itr->second.begin(); rend!=itr->second.end(); ++rend){
			glPushMatrix();
			glMultMatrixf((*rend)->getGameObject()->getTransform()->getWorldTransformMatrix().get());
			(*rend)->render();
			glPopMatrix();
		}
	}
}

void Scene::traverseSceneGraph(){

	//renderQueue.clear();
	matSortedBatches.clear();
	shadowCasters.clear();

	Transform* node = sceneRoot;
	std::stack<Transform*> openList;
	openList.push(sceneRoot);
	
	while( !openList.empty() ){	
		node = openList.top();
		openList.pop();
		
		if(node->getGameObject()){
			Renderable * renderer = node->getGameObject()->getRenderer();
			if(renderer){
				if(renderer->getMaterial())
					matSortedBatches[renderer->getMaterial()].push_back(renderer) ;
					//renderQueue.push_back(renderer);
				if(renderer->castShadow()){
					shadowCasters.push_back(renderer);
				}
			}
			renderer = (Renderable*)(node->getGameObject()->getParticleSystem());
			if(renderer){
				//renderQueue.push_back(renderer);
				if(renderer->castShadow()){
					shadowCasters.push_back(renderer);
				}
			}
		}
		
		Transform::ChildrenIterator childIt = node->getChildrenIteratorBegin();

		for(; childIt != node->getChildrenIteratorEnd(); ++childIt){
			openList.push(*childIt);				
		}
	}
}

void Scene::updateRenderQueue(){
	traverseSceneGraph();
}
void Scene::setRoot(Transform* root){
    sceneRoot = root;
}

Transform* Scene::getRoot(){
    return sceneRoot;
}

void Scene::addGameObject(GameObject * object){
	if(!object->getTransform()){
		std::cout<<"Trying to insert object without transform in the scene!"<<std::endl;
		return;
	}
	sceneRoot->addChild(object->getTransform());
}

void Scene::removeGameObject(GameObject * object){
	assert(object != this->sceneRoot->getGameObject());
	object->getTransform()->getParent()->removeChild(object->getTransform());
}

void Scene::addLight(Light* light){
	lights.push_back(light);
}

void Scene::applyLightsStates()const{
	std::vector<Light*>::const_iterator it = lights.begin();
	for(; it != lights.end(); ++it){
		glPushMatrix();
		(*it)->getTransform()->applyTransform();
		(*it)->applyLightState();
		glPopMatrix();
	}
}

void Scene::addCamera(Camera * camera){
	cameras.push_back(camera);
}

//TODO : Make sure to store the camera if not stored
void Scene::setMainCamera(Camera* camera){
	mainCamera = camera;
}


void Scene::make_proj_shadow_texture(Light* light){
	assert(light != 0);

	glViewport(0,0,shadowMapSize,shadowMapSize);
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//lookat
	light->getTransform()->applyViewTransform();
	glDisable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
    glColorMask(0, 0, 0, 0);

	static GLuint shadowMapProg=0;
	if(!shadowMapProg)
	{
		shadowMapProg = glCreateProgram();
		GLuint shadowMapProgVS = create_glsl_shader(GL_VERTEX_SHADER,
			"varying vec3 position;"
			"void main() {" 
			"position = (gl_ModelViewProjectionMatrix * gl_Vertex).xyz;"
			"gl_Position = ftransform();}");
		GLuint shadowMapProgFS = create_glsl_shader(GL_FRAGMENT_SHADER,
			"varying vec3 position;"
			"void main() { gl_FragColor = vec4(0.3);}");

		glAttachShader(shadowMapProg, shadowMapProgVS);
		glAttachShader(shadowMapProg, shadowMapProgFS);
		glLinkProgram(shadowMapProg);
		print_glsl_program_log(shadowMapProg);
	}

	//glUseProgram(shadowMapProg);
	glUseProgram(0);
	
	//DRAW OBJECTS
	for(size_t i = 0; i < shadowCasters.size(); i++){
		glPushMatrix();
		glMultMatrixf(shadowCasters[i]->getGameObject()->getTransform()->getWorldTransformMatrix().get());
		
		if(shadowCasters[i]->getType().getName() == "MeshRenderer"){
			TriMesh* mesh = static_cast<MeshRenderer*>(shadowCasters[i])->getMesh().get();
			if(mesh)
				mesh->sendVertices();
		}
		
		glPopMatrix();
	}
	
	glBindTexture(GL_TEXTURE_2D,shadowMap);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);
	//glCopyTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,0,0,Screen::width,Screen::height,0);
	
	glViewport(0,0,Screen::width,Screen::height);
	glEnable(GL_LIGHTING);
	glColorMask(1, 1, 1, 1);
	//glFlush();
}

//nothing to do here but has to be somewhere
void drawAxis(double scale)
{
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushMatrix();
	glUseProgram(0);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glScaled(scale,scale,scale);
    glBegin(GL_LINES);
    glColor3ub(255,0,0);
    glVertex3i(0,0,0);
    glVertex3i(1,0,0);
    glColor3ub(0,255,0);
    glVertex3i(0,0,0);
    glVertex3i(0,1,0);
    glColor3ub(0,0,255);
    glVertex3i(0,0,0);
    glVertex3i(0,0,1);
    glEnd();
    glPopMatrix();
    glPopAttrib();
}



