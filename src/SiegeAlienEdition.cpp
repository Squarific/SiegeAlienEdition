#include "Game.h"
#include "Entitys.h"
#include "Screen.h"
#include "PlayerController.h"
#include "ControllerCollection.h"

int main () {
	si::model::Game* mainGame = new si::model::Game();

	si::Ship* playerShip = new si::Ship("./assets/images/player.png");
	std::shared_ptr<si::Ship> player = std::shared_ptr<si::Ship>(playerShip);
	player->setPosition(0, 700);
	mainGame->addEntity(player);

	si::view::Screen screen(mainGame);

	si::controller::ControllerCollection controllerCollection = 
		si::controller::ControllerCollection();

	std::shared_ptr<si::controller::Controller> playerController = 
		std::shared_ptr<si::controller::Controller>(
			new si::controller::PlayerController(player));

	controllerCollection.controllers.push_back(playerController);

	// Run the game as long as our window is open
	while (screen.window->isOpen()) {
		controllerCollection.update();
		mainGame->update();
		screen.draw();
	}
}