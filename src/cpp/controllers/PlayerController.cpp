#include "PlayerController.h"
#include <SFML/Graphics.hpp>

si::controller::PlayerController::PlayerController (std::shared_ptr< si::Ship > target) {
	this->target = target;
}

void si::controller::PlayerController::update () {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->target->setThrustX(-0.004f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->target->setThrustX(0.004f);
	}

	// If both keys are pressed or none we dont want to thrust
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ==
	    sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->target->setThrustX(0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		this->target->fireing = true;
	} else {
		this->target->fireing = false;
	}
}