#ifndef PARTICLASYSTEM_H
#define PARTICLASYSTEM_H

#include "Renderable.h"
#include "CGLA\Vec3f.h"
class Material;


using namespace CGLA;

class ParticleSystem:public Renderable{
	public:
		ParticleSystem();
		~ParticleSystem();

		void simulate();
		void render() const;
		void emitParticles(bool oneshot = true);

		void setPosition(const Vec3f& pos){
			position = pos;
		}

		Vec3f getPosition()const{
			return position;
		}
		Vec3f getWorldPosition()const{
			return position;
		}

		static const RTTI TYPE;
		virtual const RTTI& getType() const{ return TYPE; }

	protected:
		bool oneShot;
		bool emitting;
		Vec3f* positions;
		Vec3f* velocities;
		float* lifeTimes;
		float lifeTime;
		Material* material;
		int nbOfParts;
		Vec3f position;

	private:
		//Serialization
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version){
			// serialize base class information
			ar & boost::serialization::base_object<Renderable>(*this);
		}
};

#endif