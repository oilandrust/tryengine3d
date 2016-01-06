#include <SDL.h>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include "TryEngine.h"
#include "trackballcamera.h"
#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/export.hpp>


using namespace std;
using namespace boost;
using namespace archive;


void saveGameObject(const GameObject &go, const char * filename){
    // make an archive
    std::ofstream ofs(filename);
    boost::archive::text_oarchive oa(ofs);
    oa << go;
}

void loadGameObject(GameObject &go, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    boost::archive::text_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> go;
}



int main(int argc, char *argv[])
{

	SDL_Event event;

    Uint32 last_time,current_time,elapsed_time; //for time animation
    Uint32 start_time,stop_time; //for frame limit

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("SDL GL Application", NULL);
	SDL_SetVideoMode(Screen::width, Screen::height, 32, SDL_OPENGL);


    //SETUP OBJECT
    GameObject testGO;
	testGO.setName("test GameObject");
	MeshRenderer testRenderer;
    testGO.setRenderer(&testRenderer);
	testRenderer.setGameObject(&testGO);
	testRenderer.setName("test Renderer");
    Material testMat = Material(RED);
    testRenderer.setMaterial(&testMat);
    Transform testTrans = Transform(Vec3f(3,-1,0));
	testTrans.setName("test transform");
    testGO.setTransform(&testTrans);
    testTrans.setGameObject(&testGO);

	cout<<"saving object"<<endl;
	std::string filename("test.go");
	saveGameObject(testGO,filename.c_str());

	cout<<"loading object"<<endl;
	
	GameObject loadedObject;
	try {
		// open the archive
		std::ifstream ifs(filename.c_str());
		boost::archive::text_iarchive ia(ifs);
		// restore the schedule from the archive
		ia >> loadedObject;
	}catch(archive_exception exp){
		   cout<<"SERIALIZATION EXCEPTION : "<<exp.what()<<endl;
	}

	cout<<"checking result"<<endl;
	Transform* loadedTrans = loadedObject.getTransform();
	if(!loadedTrans){
		cout<<"error null transform"<<endl;
		return 0;
	}
	MeshRenderer* loadedRenderer = static_cast<MeshRenderer*>(loadedObject.getRenderer());
	if(!loadedRenderer){
		cout<<"error null renderer"<<endl;
		return 0;
	}
	Material* loadedMat = loadedRenderer->getMaterial();
	if(!loadedRenderer){
		cout<<"error null material"<<endl;
		return 0;
	}

	assert(loadedTrans != NULL);
	assert(loadedRenderer != NULL);
	assert(loadedMat != NULL);

	std::cout<<"loaded object : \n"
			<<"name :"
			<<loadedObject.getName()
			<<"\n transform :"
			<<loadedTrans->getName()
			<<"\n renderer : "
			<<loadedRenderer->getName()
	<<std::endl;

	 //SETUP OBJECT
    GameObject testGO1;
	testGO1.setName("test cube GameObject");
	CubeMeshRenderer testRenderer1;
    testGO1.setRenderer(&testRenderer1);
	testRenderer1.setGameObject(&testGO1);
	testRenderer1.setName("test cube Renderer");
    Material testMat1 = Material(RED);
    testRenderer1.setMaterial(&testMat1);
    Transform testTrans1 = Transform(Vec3f(3,-1,0));
	testTrans1.setName("test cube transform");
    testGO1.setTransform(&testTrans1);
    testTrans1.setGameObject(&testGO1);

	std::string filename1("test.go");
	try {
		saveGameObject(testGO1,filename1.c_str());
	}catch(archive_exception exp){
		   cout<<"SERIALIZATION EXCEPTION : "<<exp.what()<<endl;
	}

	cout<<"loading object"<<endl;
	GameObject loadedObject1;
	try {
		// open the archive
		std::ifstream ifs1(filename1.c_str());
		boost::archive::text_iarchive ia1(ifs1);
		// restore the schedule from the archive
		ia1 >> loadedObject1;
	}catch(archive_exception exp){
		   cout<<"SERIALIZATION EXCEPTION : "<<exp.what()<<endl;
	}

	cout<<"checking result"<<endl;
	Transform* loadedTrans1 = loadedObject1.getTransform();
	if(!loadedTrans1){
		cout<<"error null transform"<<endl;
		return 0;
	}
	MeshRenderer* loadedRenderer1 = static_cast<MeshRenderer*>(loadedObject1.getRenderer());
	if(!loadedRenderer1){
		cout<<"error null renderer"<<endl;
		return 0;
	}
	Material* loadedMat1 = loadedRenderer1->getMaterial();
	if(!loadedRenderer1){
		cout<<"error null material"<<endl;
		return 0;
	}

	assert(loadedTrans1 != NULL);
	assert(loadedRenderer1 != NULL);
	assert(loadedMat1 != NULL);

	std::cout<<"loaded object : \n"
			<<"name :"
			<<loadedObject1.getName()
			<<"\n transform :"
			<<loadedTrans1->getName()
			<<"\n renderer : "
			<<loadedRenderer1->getName()
	<<std::endl;

	while(true)
    {
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

        }
    }



    return 0;
}


