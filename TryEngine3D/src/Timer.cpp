#include "Timer.h"

float Timer::deltatime = 0;
float Timer::timeSinceStartup = 0;

Timer::Timer(){
	last_time = SDL_GetTicks();
	time_per_frame = (Uint32)(1000/60);
}

Timer::~Timer()
{

}


void Timer::begginFrame(){
	start_time = SDL_GetTicks();
}

void Timer::endFrame(){
    current_time = SDL_GetTicks();
    elapsed_time = current_time - last_time;

	static float fps = 0;
	static int nbFrames = 0;

	deltatime = 0.001f*float(elapsed_time);
	timeSinceStartup += deltatime;

	nbFrames++;
	if(nbFrames > 100){
		nbFrames = 0;
		//std::cout<<"fps : "<<1000/(float)elapsed_time<<std::endl;
	}
	
    last_time = current_time;
}

void Timer::delay(){
    stop_time = SDL_GetTicks();
	
    if ((stop_time - last_time) < time_per_frame)
    {
        SDL_Delay(time_per_frame - (stop_time - last_time));
    }
	
}