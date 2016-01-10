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
			std::vector< Entity* > deleteObjects;

			// Used during updates
			void _handleAddObjects ();
			void _handleRemoveObjects();
			void _handleCollisions();
			void _handleFinish();

			// This is the amount of times we have used more times to calculate
			// the frames than the frames were long, this means we are going
			// to lagg behind more and more every frame, if this gets too big
			// we have to consider increasing the deltaTime
			int _laggTimes = 0;

		public:

			int level = 1;

			// Load the next xml level
			void nextLevel();
			void gameOver();

			Game();
			Game(int x, int y);

			// Update the world
			void update();

			// Clear the world
			void clear();

			std::vector<int> getWorldSize();

			// Add the given entity to the game at the beginning
			// of the next frame
			void addEntity (std::shared_ptr< Entity > entityPtr);

			// Remove the given entity from the game at the end
			// of the current or next update frame
			void removeEntity (Entity* entityPtr);

			// Returns a copy of the entitys that are within this
			// frame in the vector
			std::vector< std::shared_ptr< Entity > > getObjects();

			// Get the shared entity for a given normal entity pointer.
			// This can be used if you want to have a pointer that will get
			// memory managed for you. Entity will stay valid even if removed
			// from the game
			std::shared_ptr< Entity > getEntity (Entity* entityPtr);

			// Notify the observers that something about the subject changed
			virtual void notifyObservers();

			virtual void registerObserver(std::shared_ptr<si::Observer> observer);
		};
	}
}

#endif /* GAME_H */