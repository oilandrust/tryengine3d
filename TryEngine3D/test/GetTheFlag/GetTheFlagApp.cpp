#include "GetTheFlagApp.h"

GetTheFlagApp::GetTheFlagApp():
groundMat(0),
boxMat(0),
metalBoxMat(0),
playerMat(0),
globalLight(0),
mainCamera(0)
{
}

GetTheFlagApp::~GetTheFlagApp(){
	delete globalLight;
	delete mainCamera;
}

void GetTheFlagApp::setupApp(){
	//CREATE SHARED OBJECTS
	this->shFragLitShaderTex.reset( new GLSLShader(string("./assets/shaders/"),std::string("fragment_lit_tex.vert"),std::string("fragment_lit_tex.frag")) );
	this->shFragLitShader.reset( new GLSLShader(string("./assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag")) );
	this->shPlaneMesh.reset( new TriMesh(PLANE) );
	this->shCubeMesh.reset( new TriMesh(CUBE) );
	this->shSphereMesh.reset( new TriMesh(SPHERE) );
	
	//SCENEGRAPH ROOT
	Transform* worldTrans = new Transform(Vec3f(0,0,0));
	GameObject* world = new GameObject();
	world->setName("root");
	world->setTransform(worldTrans);
	worldTrans->setGameObject(world);

	scene->setRoot(worldTrans);

		//Setup the world
	this->trEngine->addGameObject(createPlayer());
	this->setupWorld();
	
}

void GetTheFlagApp::close(){
	//RELEASE RESSOURCES
	RessourceManager::getInstance()->releaseRessources();
	shFragLitShaderTex.reset();
	shFragLitShader.reset();
	shPlaneMesh.reset();
	shCubeMesh.reset();
	shSphereMesh.reset();
}

GameObject* GetTheFlagApp::createPlane(){
	GameObject* planeObject = new GameObject();
	planeObject->setName("plane");

	Transform* transPlane = new Transform(Vec3f(0,0,0));
    planeObject->setTransform(transPlane);
    transPlane->setGameObject(planeObject);
	transPlane->translate(0,0,-1);
	transPlane->scale(6,6,1);
	
	MeshRenderer* plane = new MeshRenderer();
	plane->setReceiveShadow(true);
	plane->setGameObject(planeObject);
	plane->setMesh(shPlaneMesh);

	planeObject->setRenderer(plane);

	if(!groundMat){
		groundMat = new Material(WHITE);
		groundMat->setShader(shFragLitShaderTex);
		
		shared_ptr<Texture> tex = RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/tiles_ctf05r.jpg");
		groundMat->setTexture(tex);
	}
	plane->setMaterial(groundMat);

	return planeObject;
}

GameObject* GetTheFlagApp::createCube(){
    GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("cube");
	Transform* trans1 = new Transform(Vec3f(-1,-1,0));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);


	MeshRenderer* cube = new MeshRenderer();
	cube->setMesh(shCubeMesh);
    cube->setGameObject(cubeObject1);
    cubeObject1->setRenderer(cube);
	cube->setCastShadow(true);
	cube->setReceiveShadow(true);

	if(!boxMat){
		boxMat = new Material(WHITE);
		shared_ptr<Texture> tex = RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/wood.jpg");
		boxMat->setTexture(tex);
		boxMat->setShader(shFragLitShaderTex);
	}
	cube->setMaterial(boxMat);

	//COLLIDER
	SphereCollider * collider = new SphereCollider();
	collider->setGameObject(cubeObject1);
	cubeObject1->setCollider(collider);
	collider->isStatic(false);

	//PHYSICS
	GravityObject* grav = new GravityObject();
	cubeObject1->setBehaviour(grav);
	grav->setGameObject(cubeObject1);

	return cubeObject1;
}
GameObject* GetTheFlagApp::createStaticCube(){
    GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("staticcube");
	Transform* trans1 = new Transform(Vec3f(-1,-1,0));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);

	MeshRenderer* cube = new MeshRenderer();
	cube->setMesh(shCubeMesh);
	cube->setCastShadow(true);
	cube->setReceiveShadow(true);
    cube->setGameObject(cubeObject1);
    cubeObject1->setRenderer(cube);


	if(!metalBoxMat){
		metalBoxMat = new Material(WHITE);
		shared_ptr<Texture> tex = RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/metal091.jpg");
		metalBoxMat->setTexture(tex);
		metalBoxMat->setShader(shFragLitShaderTex);
	}
	cube->setMaterial(metalBoxMat);

	SphereCollider * collider = new SphereCollider();
	collider->setGameObject(cubeObject1);
	cubeObject1->setCollider(collider);
	collider->isStatic(true);


	return cubeObject1;
}



