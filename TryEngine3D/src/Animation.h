#ifndef ANIMATION_H
#define ANIMATION_H

#include "Component.h"
#include "CGLA\Vec3f.h"
#include <vector>
#include <map>

using namespace CGLA;
using namespace std;

class Transform;

/**
 *A key frame structure. Implemented like a linked list.
 */
struct KeyFrame{
	float time;
	Vec3f* rotations;
	KeyFrame* next;

	KeyFrame():time(0),rotations(0),next(0){
	}
	
	~KeyFrame(){
		delete[] rotations;
		delete next;
	}
};

/**
 *An animation clip structure. Keeps state of the animation, 
 *pointers to first and current keyframe as well as a list of bones that are affected by the clip.
 */
struct AnimationClip{
	int fade;
	bool loop;
	bool playing;
	string name;
	KeyFrame* first;
	KeyFrame* current;
	int nbBones;
	Transform** bones;

	AnimationClip():first(0),current(0),nbBones(0),bones(0){
	}

	~AnimationClip(){
		delete first;
		delete[] bones;
	}
};

/**
 *An Animation class structure Operating on the Tranform nodes of the scene graph. 
 *Responsible for interpolationg the bones's rotations, playing and blending animation clips.
 */
class Animation: public Component{
	public:
		Animation();
		~Animation();
	
		/**
		*User function to add a clip to the animation
		*/
		void addClip(AnimationClip* clip);

		/**
		*User function to start playing an animation clip.
		*/
		void play(const string& clip);
		void pause();

		/**
		*User function to start fading in an animation clip. 
		*/
		void fadeIn(const string& clip);
		/**
		*User function to start fading out an animation clip. 
		*/
		void fadeOut(const string& clip);

		/**
		*Function called by the engine to set the pose to the pose at time t. 
		*/
		void animate(float t);
	protected:	
		bool playing;

		/**
		*Pointers to the clips. 
		*/
		vector<AnimationClip*> clips;
		/**
		*Map to acces to the clips. 
		*/
		map<string,AnimationClip*> clipsmap;

		/**
		*Weights associated to each clip. Used internaly to blend animations.
		*/
		vector<float> weights;

		/**
		*The time at which each clip has started. Used internaly transfom the games current time to the range of the clip.
		*/
		vector<float> startTimes;
		/**
		*A map to used internaly to associate blended rotations to bones.
		*/
		map<Transform*,Vec3f> blendedRotations;
		

};

#endif
