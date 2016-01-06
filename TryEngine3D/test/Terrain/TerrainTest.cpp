#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"
#include "FlyingCamera.h"

#define FPS 50

GameObject* createTerrain(){
    GameObject* terrain = new GameObject();
	terrain->setName("terrain");
	Terrain * terr = new Terrain();
    terr->setGameObject(terrain);
    terrain->setRenderer(terr);

	Transform* trans1 = new Transform(Vec3f(0,0,-1));
    terrain->setTransform(trans1);
    trans1->setGameObject(terrain);
	trans1->translate(-32,-32,0);
	//trans1->scale(0.01f,0.01f,1);

	Texture* tex = RessourceManager::getInstance()->loadRessource<Texture>("assets/textures/Heightmap_Example.jpg");
	terr->setHeightMap(tex);

	Texture* tex0 = RessourceManager::getInstance()->loadRessource<Texture>("assets/textures/grass.jpg");
	terr->setTexture(0,tex0);

	Texture* tex1 = RessourceManager::getInstance()->loadRessource<Texture>("assets/textures/texlocanyonjpg.jpg");
	terr->setTexture(1,tex1);

	Texture* tex2 = RessourceManager::getInstance()->loadRessource<Texture>("assets/textures/snow.jpg");
	terr->setTexture(2,tex2);
	
	Texture* alpha = RessourceManager::getInstance()->loadRessource<Texture>("assets/textures/AlphaMap_Example.jpg");
	terr->setAlphaMap(alpha);

	return terrain;
}

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
	
	FlyingCamera controler;
	cameraObject.setBehaviour(&controler);
	controler.setGameObject(&cameraObject);
	updateQueue.push_back(&controler);
	//cameraTransform.rotate(0,10,0);

	GameObject world;
	world.setTransform(&worldTrans);
	worldTrans.setGameObject(&world);

	std::cout<<Camera::getMainCamera()->getGameObject()->getName()<<std::endl;

	scene.addGameObject(createTerrain());

	scene.updateRenderQueue();

	glPolygonMode(GL_FRONT,GL_FLAT);
    glPolygonMode(GL_BACK,GL_LINE);
    glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);

    last_time = SDL_GetTicks();
    while(true)
    {
        start_time = SDL_GetTicks();
        if(SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
            exit(0);
            break;
            case SDL_KEYDOWN:
			case SDL_KEYUP:
			for(size_t i = 0; i < updateQueue.size(); i++)
				updateQueue[i]->onKeyboard((SDL_KeyboardEvent&)event);
            break;
            case SDL_MOUSEMOTION:
			for(size_t i = 0; i < updateQueue.size(); i++)
				updateQueue[i]->onMouseMotion(event.motion);
            break;
           
            break;
            case SDL_MOUSEBUTTONUP:
				
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


