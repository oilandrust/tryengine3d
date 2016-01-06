#include "Material.h"
#include "Scene.h"
#include "Texture.h"
#include "GLSLShader.h"

const RTTI Material::TYPE("Material", &Component::TYPE);

Material::Material(){
    color = diffuse = ambient = specular = Vec4f(0.7f,0.7f,0.7f,1.0f);
	shininess = 0;
}

Material::~Material(){
}

Material::Material(ColorEnum Color){
    switch(Color){
        case RED:
            color = diffuse = ambient = specular = Vec4f(0.7f,0,0,1);
        break;
        case BLUE:
            color = diffuse = ambient = specular = Vec4f(0,0,0.7f,1);
        break;
        case GREEN:
            color = diffuse = ambient = specular = Vec4f(0,1,0,1);
        break;
        case BLACK:
            color = diffuse = ambient = specular = Vec4f(0,0,0,1);
        break;
        case YELLOW:
            color = diffuse = ambient = specular = Vec4f(0.5f,0.5f,0,1);
        break;
        default:
            color = diffuse = ambient = specular = Vec4f(0.7f,0.7f,0.7f,1);
    }
	shininess = 10;
}

Material::Material(const Vec4f& Color){
    color = diffuse = ambient = specular = Vec4f(Color);
}

void Material::setTexture(boost::shared_ptr<Texture> tex){
	this->texture = tex;
}
void Material::setShader(boost::shared_ptr<GLSLShader> Shader){
	this->shader = Shader;
}

void Material::setMaterialState(bool receives_shadow)const{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.get());
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.get());
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular.get());
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	if(shader)
		shader->bindShader();
	else
		glUseProgram(0);

	//texture->bindTexture();
	if(shader){
		//MAIN TEXTURE	
		if(texture){
			glUniform1i(glGetUniformLocation(shader->getShaderProgramId(), "mainTexture"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getTexId());	
		}else{
			glUniform1i(glGetUniformLocation(shader->getShaderProgramId(), "mainTexture"), 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);	
		}
		/*
		//SHADOW MAP
		glUniform1i(glGetUniformLocation(shader->getShaderProgramId(), "shadowMap"), 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, Scene::shadowMap);

		GLfloat id = glGetUniformLocation(shader->getShaderProgramId(), "receiveShadow");
		glUniform1f(id, receives_shadow ? 1 : 0);

		glUniformMatrix4fv(glGetUniformLocation(shader->getShaderProgramId(), "shadowMat"),
							1,
							false,
							Scene::projShadowMatrix.get());
							*/
	}
}
