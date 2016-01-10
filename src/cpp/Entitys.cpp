#include "Entitys.h"
#include "Game.h"
#include "Errors.h"

#include <iostream>

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

void si::Entity::executeCollisionUsingMeOn (si::EntityBase& with, si::model::Game& game) {
	with.collision(*this, game);
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
	window->draw(this->sprite);
}

void si::Entity::update (int deltaTime, si::model::Game& game) {
	this->position.at(0) += this->speed.at(0) * deltaTime;
	this->position.at(1) += this->speed.at(1) * deltaTime;

	sf::FloatRect bounds = this->sprite.getLocalBounds();
	std::vector<int> worldSize = game.getWorldSize();

	if (this->position.at(0) + bounds.width < 0 ||
		this->position.at(0) - bounds.width > worldSize.at(0) ||
		this->position.at(1) + bounds.height < 0 ||
		this->position.at(1) - bounds.height > worldSize.at(1)) {
		game.removeEntity(this);
	}

	// ===== UPDATE THE SPRITE =====
	this->sprite.setRotation(this->rotation);

	this->sprite.setPosition(
		sf::Vector2f(this->position.at(0), this->position.at(1))
	);
}

void si::Entity::setPosition (float x, float y) {
	this->position.at(0) = x;
	this->position.at(1) = y;
}

void si::Entity::setSpeed (float x, float y) {
	this->speed.at(0) = x;
	this->speed.at(1) = y;
}

void si::Entity::setRotation (float rotation) {
	this->rotation = rotation;
}

si::Bullet::Bullet () {

}

si::Bullet::Bullet (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

void si::Bullet::executeCollisionUsingMeOn (si::EntityBase& with, si::model::Game& game) {
	with.collision(*this, game);
}

void si::Bullet::setOwner (Entity* owner) {
	this->_owner = owner;
}

bool si::Bullet::isOwner (Entity* owner) {
	return this->_owner == owner;
}

si::Ship::Ship () {

}

si::Ship::Ship (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

void si::Ship::executeCollisionUsingMeOn (si::EntityBase& with, si::model::Game& game) {
	with.collision(*this, game);
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
		game.removeEntity(this);
	}

	if (this->position.at(1) < 0 || this->position.at(1) > worldSize.at(1)) {
		game.removeEntity(this);
	}

	// ===== BULLET FIREING =====
	this->_msSinceLastBullet += deltaTime;

	if (this->fireing && this->_msSinceLastBullet > this->_fireSpeed) {
		std::shared_ptr< si::Bullet > bullet =
			std::shared_ptr< si::Bullet >(
				new Bullet("./assets/images/laser.png"));

		bullet->setPosition(this->position.at(0), this->position.at(1));
		bullet->setSpeed(0, -0.5);
		bullet->setOwner(this);

		game.addEntity(bullet);
		this->_msSinceLastBullet -= this->_fireSpeed;
	}

	if (this->_msSinceLastBullet > this->_fireSpeed)
		this->_msSinceLastBullet = this->_fireSpeed;

	// ===== UPDATE THE SPRITE =====
	this->sprite.setRotation(this->rotation);

	this->sprite.setPosition(
		sf::Vector2f(this->position.at(0), this->position.at(1))
	);
}

void si::Ship::setThrustX (float x) {
	this->thrust.at(0) = x;
}

void si::Ship::setThrustY (float y) {
	this->thrust.at(1) = y;
}

void si::Ship::setMaxThrust (float x, float y) {
	if (x < 0 || y < 0) throw new ArgumentShouldBePositive();
	this->thrustPower.at(0) = x;
	this->thrustPower.at(1) = y;
}

void si::Ship::setFireSpeed (int speed) {
	if (speed < 0) throw new ArgumentShouldBeStrictPositive();

	this->_fireSpeed = speed;
}

void si::Ship::collision (Bullet& with, si::model::Game& game) {
	// If we fired the bullet just ignore the collision
	if (with.isOwner(this)) return;

	game.removeEntity(this);
}

si::EnemyShip::EnemyShip () {
	this->fireing = true;
	this->setThrustX(1);
}

si::EnemyShip::EnemyShip (std::string textureFileName) : si::Ship::Ship(textureFileName) {
	this->fireing = true;
	this->setThrustX(1);
}

void si::EnemyShip::collision (Bullet& with, si::model::Game& game) {
	// If we fired the bullet just ignore the collision
	if (with.isOwner(this)) return;
	if (with.enemy) return;

	game.removeEntity(this);
}

void si::EnemyShip::executeCollisionUsingMeOn (si::EntityBase& with, si::model::Game& game) {
	with.collision(*this, game);
}

void si::EnemyShip::update (int deltaTime, si::model::Game& game) {
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
	if (this->position.at(0) < 20) {
		this->setThrustX(0.8);
	}

	if (this->position.at(0) > worldSize.at(0) - 20) {
		this->setThrustX(-0.8);
	}

	// ===== BULLET FIREING =====
	this->_msSinceLastBullet += deltaTime;

	if (this->fireing && this->_msSinceLastBullet > this->_fireSpeed) {
		std::shared_ptr< si::Bullet > bullet =
			std::shared_ptr< si::Bullet >(
				new Bullet("./assets/images/laser.png"));

		bullet->setPosition(this->position.at(0), this->position.at(1));
		bullet->setSpeed(0, 0.5);
		bullet->setOwner(this);
		bullet->enemy = true;

		game.addEntity(bullet);
		this->_msSinceLastBullet -= this->_fireSpeed;
	}

	if (this->_msSinceLastBullet > this->_fireSpeed)
		this->_msSinceLastBullet = this->_fireSpeed;

	// ===== UPDATE THE SPRITE =====
	this->sprite.setRotation(this->rotation);

	this->sprite.setPosition(
		sf::Vector2f(this->position.at(0), this->position.at(1))
	);
}

si::Wall::Wall () {

}

si::Wall::Wall (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

void si::Wall::executeCollisionUsingMeOn (si::EntityBase& with, si::model::Game& game) {
	with.collision(*this, game);
}