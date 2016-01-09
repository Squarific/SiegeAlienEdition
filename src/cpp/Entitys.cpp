#include "Entitys.h"
#include "Game.h"
#include "Errors.h"

si::Entity::Entity () {
	this->applyTexture("assets/image/noimg.png");

	// This is probably unexpected behaviour as making an entity without sprite
	// makes little sens, so we'll throw an exception
	throw NoTextureArgument();
}

si::Entity::Entity (std::string textureFileName) {
	this->applyTexture(textureFileName);
}

si::Entity::Entity (const si::Entity& from) {
	this->applyTexture(from.textureFileName);
}

void si::Entity::applyTexture (std::string textureFileName) {
	if (!this->texture.loadFromFile(textureFileName))
		throw TextureFileException();

	this->textureFileName = textureFileName;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);

	sf::FloatRect bounds = this->sprite.getLocalBounds();
	// Rotation and position have the center as origin
	this->sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void si::Entity::draw (sf::RenderWindow* window) {
	this->sprite.setRotation(this->rotation);

	this->sprite.setPosition(
		sf::Vector2f(this->position.at(0), this->position.at(1))
	);

	window->draw(this->sprite);
}

void si::Entity::update (int deltaTime, si::model::Game& game) {

}

void si::Entity::collision (Entity& with) {

}

void si::Entity::setPosition (float x, float y) {
	this->position.at(0) = x;
	this->position.at(1) = y;
}

void si::Entity::setSpeed (float x, float y) {
	this->speed.at(0) = x;
	this->speed.at(1) = y;
}

si::Bullet::Bullet () {

}

si::Bullet::Bullet (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

si::Ship::Ship () {

}

si::Ship::Ship (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

void si::Ship::update (int deltaTime, si::model::Game& game) {
	// ===== SHIP MOVEMENT =====
	this->speed.at(0) += this->thrust.at(0) * this->thrustPower.at(0) * deltaTime;
	this->speed.at(1) += this->thrust.at(1) * this->thrustPower.at(1) * deltaTime;

	// Never let the ship go faster than the thrustpower
	this->speed.at(0) = std::min(this->speed.at(0), this->thrustPower.at(0));
	this->speed.at(1) = std::min(this->speed.at(1), this->thrustPower.at(1));
	this->speed.at(0) = std::max(this->speed.at(0), -this->thrustPower.at(0));
	this->speed.at(1) = std::max(this->speed.at(1), -this->thrustPower.at(1));

	this->position.at(0) += this->speed.at(0) * deltaTime;
	this->position.at(1) += this->speed.at(1) * deltaTime;

	// ===== WORLD BOUND CHECKS =====
	std::vector<int> worldSize = game.getWorldSize();
	if (this->position.at(0) < 0 || this->position.at(0) > worldSize.at(0)) {
		
	}

	// ===== BULLET FIREING =====
	this->msSinceLastBullet += deltaTime;

	if (this->fireing) {
		// TODO create bullet
		this->msSinceLastBullet -= this->fireSpeed;
	}

	if (this->msSinceLastBullet > this->fireSpeed)
		this->msSinceLastBullet = this->fireSpeed;
}

void si::Ship::setThrustX (float x) {
	this->thrust.at(0) = x;
}

void si::Ship::setThrustY (float y) {
	this->thrust.at(1) = y;
}

si::Wall::Wall () {

}

si::Wall::Wall (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}