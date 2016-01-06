#include "Light.h"
#include "LightManager.h"
#include "Transform.h"

const RTTI Light::TYPE("Light", &Component::TYPE);

Light::Light(const Vec4f& amb, const Vec4f& diff, const Vec4f& spec, LightManager* manager){
	ambient = Vec4f(*amb.get(),*(amb.get()+1),*(amb.get()+2),*(amb.get()+3));
	diffuse = Vec4f(*diff.get(),*(diff.get()+1),*(diff.get()+2),*(diff.get()+3));
	specular = Vec4f(*spec.get(),*(spec.get()+1),*(spec.get()+2),*(spec.get()+3));
	glLightId = intToGlLightId(manager->getAvailableLightId());
	coneAngle = 15;
	coneExponent = 0;
	lightType = POINTSOURCE;
}

GLenum Light::intToGlLightId(int id){
				std::cout<<id<<std::endl;
	switch(id){
		case 0:
			return GL_LIGHT0;
			break;
		case 1:
			return GL_LIGHT1;
			break;
		case 2:
			return GL_LIGHT2;
			break;
		case 3:
			return GL_LIGHT3;
			break;
		case 4:
			return GL_LIGHT4;
			break;
		case 5:
			return GL_LIGHT5;
			break;
		case 6:
			return GL_LIGHT6;
			break;
		case 7:
			return GL_LIGHT7;
			break;
		default:
			std::cout<<"Invalid Light id"<<std::endl;
			return NULL;
	}
}


Transform* Light::getTransform()const{
    if(transform == NULL)
        std::cout<<"Light has no transform"<<std::endl;
    return transform;
}

void Light::setTransform(Transform* trans){
    transform = trans;
}

void Light::applyLightState(){
	glEnable(glLightId);
	glLightfv(glLightId, GL_DIFFUSE, diffuse.get());
	glLightfv(glLightId, GL_AMBIENT, ambient.get());
	glLightfv(glLightId, GL_SPECULAR, specular.get());

	switch(lightType){
		case AMBIANT:;
			break;
		case POINTSOURCE:
			glLightfv(glLightId, GL_POSITION, Vec4f(0,0,0,1).get());
			break;
		case SPOTLIGHT:
			glLightfv(glLightId, GL_POSITION, Vec4f(0,0,0,1).get());
			glLightfv(glLightId, GL_SPOT_DIRECTION, Vec4f(0,0,1,1).get());
			glLightf(glLightId, GL_SPOT_CUTOFF, coneAngle);
			glLightf(glLightId, GL_SPOT_EXPONENT, coneExponent);
			break;
		case DISTANTSOURCE:
			glLightfv(glLightId, GL_POSITION, Vec4f(0,0,-1,0).get()); 
			break;
	}
}

void Light::setLightType(LightTypEnum type){
	lightType = type;
}