#ifndef TERRAIN_H
#define TERRAIN_H

#include "CGLA/Vec3f.h"
#include "Renderable.h"

class Texture;

#include "GLSLShader.h"

using namespace CGLA;

class Terrain : public Renderable{
	public:
		Terrain();
		~Terrain();
		void render()const;

	protected:
		Vec3f* vertices;
		unsigned int* indices;
		Texture* heightMap;
		Texture* alphaMap;
		Texture* textures[3];
		int nbOfTriangles;
		GLSLShader terrainShader;

	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

		void setHeightMap(Texture * tex);
		void setTexture(int i , Texture* tex){
			textures[i] = tex;
		}
		void setAlphaMap(Texture * tex){
			alphaMap = tex;
		}
};

#endif

