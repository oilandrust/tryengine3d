#include "RTTI.h"


RTTI::RTTI(const string& name, const RTTI* baseType):name(name),baseType(baseType){
}


RTTI::~RTTI(){
}

const string& RTTI::getName () const{
	return name;
}
bool RTTI::isExactly (const RTTI& type) const{
	return &type == this;
}
bool RTTI::isDerived (const RTTI& type) const{
	const RTTI* pkSearch = this;

	while ( pkSearch ){
		if ( pkSearch == &type )
			return true;
		pkSearch = pkSearch->baseType;
	}
	return false;
}
