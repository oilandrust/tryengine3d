#ifndef TIME_H
#define TIMER_H

#include <SDL.h>

class Timer
{
	public:
		Timer();
		~Timer();

		static inline float deltaTime();
		static inline float time();

		void begginFrame();
		void endFrame();
		void delay();

	private:
		//const Uint32 time_per_frame = 1000/FPS;
		static float timeSinceStartup;
		static float deltatime;
		Uint32 last_time;
		Uint32 current_time;
		Uint32 elapsed_time; //for time animation
		Uint32 start_time;
		Uint32 stop_time; //for frame limit
		Uint32 time_per_frame;

};

inline float Timer::deltaTime(){
	return deltatime;
}

inline float Timer::time(){
	return timeSinceStartup;
}

#endif