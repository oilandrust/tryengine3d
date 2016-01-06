#ifndef TEXTURE_H
#define TEXTURE_H

#include "Component.h"
#include "includeGL.h"
#include <string>
#include "CGLA/Vec4f.h"
#include <SDL.h>
#include "Ressource.h"

using namespace CGLA;


class Texture:public Component, public Ressource{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		GLuint glTexObject;
		std::string ressourceName;
		SDL_Surface * textureMemory;

		SDL_Surface * flipSurface(SDL_Surface * surface);
		GLuint loadTexture(const char * filename,bool useMipMap);

	public:
		Texture();
		~Texture();

		virtual void load(const string& name);

		void bindTexture()const;
		GLuint getTexId()const;

		Vec4f getPixel(int u, int v)const;
		Vec4f getPixel(float u, float v)const;

		int width()const{return textureMemory->w;}
		int height()const{return textureMemory->h;}

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Component>(*this);
			ar & ressourceName;
		}
};

#endif