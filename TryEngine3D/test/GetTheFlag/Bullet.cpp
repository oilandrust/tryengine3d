#include "Bullet.h"
#include "TREngine.h"


Bullet::Bullet(): velocity(1,0,0),speed(1)
{
}


Bullet::~Bullet(void)
{
}

void Bullet::onMouseMotion(const SDL_MouseMotionEvent & event){}
void Bullet::onMouseButton(const SDL_Event & event){}
void Bullet::onKeyboard(const SDL_KeyboardEvent & event){}
void Bullet::update(){
	getGameObject().getTransform()->translate(speed*velocity);
}
void Bullet::onCollisionEnter(){
	cout<<"bullet explode"<<endl;
	TREngine::getInstance()->deleteGameObject(gameObject);
}

