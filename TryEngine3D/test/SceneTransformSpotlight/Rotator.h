#ifndef ROTATOR_H_INCLUDED
#define ROTATOR_H_INCLUDED

#include "Behaviour.h"
#include "TryEngine.h"
#include <SDL.h>

class Rotator: public Behaviour{
	protected:
		float speed;
	public:
		Rotator(float RotationSpeed);
		~Rotator();
		void update();
};
#endif