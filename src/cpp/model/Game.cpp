#include <vector>
#include <memory>
#include <algorithm>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Errors.h"
#include "Entitys.h"
#include "StopWatch.h"

#include <iostream>

si::model::Game::Game () {

};

si::model::Game::Game (int x, int y) {
	if (x < 1) throw new WorldSizeTooSmallError();
	if (y < 1) throw new WorldSizeTooSmallError();

	this->worldSize = {x, y};
};

void si::model::Game::update () {
	int frames = this->stopWatch.getFrames();
	int calculatedFrames = frames;

	// This is safe because getFrames returns a number above or equal to 0
	while (frames--) {
		// ===== Add the entitys =====
		this->_handleAddObjects();

		// ===== Handle collisions =====
		this->_handleCollisions();

		// ===== Update all entitys =====
		for (auto& entity : this->objectPointers) {
			entity->update(this->stopWatch.getDeltaTime(), *this);
		}

		// ===== Remove objects =====
		this->_handleRemoveObjects();
	}

	// If in the time we calculated the frames we now have to do more frames
	// than we calculated then we are starting to lagg behind, it this gets
	// too bad we will have to adjust the deltaTime
	if (this->stopWatch.getFramesWithoutReset() > calculatedFrames) {
		this->_laggTimes++;
	} else {
		this->_laggTimes--;
		if (this->_laggTimes < 0) this->_laggTimes = 0;
	}

	// If we lagg behind 5 times, we will raise the deltaTime
	if (this->_laggTimes > 5) {
		this->stopWatch.setDeltaTime(this->stopWatch.getDeltaTime() * 2);
	}
}

void si::model::Game::_handleAddObjects () {
	for (auto entityPtr : this->addObjects) {
		// using vector for better readability
		auto& vec = this->objectPointers;

		if (std::find(vec.begin(), vec.end(), entityPtr) == vec.end()) {
			vec.push_back(entityPtr);
		}
	}

	this->addObjects.clear();
}

void si::model::Game::_handleRemoveObjects () {
	for (auto& entityPtr : this->deleteObjects) {
		// Delete it from the list

		auto& vec = this->objectPointers;
		vec.erase(
			std::remove(vec.begin(),
			            vec.end(),
			            this->getEntity(entityPtr)),
			vec.end()
		);
	}

	this->deleteObjects.clear();
}

void si::model::Game::_handleCollisions () {
	// If in the future the performance is a problem it is possible to
	// first contruct a spatial hashmap to reduce the amount of objects
	// we need to compare
	for (auto& entity1 : this->objectPointers) {
		sf::FloatRect bounds1 = entity1->sprite.getGlobalBounds();

		for (auto& entity2 : this->objectPointers) {
			// Don't compare with ourselves
			if (entity1 == entity2) break;

			sf::FloatRect bounds2 = entity2->sprite.getGlobalBounds();
			if (bounds1.intersects(bounds2)) {
				entity1->executeCollisionUsingMeOn(*entity2, *this);
			}
		}
	}
}

void si::model::Game::addEntity (std::shared_ptr< Entity > entityPtr) {
	this->addObjects.push_back(entityPtr);
}

void si::model::Game::removeEntity (Entity* entityPtr) {
	this->deleteObjects.push_back(entityPtr);
}

std::vector< std::shared_ptr< si::Entity >> si::model::Game::getObjects () {
	return this->objectPointers;
}

std::shared_ptr<si::Entity> si::model::Game::getEntity (si::Entity* entityPtr) {
	// Find the entity we want to remove
	for (auto& sharedEntityPtr : this->objectPointers) {

		// If they are the same
		if (sharedEntityPtr.get() == entityPtr) {

			return sharedEntityPtr;
		}
	}

	return std::shared_ptr<si::Entity>();
}

void si::model::Game::notifyObservers () {
	
};

void si::model::Game::clear () {

};

std::vector<int> si::model::Game::getWorldSize () {
	return {
		this->worldSize.at(0),
		this->worldSize.at(1)
	};
}