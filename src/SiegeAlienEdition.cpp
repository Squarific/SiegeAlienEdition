#include "Game.h"
#include "Screen.h"

int main () {
	si::model::Game* mainGame = new si::model::Game();

	si::view::Screen screen(mainGame);

	si::controller::ControllerCollection controllerCollection();
	controllerCollection.controllers.push_back(std::make_shared(
		PlayerController();
	));

	// Run the game as long as our window is open
	while (screen.window->isOpen()) {
		mainGame->update();
		screen.draw();
	}
}