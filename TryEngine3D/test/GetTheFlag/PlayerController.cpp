#include "PlayerController.h"
#include "GravityObject.h"
#include "Bullet.h"

PlayerController::PlayerController(): joystick(NULL),velocity(0),speed(10.0f),aimDir(1,0,0),shootTimer(100),jumping(false)
{
	//getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + aimDir);
}


PlayerController::~PlayerController(void)
{
}

GameObject* createBullet(){
	GameObject* bullet = new GameObject();
	bullet->setName("Bullet");

	MeshRenderer* cube = new MeshRenderer();
    cube->setGameObject(bullet);
    bullet->setRenderer(cube);
    Material* redMat = new Material(BLACK);
    cube->setMaterial(redMat);

    Transform* trans1 = new Transform(Vec3f(0,0,0));
	trans1->scale(0.1f,0.1f,0.1f);
    bullet->setTransform(trans1);
    trans1->setGameObject(bullet);

	SphereCollider* ccollider = new SphereCollider();
	ccollider->setGameObject(bullet);
	bullet->setCollider(ccollider);

	Bullet* controller = new Bullet();
	controller->setGameObject(bullet);
	bullet->setBehaviour(controller);

	return bullet;
}

void PlayerController::onMouseMotion(const SDL_MouseMotionEvent & event){}
void PlayerController::onMouseButton(const SDL_Event & event){
	/*
	if(shootTimer >= 10){
		GameObject* bullet = createBullet();
		bullet->getTransform()->setPosition(gameObject->getTransform()->getPosition() + 2 * aimDir);
		static_cast<Bullet*>(bullet->getBehaviour())->setVelocity(aimDir);
		TREngine::getInstance()->addGameObject(bullet);
		shootTimer = 0;
	}
	*/
}
void PlayerController::onJoystickButton(const SDL_Event & event){
	if(shootTimer >= 10){
		GameObject* bullet = createBullet();
		bullet->getTransform()->setPosition(gameObject->getTransform()->getPosition() + 2 * aimDir);
		static_cast<Bullet*>(bullet->getBehaviour())->setVelocity(aimDir);
		TREngine::getInstance()->addGameObject(bullet);
		shootTimer = 0;
	}	
}
void PlayerController::onKeyboard(const SDL_KeyboardEvent & event){
	if (event.type == SDL_KEYDOWN){
		SDLKey keyPressed = event.keysym.sym;
		switch (keyPressed){
			case SDLK_UP: 
			case SDLK_w:
				velocity[0] = -1;
                break;
            case SDLK_DOWN: 
			case SDLK_s:
				velocity[0] = 1;
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
					getGameObject().getAnimation()->play("jump");
					jumping = true;
					velocity[2] = 9;
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
	
	if(abs(velocity[0]) > 0.1 || abs(velocity[1]) > 0.1){
		getGameObject().getAnimation()->fadeIn("walk");
		aimDir = Vec3f(velocity[0],velocity[1],0);
		getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + aimDir);
	}
	else{
		getGameObject().getAnimation()->fadeOut("walk");
		//getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + velocity);
	}

}

void PlayerController::handleJoystickDir(){
	float xAxis = (float)SDL_JoystickGetAxis(joystick, 1)/32000;
	float yAxis = (float)SDL_JoystickGetAxis(joystick, 0)/32000;

	velocity = Vec3f(xAxis,yAxis,0);
	if(length(velocity) > 0.1)
		velocity = normalize(velocity);

	xAxis = (float)SDL_JoystickGetAxis(joystick, 3)/32000;
	yAxis = (float)SDL_JoystickGetAxis(joystick, 2)/32000;

	Vec3f joyLook = Vec3f(xAxis,yAxis,0);
	if(length(joyLook) > 0.1){
		aimDir = normalize(joyLook);
		getGameObject().getTransform()->lookAt(getGameObject().getTransform()->getWorldPosition() + aimDir);
	}
}

void PlayerController::stayOnGround(){
	Vec3f position = getGameObject().getTransform()->getWorldPosition();

	Ray ray;
	ray.origine = position;
	ray.direction = Vec3f(0,0,-1);
	RayCastHit hit;
	bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());
	bool onSomething = false;

	float dist;
	float size;
	if(overSomething && (hit.collider != getGameObject().getCollider())){
		dist = position[2] - hit.collider->getGameObject()->getTransform()->getWorldPosition()[2];
		if(hit.collider->getType().getName() == "SphereCollider"){
			SphereCollider* sphere = static_cast<SphereCollider*>(hit.collider);
			size = 2*sphere->getRadius()*sphere->getGameObject()->getTransform()->getScale()[2];
			onSomething = dist < size;
		}else if(hit.collider->getType().getName() == "BoxCollider"){
			BoxCollider* cube = static_cast<BoxCollider*>(hit.collider);
			size = cube->getSize()[2]*cube->getGameObject()->getTransform()->getScale()[2];
			onSomething = position[2] < size;
			//size -= 1;
		}
	}
 
	if(getGameObject().getTransform()->getWorldPosition()[2] < 0 || onSomething){
		if(onSomething){
			getGameObject().getTransform()->translate(0,0,size-position[2]);
			velocity[2] = 0;
		}else{
			getGameObject().getTransform()->translate(0,0,-position[2]);
			velocity[2] = 0;
		}
			
		jumping = false;
	}

}

void PlayerController::update(){
	shootTimer++;
	
	if(joystick)
		handleJoystickDir();
	
	//Move
	Vec3f horizontalVelocity = Timer::deltaTime()*speed*velocity;
	horizontalVelocity[2] = 0;
	getGameObject().getTransform()->translate(horizontalVelocity);

	Vec3f position = getGameObject().getTransform()->getWorldPosition();
	if( jumping ){
		//Gravity step
		getGameObject().getTransform()->translate(0,0,Timer::deltaTime()*velocity[2]);
		velocity[2] -= Timer::deltaTime()*GravityObject::gravity;
		stayOnGround();
	}else if( position[2] > 1.5 ){
		Vec3f position = getGameObject().getTransform()->getWorldPosition();
		Ray ray;
		ray.origine = position;
		ray.direction = Vec3f(0,0,-1);
		RayCastHit hit;
		bool overSomething = TREngine::getInstance()->rayCast(ray,hit,getGameObject().getCollider());

		if(!overSomething){
			jumping = true;
		}else if(hit.collider->getType().getName()=="PlaneCollider")
			jumping = true;
	}


	if(getGameObject().getTransform()->getWorldPosition()[2] < 0 ){
		getGameObject().getTransform()->translate(0,0,-position[2]);
	}
}
void PlayerController::onCollisionEnter(){
}

void PlayerController::setJoystick(SDL_Joystick* joy){
	joystick = joy;
}
