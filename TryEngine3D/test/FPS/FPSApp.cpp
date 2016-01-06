#include "FPSApp.h"
#include <sstream>

FPSApp::FPSApp():
wallMat(0),
groundMat(0),
boxMat(0),
metalBoxMat(0),
stairMat(0)
{
}

FPSApp::~FPSApp(){
}

void FPSApp::setupApp(){
	//CREATE SHARED OBJECTS
	this->fragLitShader.reset( new GLSLShader(string("./assets/shaders/"),std::string("fragment_lit_tex.vert"),std::string("fragment_lit_tex.frag")) );
	this->fragLitShaderNoTex.reset( new GLSLShader(string("./assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag")) );
	this->planeMesh.reset( new TriMesh(PLANE) );
	this->cubeMesh.reset( new TriMesh(CUBE) );
	this->stairMesh.reset( new TriMesh() );
	stairMesh->load("./assets/models/stairs.obj");

	//Setup scene graph root
	Transform* worldTrans = new Transform(Vec3f(0,0,0));
	GameObject* world = new GameObject();
	world->setName("root");
	world->setTransform(worldTrans);
	scene->setRoot(worldTrans);

	this->trEngine->addGameObject(createPlayer());

	//Setup the world
	this->setupWorld();
	
}

void FPSApp::close(){
	//RELEASE RESSOURCES
	RessourceManager::getInstance()->releaseRessources();
	fragLitShaderNoTex.reset();
	fragLitShader.reset();
	planeMesh.reset();
	cubeMesh.reset();
	stairMesh.reset();
}


