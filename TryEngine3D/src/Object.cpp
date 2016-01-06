#include "Object.h"

const RTTI Object::TYPE("Object",NULL);

Object::Object():name("newObject"), refCount(0){}
Object::Object(const string& Name):name(Name), refCount(0){}
Object::~Object(){}

void Object::setName(const string& Name){
	name = Name;
}

const string& Object::getName() const{
	return name;
}

void Object::incRef(){
	++refCount;
}
void Object::decRef(){
	if ( --refCount == 0 )
		delete this;
}
int Object::getRefCount()const{
	return refCount;
}