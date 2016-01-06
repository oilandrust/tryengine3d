#include "MeshRenderer.h"
#include "Material.h"
#include "TriMesh.h"

using namespace TR3D;


const RTTI MeshRenderer::TYPE("MeshRenderer", &Component::TYPE);

MeshRenderer::MeshRenderer():_receiveShadow(false),_castShadow(false){
}

MeshRenderer::~MeshRenderer(){
}

void MeshRenderer::render() const{
	
	if(!mesh)
		std::cerr<<"Mesh not set in MeshRenderer::render "<<this->name<<std::endl;
	else
		mesh->sendVertices();
}

void MeshRenderer::setMesh(boost::shared_ptr<TR3D::TriMesh>  Mesh){
	this->mesh = Mesh;
}
boost::shared_ptr<TR3D::TriMesh>  MeshRenderer::getMesh(){
	return this->mesh;
}


bool MeshRenderer::castShadow()const{return _castShadow;}
bool MeshRenderer::receiveShadow()const{return _receiveShadow;}
void MeshRenderer::setCastShadow(bool cast){_castShadow = cast;}
void MeshRenderer::setReceiveShadow(bool receive){_receiveShadow = receive;}

