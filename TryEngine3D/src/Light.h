#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "Component.h"
#include "CGLA/Vec4f.h"
#include "includeGL.h"

class LightManager;
class Transform;

using namespace CGLA;
enum LightTypEnum {
	AMBIANT,
	POINTSOURCE,
	SPOTLIGHT,
	DISTANTSOURCE
};

class Light: public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		Vec4f diffuse;
		Vec4f ambient;
		Vec4f specular;
		float coneAngle;
		float coneExponent;


		LightTypEnum lightType;

		GLenum glLightId;
		Transform* transform;

		GLenum intToGlLightId(int id);

	public:
		Light(const Vec4f& amb, const Vec4f& diff, const Vec4f& spec, LightManager* manager);
		static Light ambientLight(const Vec4f& amb, LightManager* manager);
		
		void setLightType(LightTypEnum type);

		Transform* getTransform()const;
		void setTransform(Transform* trans);

		void applyLightState();
};

#endif // LIGHT_H_INCLUDED
