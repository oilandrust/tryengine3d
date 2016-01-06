#ifndef TRYENGINE_H_INCLUDED
#define TRYENGINE_H_INCLUDED

#include <Windows.h>
#include <WinGDI.h>
#include <GL/glew.h>
#include <gl/gl.h>

//CORE
#include "Object.h"
#include "Component.h"
#include "GameObject.h"
#include "Transform.h"
#include "GameObjectFactory.h"
#include "Behaviour.h"
#include "Serialization.h"
#include "RessourceManager.h"
#include "Timer.h"

//RENDER
#include "Screen.h"
#include "Scene.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "Light.h"
#include "LightManager.h"
#include "Texture.h"
#include "Camera.h"
#include "GLSLShader.h"
#include "TriMesh.h"
#include "Terrain.h"
#include "ParticleSystem.h"

//ANIM
#include "Animation.h"

//COLLISIONS
#include "CollisionHandler.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include "BoxCollider.h"


using namespace TR3D;

//STL
#include <iostream>

#endif // TRYENGINE_H_INCLUDED
