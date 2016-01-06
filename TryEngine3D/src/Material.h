#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "CGLA/Vec4f.h"
#include "Component.h"
#include "includeGL.h"



class GLSLShader;
class Texture;

/*CHANGE COLOR TO BYTE*/

using namespace CGLA;

enum ColorEnum {
	RED,
	BLUE,
	GREEN,
	YELLOW,
	BLACK,
	WHITE
};


class Material:public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

    private:
        Vec4f color;
		Vec4f ambient;
		Vec4f diffuse;
		Vec4f specular;
		float shininess;

		boost::shared_ptr<Texture> texture;
		boost::shared_ptr<GLSLShader> shader;

    public:
        Material();
		~Material();

        Material(ColorEnum Color);
        Material(const Vec4f& Color);

		void setTexture(boost::shared_ptr<Texture> tex);
		void setShader(boost::shared_ptr<GLSLShader> Shader);

        void setMaterialState(bool receives_shadow)const;

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Component>(*this);
			ar & color;
			ar & ambient;
			ar & diffuse;
			ar & specular;
			ar & shininess;
			ar & texture;
			ar & shader;
		}

};

#endif // MATERIAL_H_INCLUDED