GameObject* FPSApp::createPlane(){
	GameObject* planeObject = new GameObject();
	planeObject->setName("plane");
	MeshRenderer* plane = new MeshRenderer();
	
	plane->setMesh(planeMesh);
	plane->setReceiveShadow(true);
	plane->setGameObject(planeObject);
    planeObject->setRenderer(plane);

	if(!groundMat){
		groundMat = new Material(WHITE);
		groundMat->setShader(fragLitShader);
		groundMat->setTexture(RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/tiles_ctf05r.jpg"));
	}

	plane->setMaterial(groundMat);
    Transform* transPlane = new Transform(Vec3f(0,0,0));
    planeObject->setTransform(transPlane);
    transPlane->setGameObject(planeObject);
	transPlane->scale(6,6,1);
	
	return planeObject;
}

GameObject* FPSApp::createWall(int dir){
	GameObject* planeObject = new GameObject();
	planeObject->setName("plane");
	MeshRenderer* plane = new MeshRenderer();
	
	plane->setMesh(planeMesh);
	plane->setReceiveShadow(true);
	plane->setGameObject(planeObject);
    planeObject->setRenderer(plane);
	if(!wallMat){
		wallMat = new Material(WHITE);
		wallMat->setTexture(RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/Wall.jpg"));
		wallMat->setShader(fragLitShader);
	}
	plane->setMaterial(wallMat);

	
		PlaneCollider* coll = new PlaneCollider();
	coll->isStatic(true);
	planeObject->setCollider(coll);
	coll->setGameObject(planeObject);

	float x,y;
	if(dir == 0){
		x = -6;
		y = -0;
	}else if(dir == 1){
		x = 0;
		y = -6;
	}else if(dir == 2){
		x = 6;
		y = 0;
	}else if(dir == 3){
		x = 0;
		y = 6;
	}

	
    Transform* transPlane = new Transform(Vec3f(x,y,3));
    planeObject->setTransform(transPlane);
	transPlane->setGameObject(planeObject);

	float z = 0;
	if(dir == 1){
		y = -90;
		x = -90;
		transPlane->rotate(Vec3f(x,y,z));
	}else if(dir == 0){
		y = 90;
		x = 0;
		transPlane->rotate(Vec3f(x,y,z));
	}else if(dir == 3){
		y = -90;
		x = 90;
		transPlane->rotate(Vec3f(x,y,z));
	}else if(dir == 2){
		y = -90;
		x = 0;
		//z = 180;
		transPlane->rotate(Vec3f(x,y,z));
	}
	
	transPlane->scale(3,6,1);
	
	return planeObject;
}

GameObject* FPSApp::createRamp(){
	GameObject* planeObject = new GameObject();
	planeObject->setName("stairs");
	MeshRenderer* plane = new MeshRenderer();
	plane->setReceiveShadow(true);

	plane->setMesh(stairMesh);
	plane->setGameObject(planeObject);
    planeObject->setRenderer(plane);

	if(!stairMat){
		stairMat = new Material(WHITE);
		stairMat->setShader(fragLitShaderNoTex);
	}
	plane->setMaterial(stairMat);

    Transform* transPlane = new Transform(Vec3f(0,0,3));
    planeObject->setTransform(transPlane);
    transPlane->setGameObject(planeObject);
	

	PlaneCollider* coll = new PlaneCollider(Vec3f(0),normalize(Vec3f(0,-1,2)),Vec2f(6,6.5));
	planeObject->setCollider(coll);
	coll->setGameObject(planeObject);



	return planeObject;
}

GameObject* FPSApp::createCube(){
    GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("cube");
	MeshRenderer* cube = new MeshRenderer();

	TriMesh* mesh = new TriMesh(CUBE);
	cube->setMesh(cubeMesh);

    cube->setGameObject(cubeObject1);
    cubeObject1->setRenderer(cube);
    
    
	cube->setCastShadow(true);
	cube->setReceiveShadow(true);
    Transform* trans1 = new Transform(Vec3f(0,0,1));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);

	if(!boxMat){
		boxMat = new Material(WHITE);
		boxMat->setTexture(RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/wood.jpg"));
		boxMat->setShader(fragLitShader);
	}
	cube->setMaterial(boxMat);

	BoxCollider * collider = new BoxCollider();
	collider->setGameObject(cubeObject1);
	cubeObject1->setCollider(collider);
	collider->isStatic(false);

	GravityObject* behav = new GravityObject();

	cubeObject1->setBehaviour(behav);
	behav->setGameObject(cubeObject1);


	return cubeObject1;
}
GameObject* FPSApp::createStaticCube(){
    GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("cube");
	MeshRenderer* cube = new MeshRenderer();

	TriMesh* mesh = new TriMesh(CUBE);
	cube->setMesh(cubeMesh);
	cube->setCastShadow(true);
	cube->setReceiveShadow(true);

    cube->setGameObject(cubeObject1);
    cubeObject1->setRenderer(cube);
    
    Transform* trans1 = new Transform(Vec3f(0,0,1));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);

	if(!metalBoxMat){
		metalBoxMat = new Material(WHITE);
		metalBoxMat->setTexture(RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/metal091.jpg"));
		metalBoxMat->setShader(fragLitShader);
	}
	 cube->setMaterial(metalBoxMat);

	BoxCollider * collider = new BoxCollider();
	collider->setGameObject(cubeObject1);
	cubeObject1->setCollider(collider);
	collider->isStatic(true);
	
	return cubeObject1;
}

void FPSApp::setupWorld(){

	/*************STATIC CUBES*************/
	GameObject* cube = createStaticCube();
	cube->getTransform()->translate(2,2,0.5f);
	cube->getTransform()->scale(1.5f,1.5f,1.5f);
	TREngine::getInstance()->addGameObject(cube);

	cube = createStaticCube();
	cube->getTransform()->translate(5,4,0.5f);
	cube->getTransform()->scale(1.5f,1.5f,1.5f);
	TREngine::getInstance()->addGameObject(cube);

	cube = createStaticCube();
	cube->getTransform()->translate(-2,2,0.5f);
	cube->getTransform()->scale(1.5f,1.5f,1.5f);
	TREngine::getInstance()->addGameObject(cube);
	
	cube = createStaticCube();
	cube->getTransform()->translate(-4,-4,1.5);
	cube->getTransform()->scale(Vec3f(2.5));
	delete cube->getCollider();
	BoxCollider* collider = new BoxCollider();
	collider->setGameObject(cube);
	cube->setCollider(collider);
	TREngine::getInstance()->addGameObject(cube);
	/*************STATIC CUBES*************/
	

	/*************MOVING CUBES*************
	cube = createCube();
	cube->getTransform()->translate(4,0,0);
	TREngine::getInstance()->addGameObject(cube);
	
	cube = createCube();
	cube->getTransform()->translate(-5,3,0);
	TREngine::getInstance()->addGameObject(cube);
	
	cube = createCube();
	cube->getTransform()->translate(2,-2,0);
	TREngine::getInstance()->addGameObject(cube);

	cube = createCube();
	cube->getTransform()->translate(2,2,1);
	TREngine::getInstance()->addGameObject(cube);

	cube = createCube();
	cube->getTransform()->translate(-4.5,-3,4.5f);
	TREngine::getInstance()->addGameObject(cube);
	/*************MOVING CUBES*************/

	
	GameObject* plane;
	
	shared_ptr<Texture> map = RessourceManager::getInstance()->loadRessource<Texture>("./assets/textures/testMap.png");
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			Vec3f color = Vec3f(map->getPixel(i,j));
			
			if(color[0] > 250){
				plane = createPlane();
				string name = "downPlane ";
				std::stringstream out;
				out << i <<" "<< j;
				name += out.str();
				plane->setName(name);
				plane->getTransform()->translate(-30+12*i,-30+12*j,0);
				PlaneCollider* collide = new PlaneCollider();
				plane->setCollider(collide);
				collide->setGameObject(plane);
				TREngine::getInstance()->addGameObject(plane);
			}else if(color[1] > 250){
				plane = createPlane();
				string name = "upPlane ";
				std::stringstream out;
				out << i <<" "<< j;
				name += out.str();
				plane->setName(name);
				plane->getTransform()->translate(-30+12*i,-30+12*j,6);
				PlaneCollider* collide = new PlaneCollider();
				plane->setCollider(collide);
				collide->setGameObject(plane);
				TREngine::getInstance()->addGameObject(plane);
			}else if(color[2] > 250){
				plane = createRamp();
				string name = "Ramp ";
				std::stringstream out;
				out << i <<" "<< j;
				name += out.str();
				plane->setName(name);
				plane->getTransform()->translate(-30+12*i,-30+12*j,0);
				if(color[0] > 100)
					plane->getTransform()->rotate(Vec3f(0,0,180));
				TREngine::getInstance()->addGameObject(plane);
			}
		}
	}
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 6; j++){
			plane = createWall(i);
			string name = "Wall"+i;
			plane->setName(name);
			float x,y;
			if(i == 0){
				x = -30;
				y = -30+12*j;
			}else if(i == 1){
				x = -30+12*j;
				y = -30;
			}else if(i == 2){
				x = 30;
				y = -30+12*j;
			}else if(i == 3){
				x = -30+12*j;
				y = 30;
			}
			plane->getTransform()->translate(x,y,6);
			TREngine::getInstance()->addGameObject(plane);
		}
	}
	for(int i = 0; i < 4; i++){
		//if(i == 1 )
		for(int j = 0; j < 4; j++){
			plane = createWall(i);
			string name = "Wall ";
			std::stringstream out;
			out << i <<" "<< j;
			name += out.str();
	
			plane->setName(name);
			float x,y;
			if(i == 0){
				x = -18;
				y = -18+12*j;
			}else if(i == 1){
				x = -18+12*j;
				y = -18;
			}else if(i == 2){
				x = 18;
				y = -18+12*j;
			}else if(i == 3){
				x = -18+12*j;
				y = 18;
			}
			plane->getTransform()->translate(x,y,0);
				
			TREngine::getInstance()->addGameObject(plane);
		}
	}

	GameObject* lightObject0 = new GameObject();
	lightObject0->setName("light");
	Light* light0 = new Light(Vec4f(0.3f,0.3f,0.3f,0.3f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					LightManager::getInstance());

	Transform* lightTransform0 = new Transform(Vec3f(-10,0,15));
	lightTransform0->setGameObject(lightObject0);
	light0->setTransform(lightTransform0);
	lightTransform0->lookAt(Vec3f(0,0,0));
	lightObject0->setTransform(lightTransform0);
	scene->addLight(light0);
	light0->setLightType(POINTSOURCE);
	scene->getRoot()->addChild(lightTransform0);

}


