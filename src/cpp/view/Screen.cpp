#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Errors.h"
#include "Game.h"

si::view::Screen::Screen () {
	// Trying to make a screen without a game is not defined
	throw NotEnoughArgumentsError();
}

si::view::Screen::Screen (si::model::Game* game) {
	this->game = game;

	std::vector<int> worldSize = this->game->getWorldSize();
	this->window = new sf::RenderWindow(
		sf::VideoMode(worldSize.at(0), worldSize.at(1)),
		"Space Invaders"
	);
}

void si::view::Screen::draw () {
	// Process the quit event, the others are done in a controller
	sf::Event event;
	while (this->window->pollEvent(event))
		if (event.type == sf::Event::Closed)
			this->window->close();

	// Set this window as the active openGl window
	this->window->setActive();
	this->window->clear();

	for (auto& obj : this->game->getObjects()) {
		obj->draw(this->window);
	}

	// End the frame and draw it all
	this->window->display();
}