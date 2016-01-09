#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Entitys.h"
#include "Observers.h"
#include "StopWatch.h"

namespace si {
	namespace model {
		class Game : Observable {
		private:
			std::vector<int> worldSize = {1024, 786};
			si::model::StopWatch stopWatch;

			// Objects currently in the game
			std::vector< std::shared_ptr< Entity > > objectPointers;

			// Objects to be added at the start of the next frame
			std::vector< std::shared_ptr< Entity > > addObjects;

			// Objects to be deleted at the end of the current frame or if not
			// currently inside a frame, at the end of the next frame
			std::vector< std::shared_ptr< Entity > > deleteObjects;

		public:

			Game();
			Game(int x, int y);

			// Update the world
			void update();

			std::vector<int> getWorldSize();

			// Add the given entity to the game at the beginning
			// of the next frame
			void addEntity (std::shared_ptr< Entity > entityPtr);

			// Remove the given entity from the game at the end
			// of the current or next update frame
			void removeEntity (std::shared_ptr< Entity > entityPtr);

			// Returns a copy of the entitys that are within this
			// frame in the vector
			std::vector< std::shared_ptr< Entity >> getObjects();

			// Notify the observers that something about the subject changed
			virtual void notifyObservers();
		};
	}
}

#endif /* GAME_H */