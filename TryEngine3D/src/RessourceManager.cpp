#include "RessourceManager.h"

RessourceManager* RessourceManager::instance = 0;

RessourceManager::RessourceManager():ressourceRegistery()
{
}


RessourceManager::~RessourceManager()
{
	RessourceManager::instance = 0;
}
