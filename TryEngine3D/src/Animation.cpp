#include "Animation.h"
#include "Transform.h"


Animation::Animation(){
}


Animation::~Animation(){
	for(size_t i = 0; i < clips.size(); i++){
		delete this->clips[i];
	}
}

void Animation::addClip(AnimationClip* clip){
	clipsmap.insert( pair<string,AnimationClip*>(clip->name,clip) );
	clips.push_back(clipsmap[clip->name]);
	weights.push_back(1);
	startTimes.push_back(0);
}

void Animation::play(const string& clip){
	map<string,AnimationClip*>::iterator elt = clipsmap.find(clip);
	if( elt != clipsmap.end() )
		elt->second->playing = true;
}
void Animation::fadeIn(const string& clip){
	map<string,AnimationClip*>::iterator elt = clipsmap.find(clip);
	if( elt != clipsmap.end() )
		elt->second->fade = 1;
}
void Animation::fadeOut(const string& clip){
	map<string,AnimationClip*>::iterator elt = clipsmap.find(clip);
	if( elt != clipsmap.end() )
		elt->second->fade = -1;
}

void Animation::animate(float t){
	float sumWeights = 0;

	for(size_t i = 0; i < clips.size(); i++){
		
		if( clips[i]->playing ){
	
			if( clips[i]->fade != 0 ){
				weights[i] += (float)clips[i]->fade/10;
				if( weights[i] > 1){
					clips[i]->fade = 0;
					weights[i] = 1;
				}
				if( weights[i] < 0){
					clips[i]->fade = 0;
					weights[i] = 0;
				}
			}
			
			sumWeights += weights[i];
			KeyFrame* prevKey = clips[i]->current;
			KeyFrame* nextKey = NULL;
			if( clips[i]->current->next )
				nextKey = clips[i]->current->next;
			else{
				nextKey = clips[i]->first;
			}

			float animTime = t - startTimes[i];

			if( weights[i] != 0){			
				for(int j = 0; j < clips[i]->nbBones; j++){
					Vec3f interpolated = prevKey->rotations[j] + ((float)(animTime - prevKey->time)/(float)(nextKey->time - prevKey->time))*(nextKey->rotations[j] - prevKey->rotations[j]);
					blendedRotations[clips[i]->bones[j]] += weights[i]*interpolated;
				}
			}

			if( animTime > nextKey->time ){
				clips[i]->current = nextKey;
				if(!prevKey->next){
					clips[i]->playing = clips[i]->loop;
					startTimes[i] = t;
				}
			}
		}
	}

	map<Transform*,Vec3f>::iterator it = blendedRotations.begin();
	for(; it != blendedRotations.end(); ++it){
		(*it).first->setRotation((*it).second);
		(*it).second = Vec3f(0);
	}
}