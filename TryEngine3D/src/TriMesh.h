#ifndef TRIMESH_H_INCLUDED
#define TRIMESH_H_INCLUDED

#include "CGLA/Vec3f.h"
#include "CGLA/Vec3i.h"
#include "Component.h"
#include "Geometry/TriMesh.h"
#include "Ressource.h"
#include "includeGL.h"


enum BasicShapeEnum{
	CUBE,
	SPHERE,
	PLANE
};

using namespace CGLA;

namespace TR3D{

	static const Vec3i NULL_FACE(-1,-1,-1);

	class TriMesh:public Object, public Ressource{
		public :
			static const RTTI TYPE;
			virtual const RTTI& getType() const{ return TYPE; }

		protected:
			Geometry::TriMesh mesh;	
			GLuint VBOId;
			GLuint iVBOId;
			GLuint nVBOId;
			GLuint tVBOId;
			void createVBO();
		
		public:
			TriMesh();
			TriMesh(BasicShapeEnum shape);
			~TriMesh();
			virtual void sendVertices()const;

			virtual void load(const string& name);

		private:
			void loadOBJ(const string& fileName);

			//Serialization
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive& ar, const unsigned int version){
				// serialize base class information
				ar & boost::serialization::base_object<Object>(*this);
				ar & ressourceName;
			}

			inline int get_vert(int i) {
				assert(i!=0);
				if (i<0) {
					return mesh.geometry.no_vertices()+i;
				} else
					return i-1;
			}

			inline int get_normal(int i) {
				if (i<0) {
					return mesh.normals.no_vertices()+i;
				} else
					return i-1;
			}

			inline int get_texcoord(int i) {
				if (i<0) {
					return mesh.texcoords.no_vertices()+i;
				} else
					return i-1;
			}
				
			void read_material_library(const string& filename);

	};

}

#endif
