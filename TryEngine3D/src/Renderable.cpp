#include "Renderable.h"
#include "Material.h"

const RTTI Renderable::TYPE("Renderable", &Component::TYPE);

Renderable::Renderable(void):
material(0)
{
}


Renderable::~Renderable(void)
{
	if(this->material)
		delete this->material;
}
