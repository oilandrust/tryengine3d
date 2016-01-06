#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/shared_ptr.hpp>
#include "RTTI.h"


#include <string>

using namespace std;

class Object{
	public:
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		unsigned int id;
		string name;

	private:
		int refCount;

		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			ar & name;
		}

	public:
		Object();
		Object(const string& name);
		virtual ~Object();
		void setName(const string& name);
		const string& getName() const;

	public:
		//reference counting
		void incRef();
		void decRef();
		int getRefCount()const;
};

#endif // OBJECT_H_INCLUDED
