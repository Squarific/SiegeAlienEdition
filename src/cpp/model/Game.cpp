#include <vector>
#include <memory>
#include "Game.h"
#include "Errors.h"
#include "Entitys.h"

si::model::Game::Game () {
	// TODO MOVE TO XML
	this->objectPointers.push_back(
		std::make_shared<Entity>(
			si::Ship("./assets/images/player.png")
		)
	);

	this->objectPointers.push_back(
		std::make_shared<Entity>(
			si::Ship("./assets/images/enemy.png")
		)
	);
};

si::model::Game::Game (std::vector<int> worldSize) {
	if (this->worldSize.size() < 2) throw BadWorldSizeException();

	this->worldSize = worldSize;
};

void si::model::Game::update () {

}

void si::model::Game::notifyObservers () {
	
};

