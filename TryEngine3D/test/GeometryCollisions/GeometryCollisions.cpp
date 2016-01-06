#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"
#include "trackballcamera.h"
#include "BouncingBall.h"

#define FPS 50
#define LARGEUR_FENETRE 640
#define HAUTEUR_FENETRE 480

TrackBallCamera * pcamera;
bool cam = true;


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

    //SETUP OBJECT
    Scene scene;
    Transform worldTrans = Transform(Vec3f(0,0,0));
    scene.setRoot(&worldTrans);
	std::vector<Behaviour*> updateQueue;


    GameObject SphereObject1;
    SphereMeshRenderer sphere1;
    sphere1.setGameObject(&SphereObject1);
    SphereObject1.setRenderer(&sphere1);
    Material redMat = Material(RED);
    sphere1.setMaterial(&redMat);
    Transform trans1 = Transform(Vec3f(-1,1,0));
    SphereObject1.setTransform(&trans1);
    trans1.setGameObject(&SphereObject1);
	SphereCollider col1;
	col1.setGameObject(&SphereObject1);
	BouncingBall beh1(3,0.1f);
	SphereObject1.setBehaviour(&beh1);
	beh1.setGameObject(&SphereObject1);
	updateQueue.push_back(&beh1);

    GameObject SphereObject2;
    SphereMeshRenderer sphere2;
    sphere2.setGameObject(&SphereObject2);
    SphereObject2.setRenderer(&sphere2);
    Material blueMat = Material(BLUE);
    sphere2.setMaterial(&blueMat);
    Transform trans2 = Transform(Vec3f(1,1,0));
    SphereObject2.setTransform(&trans2);
    trans2.setGameObject(&SphereObject2);
	SphereCollider col2;
	col2.setGameObject(&SphereObject2);
	BouncingBall beh2(3,0.1f);
	SphereObject2.setBehaviour(&beh2);
	beh2.setGameObject(&SphereObject2);
	updateQueue.push_back(&beh2);

	worldTrans.addChild(&trans1);
	worldTrans.addChild(&trans2);

	CollisionHandler collHandler;
	collHandler.addCollider(&col1);
	collHandler.addCollider(&col2);




	GameObject planeObject;
    PlaneMeshRenderer plane;
	plane.setGameObject(&planeObject);
    planeObject.setRenderer(&plane);
    Material planeMat = Material(WHITE);

	GLSLShader fragLitShader = GLSLShader(std::string("assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag"));
	planeMat.setShader(&fragLitShader);
    plane.setMaterial(&planeMat);
    Transform transPlane = Transform(Vec3f(0,0,0));
    planeObject.setTransform(&transPlane);
    transPlane.setGameObject(&planeObject);
	transPlane.translate(0,0,-1);
	transPlane.scale(6,6,1);
	transPlane.rotate(180,0,0);

	Texture tex(std::string("assets/textures/tiles_ctf05r.jpg"));
	planeMat.setTexture(&tex);

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
	light0.setLightType(DISTANTSOURCE);
	worldTrans.addChild(&lightTransform0);
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

    pcamera = new TrackBallCamera(&cameraTransform);
    pcamera->setScrollSensivity(0.1);
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

		collHandler.detectCollisions();

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        last_time = current_time;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
		pcamera->look(elapsed_time);
		
        scene.render();

        SDL_GL_SwapBuffers();

        stop_time = SDL_GetTicks();
        if ((stop_time - last_time) < time_per_frame)
        {
            SDL_Delay(time_per_frame - (stop_time - last_time));
        }

    }

    return 0;
}


