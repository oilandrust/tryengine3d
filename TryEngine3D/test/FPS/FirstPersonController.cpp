#include "FirstPersonController.h"
#include "Bullet.h"

FirstPersonController::FirstPersonController(): 
velocity(0),
speed(10.0f),
shootTimer(100),
jumping(false),
head(NULL),
weapon(NULL),
mouseSensitivity(4.0f)
{
	//getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + aimDir);
}


FirstPersonController::~FirstPersonController()
{
}

void FirstPersonController::onMouseMotion(const SDL_MouseMotionEvent & event){

	if( abs(event.xrel) > 0.40f*Screen::width || abs(event.yrel) > 0.40f*Screen::height )
		return;

	Vec3f rotation = head->getRotation();
	float pitch = 0;

	if(abs(90-(rotation[0] + Timer::deltaTime()*mouseSensitivity*(event.yrel))) < 90 )
		pitch = Timer::deltaTime()*mouseSensitivity*event.yrel;
	
	head->rotate(pitch,0,-Timer::deltaTime()*mouseSensitivity*event.xrel);

	if( abs(event.x-Screen::width/2) > Screen::width*0.45f 
		|| 
		abs(event.y-Screen::height/2) > Screen::height*0.45f
	  ) 
	  SDL_WarpMouseInWindow(Screen::windowHandle,Screen::width/2,Screen::height/2);

}
void FirstPersonController::onMouseButton(const SDL_Event & event){
	if(shootTimer >= 10){
		//GameObject* bullet = createBullet();
		//bullet->getTransform()->setPosition(gameObject->getTransform()->getPosition() + 2 * aimDir);
		//static_cast<Bullet*>(bullet->getBehaviour())->setVelocity(aimDir);
		//TREngine::getInstance()->addGameObject(bullet);
		if(weapon){
			//weapon->getParticleSystem()->emitParticles(true);
		}
		shootTimer = 0;
	}	
}
void FirstPersonController::onJoystickButton(const SDL_Event & event){
	if(shootTimer >= 10){
		//GameObject* bullet = createBullet();
		//bullet->getTransform()->setPosition(gameObject->getTransform()->getPosition() + 2 * aimDir);
		//static_cast<Bullet*>(bullet->getBehaviour())->setVelocity(aimDir);
		//TREngine::getInstance()->addGameObject(bullet);
		if(weapon){
			weapon->getParticleSystem()->emitParticles(true);
		}
		shootTimer = 0;
	}	
}
void FirstPersonController::onKeyboard(const SDL_KeyboardEvent & event){
	if (event.type == SDL_KEYDOWN){
		SDLKey keyPressed = event.keysym.sym;
		switch (keyPressed){
			case SDLK_UP: 
			case SDLK_w:
				velocity[0] = 1;
                break;
            case SDLK_DOWN: 
			case SDLK_s:
				velocity[0] = -1;
                break;
            case SDLK_RIGHT: 
			case SDLK_d:
				velocity[1] = 1;
                break;
            case SDLK_LEFT: 
			case SDLK_a:
				velocity[1] = -1;
                break;
			case SDLK_SPACE:
				if(!jumping){
					jumping = true;
					velocity[2] = 2;
				}
				break;
		}
	}else if (event.type == SDL_KEYUP){
		SDLKey keyPressed = event.keysym.sym;
		switch (keyPressed){
			case SDLK_UP: 
			case SDLK_w:
            case SDLK_DOWN: 
			case SDLK_s:
                velocity[0] = 0;
                break;
            case SDLK_RIGHT: 
			case SDLK_d:
            case SDLK_LEFT: 
			case SDLK_a:
				velocity[1] = 0;
                break;
		}
	}
	
}


void FirstPersonController::stayOnGround(const RayCastHit& hit, bool overSomething){
	Vec3f position = getGameObject().getTransform()->getWorldPosition();

	bool onSomething = false;

	float dist = 0;
	float trans = 0;
	if(overSomething){
		if(hit.collider->getType().getName() == "PlaneCollider"){
			PlaneCollider* sphere = static_cast<PlaneCollider*>(hit.collider);
			dist = position[2] - hit.intersection[2];
			trans = 1.5 - dist;
			onSomething = dist < 1.5 && hit.intersection[2] < position[2] ;
		}else {
			if(hit.collider->getType().getName() == "BoxCollider"){
				dist = position[2] - hit.collider->getGameObject()->getTransform()->getWorldPosition()[2];
				BoxCollider* cube = static_cast<BoxCollider*>(hit.collider);
				float size = 0.5f*cube->getSize()[2]*cube->getGameObject()->getTransform()->getScale()[2];
				onSomething = dist < size + 1.5;
				trans = size + 1.5f - dist;
			}
		}
	}
	if(getGameObject().getTransform()->getWorldPosition()[2] < 1.5 || onSomething){
		if(onSomething){
			getGameObject().getTransform()->translate(0,0,trans);
			velocity[2] = 0;
		}else{
			getGameObject().getTransform()->translate(0,0,1.5-position[2]);
			velocity[2] = 0;
		}
			
		jumping = false;
	}

}

void FirstPersonController::update(){
	shootTimer++;

	Transform * trans = getGameObject().getTransform();
	Vec3f position = trans->getWorldPosition();
	
	Ray ray;
	ray.origine = position;
	ray.direction = Vec3f(0,0,-1);
	RayCastHit hit;
	
	bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());

	//Move
	Vec3f groundNorm = Vec3f(0,0,1);
	if(overSomething){
		if(hit.collider->getType().getName()=="PlaneCollider"){
			if(hit.intersection[2] < position[2]){
				PlaneCollider* ground = static_cast<PlaneCollider*>(hit.collider);
				groundNorm = ground->getWorldNormal(); 
			}
		}
	}
	
	Vec3f translation = 2*Timer::deltaTime()*speed*
						(velocity[0]*normalize( head->getForward()-dot(head->getForward(),groundNorm)*groundNorm	)
					   - velocity[1]*head->getRight());
	trans->translate(translation);
	
	
	
	if( jumping ){
		//Gravity step
		trans->translate(0,0,Timer::deltaTime()*speed*velocity[2]);
		velocity[2] -= Timer::deltaTime()*5.8f;
		stayOnGround(hit, overSomething);
	}else if(overSomething){
		stayOnGround(hit, overSomething);
		if(hit.collider->getType().getName() == "PlaneCollider")
			if(position[2] - hit.intersection[2] > 2){
				jumping = true;
			}

	}
}
void FirstPersonController::onCollisionEnter(const CollisionHit& hit){

}
