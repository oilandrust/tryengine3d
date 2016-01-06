#include "Terrain.h"
#include "RTTI.h"
#include "includeGL.h"
#include "GLSLShader.h"
#include "Texture.h"

const RTTI Terrain::TYPE("Terrain", &Object::TYPE);
//const GLSLShader Terrain::
	

Terrain::Terrain():terrainShader(string("assets/shaders/"),string("terrain.vert"),string("terrain.frag")),heightMap(NULL),alphaMap(NULL){
	textures[0] = textures[1] = textures[2] = NULL;
	static const int gridSize = 64;
	vertices = new Vec3f[gridSize*gridSize];

	int vertIndex = 0;
	for(int j = 0; j < gridSize; j++){
		for(int i = 0; i < gridSize; i++){
			vertices[vertIndex] = Vec3f(i,j,0);
			vertIndex++;
		}
	}
	
	static const int nbOfQuads = (gridSize-1)*(gridSize-1);
	nbOfTriangles = nbOfQuads*2;
	indices = new unsigned int[nbOfTriangles*3];

	int indCount = 0;
	for(int i = 0; i < gridSize-1; i++){
		for(int j = 0; j < gridSize-1; j++){
			indices[indCount]     = i*gridSize + j;
			indices[indCount + 1] = i*gridSize + j + 1;
			indices[indCount + 2] = i*gridSize + j + gridSize;
			indices[indCount + 3] = i*gridSize + j + gridSize;
			indices[indCount + 4] = i*gridSize + j + 1;
			indices[indCount + 5] = i*gridSize + j + gridSize + 1;
			indCount += 6;
		}
	}
}

void Terrain::render()const{
	//glPolygonMode(GL_FRONT,GL_LINE);
	terrainShader.bindShader();
	static bool first = true;
	if(first){
		glUniform1i(glGetUniformLocation(terrainShader.getShaderProgramId(), "tex0"), 0);
		glUniform1i(glGetUniformLocation(terrainShader.getShaderProgramId(), "tex1"), 1);
		glUniform1i(glGetUniformLocation(terrainShader.getShaderProgramId(), "tex2"), 2);
		glUniform1i(glGetUniformLocation(terrainShader.getShaderProgramId(), "alphaMap"), 3);
		first = false;
	}
		
	if(textures[0]){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]->getTexId());
	}
	if(textures[1]){
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]->getTexId());
	}
	if(textures[2]){
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures[2]->getTexId());
	}
	if(alphaMap){
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, alphaMap->getTexId());
	}
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < nbOfTriangles; i++){
		glVertex3fv(vertices[indices[3*i]].get());
		glVertex3fv(vertices[indices[3*i+1]].get());
		glVertex3fv(vertices[indices[3*i+2]].get());
	}
	glEnd();
	glPolygonMode(GL_FRONT,GL_FILL);
}

void Terrain::setHeightMap(Texture* heightmap){
	heightMap = heightmap;

	static const int gridSize = 64;

	int vertIndex = 0;
	for(int j = 0; j < gridSize; j++){
		for(int i = 0; i < gridSize; i++){
			vertices[vertIndex][2] = heightmap->getPixel(j*heightmap->width()/gridSize,i*heightmap->height()/gridSize)[0]/10;
			vertIndex++;
		}
	}
}


Terrain::~Terrain(){
	delete[] vertices;
	delete[] indices;
}