void GetTheFlagApp::setupWorld(){	
	
	GameObject* cube = createCube();
	cube->getTransform()->translate(4,0,0);
	TREngine::getInstance()->addGameObject(cube);

	cube = createCube();
	cube->getTransform()->translate(-5,3,0);
	TREngine::getInstance()->addGameObject(cube);
	cube = createCube();
	cube->getTransform()->translate(2,-2,0);
	TREngine::getInstance()->addGameObject(cube);
	
	cube = createStaticCube();
	cube->getTransform()->translate(2,2,0);
	TREngine::getInstance()->addGameObject(cube);
	cube = createCube();
	cube->getTransform()->translate(2,2,2);
	TREngine::getInstance()->addGameObject(cube);
	cube = createStaticCube();
	cube->getTransform()->translate(5,4,0);
	TREngine::getInstance()->addGameObject(cube);
	cube = createStaticCube();
	cube->getTransform()->translate(-2,2,0);
	TREngine::getInstance()->addGameObject(cube);
	
	cube = createCube();
	cube->getTransform()->translate(-4.5,-3,5);
	TREngine::getInstance()->addGameObject(cube);

	cube = createStaticCube();
	cube->getTransform()->translate(-4,-4,1.5);
	cube->getTransform()->scale(Vec3f(2.5));
	delete cube->getCollider();
	BoxCollider* collider = new BoxCollider();
	collider->setGameObject(cube);
	cube->setCollider(collider);
	TREngine::getInstance()->addGameObject(cube);


	GameObject* plane = createPlane();
	plane->getTransform()->translate(6,6,0);
	TREngine::getInstance()->addGameObject(plane);
	plane = createPlane();
	plane->getTransform()->translate(6,-6,0);
	TREngine::getInstance()->addGameObject(plane);
	plane = createPlane();
	plane->getTransform()->translate(-6,6,0);
	TREngine::getInstance()->addGameObject(plane);
	plane = createPlane();
	plane->getTransform()->translate(-6,-6,0);
	TREngine::getInstance()->addGameObject(plane);
		
	GameObject* lightObject0 = new GameObject();
	lightObject0->setName("light");
	globalLight = new Light(Vec4f(0.3f,0.3f,0.3f,0.3f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					LightManager::getInstance());

	Transform* lightTransform0 = new Transform(Vec3f(-10,0,15));
	lightTransform0->setGameObject(lightObject0);
	globalLight->setTransform(lightTransform0);
	lightTransform0->lookAt(Vec3f(0,0,0));
	lightObject0->setTransform(lightTransform0);
	scene->addLight(globalLight);
	globalLight->setLightType(POINTSOURCE);
	scene->getRoot()->addChild(lightTransform0);

	mainCamera = new Camera(Screen::width/Screen::height,2,100,80);
	Camera::setMainCamera(mainCamera);
	GameObject* cameraObject = new GameObject();
	cameraObject->setName("camera");
	mainCamera->setGameObject(cameraObject);
	Transform* cameraTransform = new Transform(Vec3f(10,0,15));
	cameraObject->setTransform(cameraTransform);
	cameraTransform->setGameObject(cameraObject);
	scene->setMainCamera(mainCamera);
	scene->getRoot()->addChild(cameraTransform);
	cameraTransform->lookAt(Vec3f(0,0,0));
}


GameObject* GetTheFlagApp::createLeg(const string& name){
	//GAME OBJECT+TRANSFORM
	GameObject* LLeg = new GameObject();
	LLeg->setName(name);
	Transform* tran = new Transform();
	LLeg->setTransform(tran);
	tran->setGameObject(LLeg);


	MeshRenderer* rend = new MeshRenderer();
	rend->setReceiveShadow(true);
	rend->setCastShadow(true);
	rend->setMesh(shSphereMesh);
	LLeg->setRenderer(rend);
	rend->setGameObject(LLeg);
	
	if(!playerMat){
		playerMat = new Material(GREEN);
		playerMat->setShader(shFragLitShader);
	}
	rend->setMaterial(playerMat);

	GameObject* LLLeg = new GameObject();
	LLLeg->setName("LLLeg");
	
	MeshRenderer* rende = new MeshRenderer();
	rende->setMesh(shCubeMesh);
	rende->setCastShadow(true);
	rende->setReceiveShadow(true);
	Transform* tra = new Transform();
	LLLeg->setTransform(tra);
	tra->setGameObject(LLLeg);
	LLLeg->setRenderer(rende);
	rende->setGameObject(LLLeg);

	rende->setMaterial(playerMat);

	tra->translate(0,-1,0);
	tra->scale(Vec3f(.5f,2,.5f));
	tran->addChild(tra);

	tran->scale(Vec3f(.5f));

	return LLeg;
}

GameObject* GetTheFlagApp::createPlayer(){
	GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("Player");
	Transform* trans1 = new Transform(Vec3f(5,5,0));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);
	//Camera::getMainCamera()->getGameObject()->getTransform()->translate((Vec3f(5,5,0)));

	GameObject* body = new GameObject();
	body->setName("body");
	Transform* bodyTrans = new Transform(Vec3f(0,1.6f,0));
	body->setTransform(bodyTrans);
	bodyTrans->setGameObject(body);
	trans1->addChild(bodyTrans);

	GameObject* torso = new GameObject();
	torso->setName("torso");
	MeshRenderer* cube = new MeshRenderer();
	
	cube->setMesh(shCubeMesh);
	cube->setReceiveShadow(true);
	cube->setCastShadow(true);
    cube->setGameObject(torso);
    torso->setRenderer(cube);
    
	if(!playerMat){
		playerMat = new Material(GREEN);
		playerMat->setShader(shFragLitShader);
	}

	playerMat->setShader(shFragLitShader);
    cube->setMaterial(playerMat);
	Transform* ttrans = new Transform();
	ttrans->setGameObject(torso);
	torso->setTransform(ttrans);
	ttrans->scale(.6f,1,.6f);
	bodyTrans->addChild(ttrans);

	SphereCollider* coll = new SphereCollider(); 
	cubeObject1->setCollider(coll);
	coll->setGameObject(cubeObject1);
	coll->isStatic(false);

	GameObject* LLeg = createLeg("LLeg");
	LLeg->getTransform()->translate(.6f,-1,0);
	GameObject* LTibias = createLeg("LTibias");
	LTibias->getTransform()->scale(Vec3f(2));
	LTibias->getTransform()->scale(Vec3f(.8f));
	LTibias->getTransform()->translate(0,-3,0);
	LLeg->getTransform()->addChild(LTibias->getTransform());
	bodyTrans->addChild(LLeg->getTransform());

	GameObject* RLeg = createLeg("RLeg");
	RLeg->getTransform()->translate(-.6f,-1,0);
	GameObject* RTibias = createLeg("RTibias");
	RTibias->getTransform()->scale(Vec3f(2));
	RTibias->getTransform()->scale(Vec3f(.8f));
	RTibias->getTransform()->translate(0,-3,0);
	RLeg->getTransform()->addChild(RTibias->getTransform());
	bodyTrans->addChild(RLeg->getTransform());

	GameObject* LArm = createLeg("LArm");
	LArm->getTransform()->scale(Vec3f(.8f));
	LArm->getTransform()->translate(1,1,0);
	bodyTrans->addChild(LArm->getTransform());

	GameObject* RArm = createLeg("RArm");
	RArm->getTransform()->scale(Vec3f(.8f));
	RArm->getTransform()->translate(-1,1,0);
	bodyTrans->addChild(RArm->getTransform());


	GameObject* cubeObject2 = new GameObject();
	cubeObject2->setName("head");
	MeshRenderer* cube2 = new MeshRenderer();
	cube2->setReceiveShadow(true);
	cube2->setCastShadow(true);
	
	cube2->setMesh(shSphereMesh);
    cube2->setGameObject(cubeObject2);
    cubeObject2->setRenderer(cube2);
  
    cube2->setMaterial(playerMat);
    Transform* trans2 = new Transform(Vec3f(0,1.5,0));
	trans2->scale(0.6f,0.6f,0.6f);
    cubeObject2->setTransform(trans2);
    trans2->setGameObject(cubeObject2);

	bodyTrans->addChild(trans2);

	bodyTrans->scale(Vec3f(.7f));

	PlayerController * controller = new PlayerController();
	cubeObject1->setBehaviour(controller);
	controller->setGameObject(cubeObject1);

	//*****************Animation
	shAnim.reset(new Animation());
	AnimationClip* lclip = new AnimationClip();
	lclip->name = "walk";
	lclip->playing = true;
	lclip->loop = true;
	lclip->nbBones = 6;
	lclip->fade = -1;
	lclip->bones = new Transform*[lclip->nbBones];
	lclip->bones[0] = LLeg->getTransform();
	lclip->bones[1] = RLeg->getTransform();
	lclip->bones[2] = LArm->getTransform();
	lclip->bones[3] = RArm->getTransform();
	lclip->bones[4] = LTibias->getTransform();
	lclip->bones[5] = RTibias->getTransform();

	KeyFrame* key0l = new KeyFrame();
	key0l->rotations = new Vec3f[lclip->nbBones];
	//left leg
	key0l->rotations[0] = Vec3f(0,0,0);
	key0l->rotations[4] = Vec3f(0,0,0);
	//right leg
	key0l->rotations[1] = Vec3f(-70,0,0);
	key0l->rotations[5] = Vec3f(70,0,0);
	//arms
	key0l->rotations[2] = Vec3f(0,0,0);
	key0l->rotations[3] = Vec3f(50,0,0);
	key0l->time = 0;

	KeyFrame* key1l = new KeyFrame();
	key1l->rotations = new Vec3f[lclip->nbBones];
	key1l->rotations[0] = Vec3f(70,0,0);
	key1l->rotations[4] = Vec3f(0,0,0);
	key1l->rotations[1] = Vec3f(-70,0,0);
	key1l->rotations[5] = Vec3f(0,0,0);
	key1l->rotations[2] = Vec3f(-50,0,0);
	key1l->rotations[3] = Vec3f(50,0,0);
	key1l->time = 0.25f;

	KeyFrame* key2l = new KeyFrame();
	key2l->rotations = new Vec3f[lclip->nbBones];
	key2l->rotations[0] = Vec3f(-70,0,0);
	key2l->rotations[4] = Vec3f(70,0,0);
	key2l->rotations[1] = Vec3f(0,0,0);
	key2l->rotations[5] = Vec3f(0,0,0);
	key2l->rotations[2] = Vec3f(50,0,0);
	key2l->rotations[3] = Vec3f(0,0,0);
	key2l->time = 0.5f;

	KeyFrame* key3l = new KeyFrame();
	key3l->rotations = new Vec3f[lclip->nbBones];
	key3l->rotations[0] = Vec3f(-70,0,0);
	key3l->rotations[4] = Vec3f(0,0,0);
	key3l->rotations[1] = Vec3f(70,0,0);
	key3l->rotations[5] = Vec3f(0,0,0);
	key3l->rotations[2] = Vec3f(50,0,0);
	key3l->rotations[3] = Vec3f(-50,0,0);
	key3l->time = 0.75f;

	KeyFrame* key4l = new KeyFrame();
	key4l->rotations = new Vec3f[lclip->nbBones];
	//left leg
	key4l->rotations[0] = Vec3f(0,0,0);
	key4l->rotations[4] = Vec3f(0,0,0);
	//right leg
	key4l->rotations[1] = Vec3f(-70,0,0);
	key4l->rotations[5] = Vec3f(70,0,0);
	//arms
	key4l->rotations[2] = Vec3f(0,0,0);
	key4l->rotations[3] = Vec3f(50,0,0);
	key4l->time = 1;


	key0l->next = key1l;
	key1l->next = key2l;
	key2l->next = key3l;
	key3l->next = key4l;
	lclip->first = key0l;
	lclip->current = key0l;
	shAnim->addClip(lclip);


	AnimationClip* jclip = new AnimationClip();
	jclip->name = "jump";
	jclip->nbBones = 6;
	jclip->loop = false;
	jclip->playing = false;
	jclip->fade = 0;
	jclip->bones = new Transform*[jclip->nbBones];
	jclip->bones[0] = LLeg->getTransform();
	jclip->bones[1] = RLeg->getTransform();
	jclip->bones[2] = LArm->getTransform();
	jclip->bones[3] = RArm->getTransform();
	jclip->bones[4] = LTibias->getTransform();
	jclip->bones[5] = RTibias->getTransform();

	KeyFrame* key0 = new KeyFrame();
	key0->rotations = new Vec3f[jclip->nbBones];
	//left leg
	key0->rotations[0] = Vec3f(-20,0,0);
	key0->rotations[4] = Vec3f(20,0,0);
	//right leg
	key0->rotations[1] = Vec3f(20,0,0);
	key0->rotations[5] = Vec3f(20,0,0);
	//arms
	key0->rotations[2] = Vec3f(0,0,0);
	key0->rotations[3] = Vec3f(50,0,0);
	key0->time = 0;

	KeyFrame* key1 = new KeyFrame();
	key1->rotations = new Vec3f[jclip->nbBones];
	key1->rotations[0] = Vec3f(20,0,0);
	key1->rotations[4] = Vec3f(0,0,0);
	key1->rotations[1] = Vec3f(-30,0,0);
	key1->rotations[5] = Vec3f(30,0,0);
	key1->rotations[2] = Vec3f(-50,0,0);
	key1->rotations[3] = Vec3f(50,0,0);
	key1->time = 0.25f;

	KeyFrame* key2 = new KeyFrame();
	key2->rotations = new Vec3f[jclip->nbBones];
	key2->rotations[0] = Vec3f(40,0,0);
	key2->rotations[4] = Vec3f(10,0,0);
	key2->rotations[1] = Vec3f(-40,0,0);
	key2->rotations[5] = Vec3f(10,0,0);
	key2->rotations[2] = Vec3f(50,0,0);
	key2->rotations[3] = Vec3f(0,0,0);
	key2->time = 0.5f;

	KeyFrame* key3 = new KeyFrame();
	key3->rotations = new Vec3f[jclip->nbBones];
	key3->rotations[0] = Vec3f(-30,0,0);
	key3->rotations[4] = Vec3f(30,0,0);
	key3->rotations[1] = Vec3f(30,0,0);
	key3->rotations[5] = Vec3f(30,0,0);
	key3->rotations[2] = Vec3f(50,0,0);
	key3->rotations[3] = Vec3f(-50,0,0);
	key3->time = 0.75f;

	KeyFrame* key4 = new KeyFrame();
	key4->rotations = new Vec3f[jclip->nbBones];
	//left leg
	key4->rotations[0] = Vec3f(-20,0,0);
	key4->rotations[4] = Vec3f(20,0,0);
	//right leg
	key4->rotations[1] = Vec3f(20,0,0);
	key4->rotations[5] = Vec3f(20,0,0);
	//arms
	key4->rotations[2] = Vec3f(0,0,0);
	key4->time = 1;
	
	key0->next = key1;
	key1->next = key2;
	key2->next = key3;
	key3->next = key4;
	jclip->first = key0;
	jclip->current = key0;
	shAnim->addClip(jclip);

	shAnim->setGameObject(cubeObject1);
	cubeObject1->setAnimation(shAnim);

	this->animations->push_back(shAnim);

	cout<<"anim initialized"<<endl;

	cubeObject1->getTransform()->lookAt(Vec3f(0));
	
	scene->addGameObject(cubeObject1);
	return cubeObject1;
}



