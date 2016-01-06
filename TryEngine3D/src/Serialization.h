#ifndef SERIALIZATION_H
#define SERIALIZATION_H

//Register class for serialization (needed whe derived class is serialized just like base class)
#include <boost/serialization/export.hpp>

namespace boost {
namespace serialization {

		template<class Archive>
		void serialize(Archive & ar, Vec3f & v, const unsigned int version){
			ar & v[0];
			ar & v[1];
			ar & v[2];
		}

		
		template<class Archive>
		void serialize(Archive & ar, Vec4f & v, const unsigned int version){
			ar & v[0];
			ar & v[1];
			ar & v[2];
			ar & v[3];
		}

	} // namespace serialization
} // namespace boost


#endif