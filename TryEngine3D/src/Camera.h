#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Component.h"



enum CameraProjectionTypeEnum{
	ORTHOGRAPHIC,
	PERSPECTIVE
};

struct Ray;

/**
 *Base class for a Camera Component of a GameObject.
 *Used by the Scene server of the engine and accessible to the user for eg. ray-casting.
 */
class Camera: public Component{
	public :
		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		/**
		 *Static member to acces the camera from which the scene is renderer.
		 */
		static Camera* mainCamera;

		CameraProjectionTypeEnum projectionType;
		float aspectRatio;
		float fovy;
		float _near;
		float _far;

	public:
		Camera();
		Camera(float AspectRatio, float Near, float Far, float Fovy);
		~Camera();

		/**
		 *Draws a wireframe frustum. Used to debug.
		 */
		void drawFrustum()const;

		/**
		 *Get the camera from which the scene is rendered.
		 */
		static Camera* getMainCamera(){
			if(!mainCamera)
				std::cerr<<"Main Camera Not Set"<<std::endl;
			return mainCamera;
		}
		static void setMainCamera(Camera* cam){
			mainCamera = cam;
		}

		/**
		 *Construct a world space ray from a position on the screen.
		 */
		Ray getWorldRayFromScreenPos(int xScreen, int yScreen)const;

		/**
		 *Set the camera's projection matrix as OpenGL's projection matrix.
		 *Used internaly.
		 */
		void setProjectionMatrix()const;
};

#endif

