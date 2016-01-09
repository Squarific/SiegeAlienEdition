#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "Entitys.h"
#include "Observers.h"

namespace si {
	namespace model {
		class Game : Observable {
		public:
			std::vector<int> worldSize = {400, 800};
			std::vector< std::shared_ptr< Entity > > objectPointers;

			Game();
			Game(std::vector<int> worldSize);

			void update();

			// Notify the observers that something about the subject changed
			virtual void notifyObservers();
		};
	}
}

#endif /* GAME_H */