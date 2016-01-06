#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"

#define FPS 50

int main(int argc, char *argv[])
{
//    freopen( "CON", "w", stdout );
 //   freopen( "CON", "w", stderr );

    SDL_Event event;
    const Uint32 time_per_frame = 1000/FPS;

    Uint32 last_time,current_time,elapsed_time; //for time animation
    Uint32 start_time,stop_time; //for frame limit

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("SDL GL Application", NULL);
	SDL_SetVideoMode(Screen::width, Screen::height, 32, SDL_OPENGL);
	glewInit();
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
	gluPerspective(70,(double)Screen::width/Screen::height,1,1000);
	glViewport(0,0,Screen::width,Screen::height);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //SETUP OBJECT
    Scene scene;
    Transform worldTrans = Transform(Vec3f(0,0,0));
    scene.setRoot(&worldTrans);
	std::vector<Behaviour*> updateQueue;
	std::vector<Collider*> colliders;

    GameObject cubeObject1;
	cubeObject1.setName("red cube");
    CubeMeshRenderer cube;
    cube.setGameObject(&cubeObject1);
    cubeObject1.setRenderer(&cube);
    Material redMat = Material(RED);
    cube.setMaterial(&redMat);
    Transform trans1 = Transform(Vec3f(3,-1,0));
    cubeObject1.setTransform(&trans1);
    trans1.setGameObject(&cubeObject1);
	BoxCollider box1;
	cubeObject1.addComponent(&box1);
	box1.setGameObject(&cubeObject1);

    GameObject cubeObject2;
	cubeObject2.setName("yellow sphere");
    SphereMeshRenderer cube2;
    cube2.setGameObject(&cubeObject2);
    cubeObject2.setRenderer(&cube2);
    Material redMat2 = Material(YELLOW);
    cube2.setMaterial(&redMat2);
    Transform trans2 = Transform(Vec3f(-1,1,0));
    cubeObject2.setTransform(&trans2);
    trans2.setGameObject(&cubeObject2);
	SphereCollider box2;
	cubeObject2.addComponent(&box2);
	box2.setGameObject(&cubeObject2);

    GameObject cubeObject3;
	cubeObject3.setName("blue cube");
    CubeMeshRenderer cube3;
    cube3.setGameObject(&cubeObject3);
    cubeObject3.setRenderer(&cube3);
    Material redMat3 = Material(BLUE);
    cube3.setMaterial(&redMat3);
    Transform trans3 = Transform(Vec3f(1,1,0));
    cubeObject3.setTransform(&trans3);
    trans3.setGameObject(&cubeObject3);
	BoxCollider box3;
	cubeObject3.addComponent(&box3);
	box3.setGameObject(&cubeObject3);

    GameObject cubeObject4;
	cubeObject4.setName("green sphere");
    SphereMeshRenderer cube4;
    cube4.setGameObject(&cubeObject4);
    cubeObject4.setRenderer(&cube4);
    Material redMat4 = Material(GREEN);
    cube4.setMaterial(&redMat4);
    Transform trans4 = Transform(Vec3f(1,-1,0));
    cubeObject4.setTransform(&trans4);
    trans4.setGameObject(&cubeObject4);
	SphereCollider box4;
	cubeObject4.addComponent(&box4);
	box4.setGameObject(&cubeObject4);

    GameObject cubeObject5;
	cubeObject5.setName("white cube");
    CubeMeshRenderer cube5;
    cube5.setGameObject(&cubeObject5);
    cubeObject5.setRenderer(&cube5);
    Material redMat5 = Material(WHITE);
    cube5.setMaterial(&redMat5);
    Transform trans5 = Transform(Vec3f(0,0,2));
    cubeObject5.setTransform(&trans5);
    trans5.setGameObject(&cubeObject5);
	BoxCollider box5;
	cubeObject5.addComponent(&box5);
	box5.setGameObject(&cubeObject5);


    Transform transP1 = Transform(Vec3f(0,0,0));

    transP1.addChild(&trans1);
    transP1.addChild(&trans2);
    transP1.addChild(&trans3);
    transP1.addChild(&trans4);
    transP1.addChild(&trans5);

	colliders.push_back(&box1);
	colliders.push_back(&box2);
	colliders.push_back(&box3);
	colliders.push_back(&box4);
	colliders.push_back(&box5);

    worldTrans.addChild(&transP1);

	GameObject planeObject;
    PlaneMeshRenderer plane;
	plane.setGameObject(&planeObject);
    planeObject.setRenderer(&plane);
    Material planeMat = Material(WHITE);

	GLSLShader fragLitShader = GLSLShader(std::string("assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag"));
	planeMat.setShader(&fragLitShader);
	redMat.setShader(&fragLitShader);
	redMat2.setShader(&fragLitShader);
	redMat3.setShader(&fragLitShader);
	redMat4.setShader(&fragLitShader);
	redMat5.setShader(&fragLitShader);

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

	Camera camera(Screen::width/Screen::height,1,1000,70);
	GameObject cameraObject;
	cameraObject.setName("Main Camera");
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

	Camera cam2(Screen::width/Screen::height,1,10,70);
	GameObject camObject2;
	camObject2.setName("second camera");
	Transform camTrans2(Vec3f(-3,3,3));
	camTrans2.lookAt(Vec3f(0));
	cam2.setGameObject(&camObject2);
	camObject2.setTransform(&camTrans2);
	camTrans2.setGameObject(&camObject2);
	worldTrans.addChild(&camTrans2);

	GameObject debugCube;
	debugCube.setName("debug");
    SphereMeshRenderer cub;
    cub.setGameObject(&debugCube);
    debugCube.setRenderer(&cub);
    cub.setMaterial(&redMat2);
    Transform tran = Transform(Vec3f(0,0,2));
	tran.scale(Vec3f(0.1f));
	cameraTransform.addChild(&tran);
    debugCube.setTransform(&tran);
    tran.setGameObject(&debugCube);

	std::cout<<Camera::getMainCamera()->getGameObject()->getName()<<std::endl;
	scene.updateRenderQueue();

	glPolygonMode(GL_FRONT,GL_FLAT);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
	Ray ray;
	
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
                default :;
            }
            break;
            case SDL_MOUSEMOTION:
           
            break;
            case SDL_MOUSEBUTTONUP:
				ray = Camera::getMainCamera()->getWorldRayFromScreenPos(event.motion.x,event.motion.y);
				//std::cout<<"origine: "<<ray.origine<<"direction: "<<ray.direction<<std::endl;
				Vec3f Point = ray.direction;
				tran.setPosition(Point);
				//std::cout<<Point<<std::endl;

				std::vector<Collider*>::iterator it = colliders.begin();
				for(; it != colliders.end(); ++it){
					if( (*it)->rayCast(ray) ){
						std::cout<<(*it)->getGameObject()->getName()<<std::endl;
					}
				}  
             break;
        }
		std::vector<Behaviour*>::iterator it = updateQueue.begin();
		for(; it != updateQueue.end(); ++it)
			(*it)->update();

        current_time = SDL_GetTicks();
        elapsed_time = current_time - last_time;
        last_time = current_time;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
        scene.render();
		cam2.drawFrustum();
		Camera::getMainCamera()->drawFrustum();
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		Camera::getMainCamera()->getGameObject()->getTransform()->applyViewTransform();
		glBegin(GL_LINES);
		glVertex3fv(ray.origine.get());
		glVertex3fv((ray.origine + 10* ray.direction).get());
		glEnd();
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


