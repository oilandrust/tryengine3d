#include "ParticleSystem.h"
#include "includeGL.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"
#include <time.h>

const RTTI ParticleSystem::TYPE("ParticleSystem", &Renderable::TYPE);

ParticleSystem::ParticleSystem(){
	nbOfParts = 100;
	lifeTime = 100;
	emitting = false;
	positions = new Vec3f[nbOfParts];
	velocities = new Vec3f[nbOfParts];
	lifeTimes = new float[nbOfParts];
	position = Vec3f(0);

	srand( time(NULL) );

	for(int i = 0; i < nbOfParts; i++){
		velocities[i] = normalize(Vec3f(.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX));
		positions[i] = position;
		lifeTimes[i] = 0;
	}

}

ParticleSystem::~ParticleSystem(){
}

void ParticleSystem::emitParticles(bool oneshot){
	oneShot = oneshot;
	emitting = true;
	for(int i = 0; i < nbOfParts; i++){
		lifeTimes[i] = 0;
		velocities[i] = normalize(Vec3f(.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX));
		positions[i] = position;
	}
}

void ParticleSystem::simulate(){
	if(emitting){
		for(int i = 0; i < nbOfParts; i++){
			velocities[i] = velocities[i] - 0.00981*Vec3f(0,0,1);
			positions[i] = positions[i] + 0.1*velocities[i];
			lifeTimes[i]++;
			if(lifeTimes[i] > lifeTime){
				velocities[i] = Vec3f(.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX,.5f-(float)rand()/RAND_MAX);
				positions[i] = position;
				lifeTimes[i] = 0;
				if(oneShot)
					emitting = false;
			}
		}
	}
}

void ParticleSystem::render()const{
	if(emitting){
		Transform* camTrans = Camera::getMainCamera()->getGameObject()->getTransform();
		glUseProgram(0);
		for(int i = 0; i < nbOfParts; i++){
			glPushMatrix();
			glTranslatef(positions[i][0],positions[i][1],positions[i][2]);
			Vec3f view = normalize(camTrans->getWorldPosition() - gameObject->getTransform()->getWorldPosition() + positions[i]);
			Vec3f up = camTrans->getUp();
			Vec3f right = cross(up,view);
			up = cross(view,right);
		
			glMultMatrixf( Mat4x4f( Vec4f(view,0),
									Vec4f(up,0),
									Vec4f(right,0),
									Vec4f(0,0,0,1)
									).get()
						  );
			glScalef(.1f,.1f,.1f);

			glBegin(GL_TRIANGLE_STRIP);

				glTexCoord2f(0,0);
				glVertex3fv( Vec3f(0,-1,-1).get());
				glTexCoord2f(0,1);
				glVertex3fv(Vec3f(0,-1,1).get());
				glTexCoord2f(1,0);
				glVertex3fv(Vec3f(0,1,-1).get());
				glTexCoord2f(1,1);
				glVertex3fv(Vec3f(0,1,1).get());

			glEnd();
			glPopMatrix();
		}
	}
}