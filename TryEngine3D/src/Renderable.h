#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Component.h"

class Material;

class Renderable:public Component{
	public:
		Renderable();
		virtual ~Renderable();
		virtual void render() const{}
		virtual bool castShadow()const{ return false; }
		virtual bool receiveShadow()const{ return false; }

		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }
		virtual void setMaterial(Material* mat){material = mat;}
		virtual Material* getMaterial(){return this->material;}

	protected:
		Material* material;

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Component>(*this);
		}
};

#endif