GameObject* FPSApp::createPlayer(){
	GameObject* cubeObject1 = new GameObject();
	cubeObject1->setName("Player");
	Transform* trans1 = new Transform(Vec3f(7,7,1));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);
	
	FirstPersonController* controller = new FirstPersonController();
	cubeObject1->setBehaviour(controller);
	controller->setGameObject(cubeObject1);
	
	SphereCollider* coll = new SphereCollider(); 
	coll->setRadius(1.5f);
	cubeObject1->setCollider(coll);
	coll->setGameObject(cubeObject1);
	coll->isStatic(false);
	
	GameObject* head = new GameObject();
	head->setName("head"); 
	Transform* headTrans = new Transform(Vec3f(0,0,2));
	head->setTransform(headTrans);
	headTrans->setGameObject(head);
	headTrans->lookAt(Vec3f(1,1,0));
	Camera* camera = new Camera(Screen::width/Screen::height,2,100,80);
	Camera::setMainCamera(camera);
	camera->setGameObject(head);
	trans1->addChild(headTrans);

	headTrans->rotate(90,0,0);
	controller->setHead(headTrans);

	GameObject* weapon = new GameObject();
	Transform* weapTrans = new Transform();
	weapon->setTransform(weapTrans);
	weapTrans->setGameObject(weapon);
	MeshRenderer* weapRend = new MeshRenderer();
	weapRend->setMesh(RessourceManager::getInstance()->loadRessource<TR3D::TriMesh>("assets/models/ak47.obj"));
	weapon->setRenderer(weapRend);
	weapRend->setGameObject(weapon);
	Material* planeMat = new Material(WHITE);
	weapRend->setMaterial(planeMat);
	headTrans->addChild(weapTrans);
	weapTrans->translate(.7f,-.7f,0);
	//weapTrans->rotate(0,180,0);
	//weapTrans->scale(.08f,.08f,.08f);
	controller->setWeapon(weapon);

	
	return cubeObject1;
}




