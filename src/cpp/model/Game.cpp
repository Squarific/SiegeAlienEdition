#include <vector>
#include <memory>
#include <algorithm>

#include "Game.h"
#include "Errors.h"
#include "Entitys.h"
#include "StopWatch.h"

si::model::Game::Game () {
	// TODO MOVE TO XML
	this->addEntity(
		std::make_shared<Entity>(
			si::Ship("./assets/images/enemy.png")
		)
	);
};

si::model::Game::Game (int x, int y) {
	if (x < 1) throw new WorldSizeTooSmallError();
	if (y < 1) throw new WorldSizeTooSmallError();

	this->worldSize = {x, y};
};

void si::model::Game::update () {
	int frames = this->stopWatch.getFrames();
	int framesCopy = frames;

	// TODO WHAT IF UPDATE TAKES LONGER THAN DELTATIME

	// This is safe because getFrames returns a number above or equal to 0
	while (frames--) {
		// Add the entitys
		for (auto& entityPtr : this->addObjects) {
			// using vector for better readability
			auto vec = this->addObjects;
			if (std::find(vec.begin(), vec.end(), entityPtr) != vec.end()) {
				this->objectPointers.push_back(entityPtr);
			}
		}

		this->addObjects.clear();

		for (auto& entity : this->objectPointers) {
			// ===== Handle collisions =====


			// ===== Update all entitys =====
			entity->update(this->stopWatch.getDeltaTime(), *this);
		}

		// Remove objects
		for (auto& entityPtr : this->deleteObjects) {
			// using vector for better readability
			auto vec = this->addObjects;
			this->objectPointers.erase(
				std::remove(vec.begin(), vec.end(), entityPtr), vec.end()
			);
		}

		this->deleteObjects.clear();
	}
}

void si::model::Game::addEntity (std::shared_ptr< Entity > entityPtr) {
	this->addObjects.push_back(entityPtr);
}

void si::model::Game::removeEntity (std::shared_ptr< Entity > entityPtr) {
	this->deleteObjects.push_back(entityPtr);
}

std::vector< std::shared_ptr< si::Entity >> si::model::Game::getObjects () {
	return this->objectPointers;
}

void si::model::Game::notifyObservers () {
	
};

std::vector<int> si::model::Game::getWorldSize () {
	return {
		this->worldSize.at(0),
		this->worldSize.at(1)
	};
}