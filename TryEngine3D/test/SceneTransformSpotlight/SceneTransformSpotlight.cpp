#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"
#include "Rotator.h"
#include "WhippingSpot.h"
#include "trackballcamera.h"

#define FPS 100
#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

TrackBallCamera * pcamera;
GLSLShader* fragLitShader;
bool cam = true;

GameObject* createRotatingObject(BasicShapeEnum shape, ColorEnum color, float speed){
	GameObject* cubeObject1 = new GameObject();
    MeshRenderer* cube = new MeshRenderer();
	TriMesh* mesh = new TriMesh(shape);
	cube->setMesh(mesh);
    cube->setGameObject(cubeObject1);
    cubeObject1->setRenderer(cube);
    Material* redMat = new Material(color);
    cube->setMaterial(redMat);
	redMat->setShader(fragLitShader);
    Transform* trans1 = new Transform(Vec3f(0,0,0));
    cubeObject1->setTransform(trans1);
    trans1->setGameObject(cubeObject1);
	Rotator* rot1 = new Rotator(speed);
	rot1->setGameObject(cubeObject1);
	cubeObject1->setBehaviour(rot1);

	return cubeObject1;
}


int main(int argc, char *argv[])
{
//    freopen( "CON", "w", stdout );
 //   freopen( "CON", "w", stderr );

    SDL_Event event;
    const Uint32 time_per_frame = 1000/FPS;
    unsigned int width = LARGEUR_FENETRE;
    unsigned int height = HAUTEUR_FENETRE;

    Uint32 last_time,current_time,elapsed_time; //for time animation
    Uint32 start_time,stop_time; //for frame limit

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	glewInit();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(70,(double)width/height,0.001,1000);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);


	fragLitShader = new GLSLShader(std::string("assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag"));
    //SETUP OBJECT
    Scene scene;
    Transform worldTrans = Transform(Vec3f(0,0,0));
    scene.setRoot(&worldTrans);
	std::vector<Behaviour*> updateQueue;

	GameObject* cubeObject1 = createRotatingObject(CUBE,RED,1);
	updateQueue.push_back( cubeObject1->getBehaviour() );
	cubeObject1->getTransform()->translate(-1,-1,0);

	GameObject* cubeObject2 = createRotatingObject(SPHERE,YELLOW,1);
	updateQueue.push_back( cubeObject2->getBehaviour() );
	cubeObject2->getTransform()->translate(-1,1,0);

	GameObject* cubeObject3 = createRotatingObject(CUBE,BLUE,1);
	updateQueue.push_back( cubeObject3->getBehaviour() );
	cubeObject3->getTransform()->translate(1,1,0);

	GameObject* cubeObject4 = createRotatingObject(SPHERE,GREEN,1);
	updateQueue.push_back( cubeObject4->getBehaviour() );
	cubeObject4->getTransform()->translate(1,-1,0);

	GameObject* cubeObject5 = createRotatingObject(CUBE,WHITE,1);
	updateQueue.push_back( cubeObject4->getBehaviour() );
	cubeObject5->getTransform()->translate(0,0,2);


    Transform transP1 = Transform(Vec3f(0,0,0));

	transP1.addChild(cubeObject1->getTransform());
    transP1.addChild(cubeObject2->getTransform());
    transP1.addChild(cubeObject3->getTransform());
    transP1.addChild(cubeObject4->getTransform());
    transP1.addChild(cubeObject5->getTransform());

    worldTrans.addChild(&transP1);

	GameObject planeObject;
    MeshRenderer plane;
	TriMesh pmesh = TriMesh(PLANE);
	plane.setMesh(&pmesh);
	plane.setGameObject(&planeObject);
    planeObject.setRenderer(&plane);
    Material planeMat = Material(WHITE);


	planeMat.setShader(fragLitShader);


	plane.setMaterial(&planeMat);
    Transform transPlane = Transform(Vec3f(0,0,0));
    planeObject.setTransform(&transPlane);
    transPlane.setGameObject(&planeObject);
	transPlane.translate(0,0,-1);
	transPlane.scale(6,6,1);

	Texture* tex = RessourceManager::getInstance()->loadRessource<Texture>(std::string("assets/textures/tiles_ctf05r.jpg"));
	planeMat.setTexture(tex);

	GameObject* center = createRotatingObject(CUBE,RED,1);
	updateQueue.push_back( center->getBehaviour() );
	center->getTransform()->translate(0,0,5);

	GameObject* around = createRotatingObject(CUBE,GREEN,1);
	updateQueue.push_back( around->getBehaviour() );
	around->getTransform()->translate(5,0,0);
	center->getTransform()->addChild(around->getTransform());


	worldTrans.addChild(center->getTransform());
	worldTrans.addChild(&transPlane);

	GameObject lightObject0;
	Light light0 = Light(Vec4f(0.3f,0.3f,0.3f,0.3f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					LightManager::getInstance());
	Transform lightTransform0 = Transform(Vec3f(-4,-4,4));
	lightTransform0.setGameObject(&lightObject0);
	light0.setTransform(&lightTransform0);
	lightTransform0.lookAt(Vec3f(-1.5f,-1.5f,0));
	lightObject0.setTransform(&lightTransform0);
	scene.addLight(&light0);
	light0.setLightType(SPOTLIGHT);
	worldTrans.addChild(&lightTransform0);
	WhippingSpot whip1 = WhippingSpot(6,0.1f);
	whip1.setGameObject(&lightObject0);
	updateQueue.push_back(&whip1);

	Light light1 = Light(Vec4f(0.3f,0,0,1),
					Vec4f(0.8f,0,0,1),
					Vec4f(0.8f,0,0,1),
					LightManager::getInstance());
	GameObject lightObject1;
	Transform lightTransform1 = Transform(Vec3f(4,4,4));
	lightTransform1.setGameObject(&lightObject1);
	lightTransform1.lookAt(Vec3f(2,2,0));
	light1.setTransform(&lightTransform1);
	scene.addLight(&light1);
	light1.setLightType(SPOTLIGHT);
	lightObject1.setTransform(&lightTransform1);
	worldTrans.addChild(&lightTransform1);
	WhippingSpot whip2 = WhippingSpot(6,0.1f);
	whip2.setGameObject(&lightObject1);
	updateQueue.push_back(&whip2);

	Camera camera;
	GameObject cameraObject;
	camera.setGameObject(&cameraObject);
	Transform cameraTransform(Vec3f(6,6,6));
	cameraObject.setTransform(&cameraTransform);
	cameraTransform.setGameObject(&cameraObject);
	scene.setMainCamera(&camera);
	worldTrans.addChild(&cameraTransform);
	cameraTransform.lookAt(Vec3f(0,0,0));
	//cameraTransform.rotate(0,10,0);

	GameObject world;
	world.setTransform(&worldTrans);
	worldTrans.setGameObject(&world);

	Camera cam2(Screen::width/Screen::height,0.5,10,70);
	GameObject camObject2;
	Transform camTrans2(Vec3f(0,0,3));
	cam2.setGameObject(&camObject2);
	camObject2.setTransform(&camTrans2);
	camTrans2.setGameObject(&camObject2);

    pcamera = new TrackBallCamera(&cameraTransform);
    pcamera->setScrollSensivity(0.1);

	scene.updateRenderQueue();

	glPolygonMode(GL_FRONT,GL_FLAT);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);

    last_time = SDL_GetTicks();
    while(true)
    {
        start_time = SDL_GetTicks();
        SDL_PollEvent(&event);

        switch(event.type)
        {
            case SDL_QUIT:
            exit(0);
            break;
            case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                break;
                case SDLK_ESCAPE:
                exit(0);
                break;
				case SDLK_a:
					cam =! cam;
				break;
                default :;
                pcamera->OnKeyboard(event.key);
            }
            break;
            case SDL_MOUSEMOTION:
            pcamera->OnMouseMotion(event.motion);
            break;
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
            pcamera->OnMouseButton(event.button);
            break;
        }
		std::vector<Behaviour*>::iterator it = updateQueue.begin();
		for(; it != updateQueue.end(); ++it)
			(*it)->update();

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;

		static float fps = 0;
		static int nbFrames = 0;

		nbFrames++;
		if(nbFrames > 100){
			nbFrames = 0;
			std::cout<<"fps : "<<1000/(float)elapsed_time<<std::endl;
		}
		
        last_time = current_time;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
		pcamera->look(elapsed_time);
		
        scene.render();

		glFlush();
        SDL_GL_SwapBuffers();

        stop_time = SDL_GetTicks();
        if ((stop_time - last_time) < time_per_frame)
        {
            SDL_Delay(time_per_frame - (stop_time - last_time));
        }

    }

    return 0;
}


