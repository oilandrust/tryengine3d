#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <list>
#include "Object.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Behaviour;
class Transform;
class Component;
class Collider;
class Animation;
class ParticleSystem;
class MeshRenderer;
class Renderable;


/**
 *Basic class of the engine, compose game objects with components like renderers, collider, etc...
 */
class GameObject:public Object{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

    private:
		GameObject(GameObject const& object);
		//Attached transform, must be set by the user, this must not be NULL
        Transform* transform;
		//The components of the Game Object
        vector<Component*> components;
		//Map of the game Object's components, allows retrieval by type
		multimap<string,Component*> componentMap;
		//The renderable part of the game object (easy solution to find it easyly, should be improved)
        Renderable* meshRenderer;
		//The collider of the game object (easy solution to find it easyly, should be improved)
		Collider* collider;
		//The behaviour of the game object (easy solution to find it easyly, should be improved)
		Behaviour* behaviour;
		//The animation of the game object
		boost::shared_ptr<Animation> animation;
		ParticleSystem* particleSystem;

		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Object>(*this);
			ar & meshRenderer;
			for(size_t i = 0; i < components.size(); ++i)
				ar & components[i];
			ar & transform;
		}

    public:
        GameObject();
		
		~GameObject();

        void addComponent(Component* comp);
        
		void setRenderer(Renderable* renderer);
		Renderable* getRenderer() const;

        Transform* getTransform() const;
        void setTransform(Transform* trans);

		Behaviour* getBehaviour() const;
        void setBehaviour(Behaviour* behav);

		Collider* getCollider() const;
        void setCollider(Collider* collid);

		boost::shared_ptr<Animation> getAnimation() const;
        void setAnimation(boost::shared_ptr<Animation> anim);

		ParticleSystem* getParticleSystem() const;
        void setParticleSystem(ParticleSystem* anim);

		void onCollisionEnter();

};

#endif // GAMEOBJECT_H_INCLUDED
