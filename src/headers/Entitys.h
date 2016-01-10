#ifndef ENTITYS_H
#define ENTITYS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include <iostream>

namespace si {
	namespace model {
		// Forward declaration of Game to break cyclic dependency
		class Game;
	}

	class Bullet;
	class Ship;
	class EnemyShip;
	class Wall;

	class EntityBase {
	public:
		// This function will be called by the game, let the other know you
		// collided with it, this is called double dispatch because you know
		// what type you are but the game itself does not keep track
		// This one has to be implemented on every entitytype
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game) = 0;

		// This is the collision function that will be called
		// The parameter is an entity with the most specific type implemented
		// When two objects collide both their collision function will be
		// called, This base class should implement every collision function
		void virtual collision(EntityBase& with, si::model::Game& game) {};
		void virtual collision (Bullet& with, si::model::Game& game) {};
		void virtual collision (Ship& with, si::model::Game& game) {};
		void virtual collision (EnemyShip& with, si::model::Game& game) {};
		void virtual collision (Wall& with, si::model::Game& game) {};
	};

	class Entity : public EntityBase {
	private:
		std::vector<float> position = {0, 0}; // Pixels
		std::vector<float> speed = {0, 0};    // Pixels per ms
		float rotation = 0;                   // Degrees

	public:
		friend class Bullet;
		friend class Ship;
		friend class Wall;
		friend class EnemyShip;

		sf::Texture texture;
		std::string textureFileName;
		sf::Sprite sprite;

		Entity();
		Entity(const Entity& from);
		Entity(std::string textureFileName);

		// Apply the texture to the sprite
		void applyTexture (std::string textureFileName);

		// Draw the entity using its sprite on the window in the correct pos.
		void virtual draw(sf::RenderWindow* window);

		// Update the entity for 1 frame
		void virtual update(int deltaTime, si::model::Game& game);     // Deltatime = ms

		// Has to be implemented on all entity types
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game);

		// This function is called within one frame before update
		// You should not keep the given reference without continiously
		// checking if it still exists
		void virtual collision(EntityBase& with, si::model::Game& game) {};

		// Set the position, speed and rotation in pixels,
		// pixels per ms and degrees respectively
		void virtual setPosition(float x, float y);
		void virtual setSpeed(float x, float y);
		void virtual setRotation(float rotation);
	};

	class Bullet : public Entity {
	private:
		// You should never use this to access the owner unless you are sure
		// that it is currently still in memory. It is possible that this does
		// no longer exist
		Entity* _owner;

	public:
		Bullet();
		Bullet(std::string textureFileName);

		// Has to be implemented on all entity types
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game);

		// Set the owner or check if an object is the owner
		// There is no get owner cause we cannot guarentee that it still exist
		void setOwner(Entity* owner);
		bool isOwner(Entity* owner);
	};

	class Ship : public Entity {
	private:
		// Ratio, 1 means go full thrust in the given direction
		std::vector<float> thrust = {0, 0};

		// Pixels per ms per ms that the thrusters can give in that direction
		std::vector<float> thrustPower = {0.2, 0.2};

		// FireSpeed = ms per bullet, if this is smaller than the deltaTime
		// used in the updatefunction only one bullet will be fired per tick
		int _fireSpeed = 1000;
		int _msSinceLastBullet = 0;

	public:
		friend class EnemyShip;
		Ship();
		Ship(std::string textureFileName);

		// Set the thrust of the ship in ratio (0 = no thrust, 1 = full thrust)
		// 2 = double thrust, negative values are in the opposite direction
		// The ship never goes faster than the thrustPower so giving anything
		// above 1 is futile
		void setThrustX(float x);
		void setThrustY(float y);

		void virtual update(int deltaTime, si::model::Game& game);     // Deltatime = ms

		// Has to be implemented on all entity types
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game);

		// Collision with bullets
		void virtual collision (Bullet& with, si::model::Game& game);

		bool fireing = false;
	};

	class EnemyShip : public Ship {
	public:
		EnemyShip();
		EnemyShip(std::string textureFileName);

		// Has to be implemented on all entity types
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game);

		// Collision with bullets
		void virtual collision (Bullet& with, si::model::Game& game);
		void virtual update(int deltaTime, si::model::Game& game);     // Deltatime = ms
	};

	class Wall : public Entity {
	public:
		Wall();
		Wall(std::string textureFileName);

		// Has to be implemented on all entity types
		void virtual executeCollisionUsingMeOn(EntityBase& other, si::model::Game& game);
	};

}

#endif /* ENTITYS_H */
