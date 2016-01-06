#include "LightManager.h"

LightManager* LightManager::instance = NULL;

LightManager::LightManager(void){
	maxNumberOfLights = 8;
	numberOfLights = 0;
}

LightManager::~LightManager(void)
{
	LightManager::instance = 0;
}

int LightManager::getAvailableLightId(){
	if(numberOfLights < maxNumberOfLights){
		++numberOfLights;
		return numberOfLights;
	}else
		return -1;
}
