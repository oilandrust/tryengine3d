#ifndef POINTER_H_INCLUDED
#define POINTER_H_INCLUDED

template <class T>
class Pointer{
	public:
			// construction and destruction
		Pointer (T* Object = NULL);
		Pointer (const Pointer& pointer);
		~Pointer ();
		// implicit conversions
		operator T* () const{return pobject;}
		T& operator* () const;
		T* operator-> () const;
		// assignment
		Pointer& operator= (T* Object);
		Pointer& operator= (const Pointer& reference);
		// comparisons
		bool operator== (T* pkObject) const;
		bool operator!= (T* pkObject) const;
		bool operator== (const Pointer& rkReference) const;
		bool operator!= (const Pointer& rkReference) const;
		
	protected:
		// the shared object
		T* pobject;
};

//CONSTRUCTORS AND DESTRUCTORS
template <class T> 
Pointer<T>::Pointer (T* object){
	pbject = object;
	if ( pobject )
		pobject->incRef();
}
template <class T> 
Pointer<T>::Pointer (const Pointer& pointer){
	pobject = pointer.pobject;
	if ( pobject )
		pobject->incRef();
}
template <class T> 
Pointer<T>::~Pointer (){
	if ( pobject )
		pobject->decRef();
}

//IMPLICIT CONVERSION
template <class T> 
T& Pointer<T>::operator* () const{
	return *pobject;
}

template <class T> 
T* Pointer<T>::operator-> () const{
	return pobject;
}

//ASSIGNEMENT
template <class T> 
Pointer<T>& Pointer<T>::operator= (T* pkObject){

	if ( pobject != pkObject ){

		if ( pkObject )
			pkObject->incRef();
		
		if ( pobject )
			pobject->decRef();
		
		pobject = pkObject;
	}
	return *this;
}

template <class T> 
Pointer<T>& Pointer<T>::operator= (Pointer<T>& reference){

	if ( reference.pobject )
		reference.pobject->incRef();
	
	if ( pobject )
		pobject->decRef();
	
	pobject = reference.pobject;

	return *this;
}

//COMPARISON
template <class T> 
bool operator== (T* pkObject) const;

template <class T> 
bool operator!= (T* pkObject) const;

template <class T> 
bool operator== (const Pointer& rkReference) const;

template <class T> 
bool operator!= (const Pointer& rkReference) const;

#endif
