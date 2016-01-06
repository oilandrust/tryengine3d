#ifndef THIRDPERSONAPP_H
#define THIRDPERSONAPP_H

#include "TryEngine.h"
#include "PlayerController.h"
#include "GravityObject.h"

class ThirdPersonApp
{
	protected:
		//Shared ressources
		shared_ptr<Animation> shAnim;
		shared_ptr<GLSLShader> shFragLitShaderTex;
		shared_ptr<GLSLShader> shFragLitShader;
		shared_ptr<TR3D::TriMesh> shPlaneMesh;
		shared_ptr<TR3D::TriMesh> shCubeMesh;
		shared_ptr<TR3D::TriMesh> shSphereMesh;

		Timer* timer;
		Light* globalLight;
		Camera* mainCamera;
	public:
		ThirdPersonApp();
		~ThirdPersonApp();
};

#endif