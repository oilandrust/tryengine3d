#ifndef MESHRENDERER_H_INCLUDED
#define MESHRENDERER_H_INCLUDED

#include "Renderable.h"
#include "CGLA/Vec3f.h"
#include "TriMesh.h"

enum BasicShapeEnum;

class Material;

using namespace CGLA;
class GameObject;

class MeshRenderer:public Renderable{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

    protected:
		boost::shared_ptr<TR3D::TriMesh> mesh;
		bool _castShadow;
		bool _receiveShadow;

    public:
		MeshRenderer();
		~MeshRenderer();

        virtual void render() const;

		void setMesh(boost::shared_ptr<TR3D::TriMesh>  Mesh);
		boost::shared_ptr<TR3D::TriMesh>  getMesh();

		bool castShadow()const;
		bool receiveShadow()const;
		void setCastShadow(bool cast);
		void setReceiveShadow(bool receive);

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Renderable>(*this);
			ar & material;
			ar & mesh;
			ar & _castShadow;
			ar & _receiveShadow;
		}

};

#endif // MESHRENDERER_H_INCLUDED
