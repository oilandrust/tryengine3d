#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include "Object.h"
#include <CGLA/Vec3f.h>

using namespace CGLA;
class GameObject;

/**
 *Base class for a Component to attach to a GameObject.
 */
class Component:public Object{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

    protected:
        GameObject* gameObject;
		bool enabled;

    public:
		Component();
		virtual ~Component();

        GameObject* getGameObject();
		GameObject const* const getGameObject()const;
        void setGameObject(GameObject* obj);

		virtual Vec3f getWorldPosition()const;
		virtual Vec3f getPosition()const;

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Object>(*this);
			//ar & gameObject;
			//ar & enabled;
		}


};

#endif // COMPONENT_H_INCLUDED
