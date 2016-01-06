#ifndef LIGHTMANAGER_H_INCLUDED
#define LIGHTMANAGER_H_INCLUDED

#include <vector>

class Light;

class LightManager{
	private:
		static LightManager* instance;
		LightManager();
		~LightManager();

		int numberOfLights;
		int maxNumberOfLights;
		std::vector<Light*> lights;
		

	public:
		static LightManager* getInstance(){
			if(!instance)
				instance = new LightManager;

			return instance;
		};
		int getAvailableLightId();

		void shutDown(){
			delete this;
		}
};

#endif
