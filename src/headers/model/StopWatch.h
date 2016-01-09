#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

namespace si {
	namespace model {

		typedef std::chrono::duration<double, std::milli> milliDuration;
		typedef std::chrono::time_point<std::chrono::system_clock> clocktime;

		class StopWatch {
		 	private:
		 		// Time since last frames
		 		clocktime _lastTime;

		 		// Time per frame
		 		// Should be > 0
				int _delta;

		 	public:
		 		

		 		/*
		 			int delta: The amount of time in one frame
		 			Defaults to 5ms if not provided
		 		*/
		 		StopWatch();
				StopWatch(int delta);
			
				/*
					Resets the internal times, as if you just created the stopwatch
				*/
				void Reset();

				/*
					Get the amount of frames since now and either the last time 
					getFrames was called or since Reset/Construction
				*/
				int getFrames();
		};
	}
}

#endif /* STOPWATCH_H */