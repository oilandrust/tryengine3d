#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "CGLA/Vec3f.h"
#include "CGLA/Vec4f.h"
#include "CGLA/Mat3x3f.h"
#include "CGLA/Mat4x4f.h"
#include "Object.h"

#include <vector>

class GameObject;

using namespace CGLA;

enum SpaceOfReferenceEnum{
	LOCAL,
	PARENT,
	WORLD
};

//Transform class
/*
* Class responsible for the scene graph hierarchy and for the space transformations,
* A transform must attached to a game object, child can be attached,
* The class provides methods for translation, rotation and scalings as well as accessors
* for world and local transform matrices as well as the inverses and the wiew transformations.
*/

class Transform :public Object{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	public: 
		typedef std::vector<Transform*>::const_iterator ChildrenIterator;

    protected:
		GameObject* gameObject;

        Transform * parent;
        std::vector<Transform*> children;
        
        Vec3f position;
		Vec3f worldPosition;
		Vec3f scaling;
		Vec3f worldScaling;
		Vec3f eulerAngles;
		Vec3f worldEulerAngles;

		Mat3x3f rotationMatrix;
		Mat3x3f worldRotationMatrix;
		Mat4x4f transformMatrix;
		Mat4x4f worldTransformMatrix;
        
		bool _hasMoved;

    public:
        Transform();
		Transform(const Transform& other);
		~Transform();
        Transform(Vec3f const& pos);

        void setGameObject(GameObject* object);
		GameObject* getGameObject()const;

		//***********TREE STRTURE********//
        void addChild(Transform* child);
		void attachChild(Transform* child);
        void removeChild(Transform* child);
		void removeChild(size_t index);
		ChildrenIterator getChildrenIteratorBegin()const;
		ChildrenIterator getChildrenIteratorEnd()const;
		size_t getChildCount()const;
		Transform* getChild(size_t index);
		int getChildIndex(Transform * child)const;
		Transform* getParent();

		void setParent(Transform* par);

		//*****************MOVEMENT************//
		/**
		 * Unused, unmaintained
		 */
		void setPosition(const Vec3f& pos);
		/**
		 * Unused, unimplemented
		 */
		void setWorldPosition(const Vec3f& pos);
		/**
		 * Unused, unmaintained
		 */
		void setScale(const Vec3f& scal);
		/**
		 * Unused, unimplemented
		 */
		void setWorldScale(const Vec3f& scal);
		/**
		 * Unused, unmaintained
		 */
		void setRotation(const Vec3f& rot);
			
		void translate(float x, float y, float z);
		void translate(const Vec3f& translation);

		void scale(float x, float y, float z);
		void scale(const Vec3f& scaling);
		/**
		 * set the rotation of the transform, bad interface since rot are done xyz
		 */
		void rotate(float rx, float ry, float rz, SpaceOfReferenceEnum reference = PARENT);
		/**
		 * set the rotation of the transform, bad interface since rot are done xyz
		 */
		void rotate(const Vec3f& euler_angles, SpaceOfReferenceEnum reference = PARENT);
		/**
		 * Rotates the transform around an arbitrary axe in world space
		 */
		void rotate(const Vec3f& axis, float angle);

		/**
		 * Sets the orientation of the transform so that it points to targetPoint with up vector being z world
		 */
		void lookAt(const Vec3f& targetPoint);

		
		//***********QUERIES*********//
		Vec3f getPosition()const;
		Vec3f getWorldPosition()const;
		Vec3f getScale()const;
		Vec3f getWorldScale()const;
		Vec3f getRotation()const;

		/**
		 * Returns the forward vector of the frame in world space
		 */
		Vec3f getForward()const;
		/**
		 * Returns the up vector of the frame in world space
		 */
		Vec3f getUp()const;
		/**
		 * Returns the right vector of the frame in world space
		 */
		Vec3f getRight()const;

		Mat3x3f getRotationMatrix()const;
		Mat3x3f getWorldRotationMatrix()const;
		Mat4x4f getTransformMatrix()const;
		/**
		 * Returns the inverse of the transform matrix (used?) not taking into account the scaling
		 */
		Mat4x4f getInverseTransformMatrix()const;

		Mat4x4f getWorldTransformMatrix()const;
		Mat4x4f getWorldInverseTransformMatrix()const;

		Mat4x4f getWorldViewMatrix() const;
		Mat4x4f getWorldInverseViewMatrix() const;

		//*****************OPENGL STATE**********//
		void applyTransform()const;
		void applyWorldTransform()const;
		void applyViewTransform()const;
		void applyWorldViewTransform()const;

		/**
		 * Called internally, updates and caches the world position given the one of the parent, propagates to childrens
		 */
		void _updateWorldPosition();
		/**
		 * Called internally, updates and caches the local transform matrix from position rotation and scaling, calls _updateWorldPosition()
		 */
		void _updateTransformMatrix();
		/**
		 * Called internally, updates and caches the worl transform (SRT) matrix from the parent, propagates to childrens
		 */
		void _updateWorldTransformMatrix();
		/**
		 * Called internally, updates and caches the worl rotation matrix (R) from the parent, propagates to childrens
		 */
		void _updateWorldRotationMatrix();

	protected:


	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Object>(*this);
			ar & position;
			ar & scaling;
			ar & eulerAngles;
		}

};


#endif // TRANSFORM_H_INCLUDED
