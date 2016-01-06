#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"
#include "trackballcamera.h"

#define FPS 50

TrackBallCamera * pcamera;
bool cam = true;

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
	if (!glewGetExtension("GL_ARB_vertex_buffer_object"))
		cout<<"VBO not supported"<<endl;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
	//glOrtho(-10,10,-10,10,-10,10);
	gluPerspective(70,(double)Screen::width/Screen::height,1,50);
	glViewport(0,0,Screen::width,Screen::height);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //SETUP OBJECT
    Scene scene;
    Transform worldTrans = Transform(Vec3f(0,0,0));
    scene.setRoot(&worldTrans);
	std::vector<Behaviour*> updateQueue;

	GameObject cubeObject5;
	MeshRenderer cube5;
	TriMesh mesh5(CUBE);
	cube5.setMesh(&mesh5);
	cube5.setGameObject(&cubeObject5);
	cube5.setReceiveShadow(true);
	cube5.setCastShadow(true);
    cubeObject5.setRenderer(&cube5);
    Material redMat5 = Material(WHITE);
    cube5.setMaterial(&redMat5);
    Transform trans5 = Transform(Vec3f(3,-3,0));
    cubeObject5.setTransform(&trans5);
    trans5.setGameObject(&cubeObject5);

	GameObject meshObject;
	meshObject.setName("cow");
	MeshRenderer meshRend;
	meshRend.setReceiveShadow(true);
    meshRend.setGameObject(&meshObject);
    meshObject.setRenderer(&meshRend);
	meshRend.setCastShadow(true);
    meshRend.setMaterial(&redMat5);
	TriMesh mesh(std::string("assets/models/cow.obj"));
	meshRend.setMesh(&mesh);
    Transform transMesh = Transform(Vec3f(0,1,0.7f));
    meshObject.setTransform(&transMesh);
    transMesh.setGameObject(&meshObject);
	transMesh.rotate(Vec3f(90,0,0));
	transMesh.scale(0.5f,0.5f,0.5f);
	
	worldTrans.addChild(&transMesh);
	worldTrans.addChild(&trans5);

	GameObject planeObject;
	planeObject.setName("plane");
    PlaneMeshRenderer plane;
	plane.setGameObject(&planeObject);
    planeObject.setRenderer(&plane);
	plane.setReceiveShadow(true);
    Material planeMat = Material(WHITE);

	GLSLShader fragLitShader = GLSLShader(std::string("assets/shaders/"),std::string("fragment_lit.vert"),std::string("fragment_lit.frag"));
	planeMat.setShader(&fragLitShader);

	redMat5.setShader(&fragLitShader);

	plane.setMaterial(&planeMat);
	plane.setCastShadow(false);
    Transform transPlane = Transform(Vec3f(0,0,0));
    planeObject.setTransform(&transPlane);
    transPlane.setGameObject(&planeObject);
	transPlane.translate(0,0,-1);
	transPlane.scale(6,6,1);
	transPlane.rotate(Vec3f(180,0,0));

	Texture tex(std::string("assets/textures/tiles_ctf05r.jpg"));
	planeMat.setTexture(&tex);

	worldTrans.addChild(&transPlane);

	Camera camera(Screen::width/Screen::height,1,50,70);
	GameObject cameraObject;
	cameraObject.setName("Main Camera");
	camera.setGameObject(&cameraObject);
	Transform cameraTransform(Vec3f(6,6,6));
	cameraObject.setTransform(&cameraTransform);
	cameraTransform.setGameObject(&cameraObject);
	scene.setMainCamera(&camera);
	worldTrans.addChild(&cameraTransform);
	cameraTransform.lookAt(Vec3f(0,0,0));

	GameObject LightObj;
	Light light0 = Light(Vec4f(0.3f,0.3f,0.3f,0.3f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					Vec4f(0.8f,0.8f,0.8f,0.8f),
					LightManager::getInstance());
	Transform lightTrans = Transform(Vec3f(0,6,6));
	//lightTrans.scale(0.2f,0.2f,0.2f);
	lightTrans.lookAt(Vec3f(0,0,0));
	LightObj.setTransform(&lightTrans);
	light0.setTransform(&lightTrans);
	lightTrans.setGameObject(&LightObj);
	scene.addLight(&light0);
	light0.setLightType(POINTSOURCE);


	GameObject sphereObj;
	sphereObj.setName("sphere");
	Transform sphereTrans;
	sphereTrans.setGameObject(&sphereObj);
	sphereObj.setTransform(&sphereTrans);
	SphereMeshRenderer sphere;
	Material yellowMat(YELLOW);
	sphere.setMaterial(&yellowMat);
	sphere.setGameObject(&sphereObj);
	sphereObj.setRenderer(&sphere);
	lightTrans.addChild(&sphereTrans);
	sphereTrans.scale(Vec3f(0.3f));

	worldTrans.addChild(&lightTrans);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1,0,0);
	Mat4x4f test;
	Transform t(Vec3f(1,0,0));
	glGetFloatv(GL_MODELVIEW_MATRIX,test.get());

	GameObject world;
	world.setTransform(&worldTrans);
	worldTrans.setGameObject(&world);

	std::cout<<Camera::getMainCamera()->getGameObject()->getName()<<std::endl;
	pcamera = new TrackBallCamera(&cameraTransform);
    pcamera->setScrollSensivity(0.1);

	glPolygonMode(GL_FRONT,GL_FLAT);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_CULL_FACE);

	scene.updateRenderQueue();

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
        last_time = current_time;

		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		
        scene.render();
		Camera::getMainCamera()->drawFrustum();
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity( );
		pcamera->look(elapsed_time);
		//Camera::getMainCamera()->getGameObject()->getTransform()->applyCameraTransform();
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


