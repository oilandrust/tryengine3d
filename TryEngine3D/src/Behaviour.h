#ifndef BEHAVIOUR_H_INCLUDED
#define BEHAVIOUR_H_INCLUDED

#include "Component.h"

#include <SDL.h>

struct CollisionHit;
class Transform;
class GameObject;


/**
 *Base class for a behaviour Component of a GameObject.
 *Inherit in your apps to implement gameplay and game rules.
 */
class Behaviour: public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		GameObject * gameObject;

	public:
		Behaviour();
		virtual ~Behaviour();

		/**
		 *Get a reference to the GameObject owner of the behaviour.
		 */
		const GameObject& getGameObject();
		/**
		 *Set the GameObject owner of the behaviour.
		 */
		void setGameObject(GameObject* object);

		/**
		 *Called by the engine on mouse motion events.
		 *Override to implement mouse controls.
		 */
		virtual void onMouseMotion(const SDL_MouseMotionEvent & event);
		/**
		 *Called by the engine on mouse button events.
		 *Override to implement mouse controls.
		 */
		virtual void onMouseButton(const SDL_Event & event);
		/**
		 *Called by the engine on joystick button events.
		 *Override to implement joystick controls.
		 */
		virtual void onJoystickButton(const SDL_Event & event);
		/**
		 *Called by the engine on keyboard events.
		 *Override to implement keyboard controls.
		 */
		virtual void onKeyboard(const SDL_KeyboardEvent & event);
		/**
		 *Called by the engine once per frame.
		 *Override to implement physics.
		 */
		virtual void update();
		/**
		 *Callback function on collision events.
		 */
		virtual void onCollisionEnter(const CollisionHit& hit);
};

#endif
