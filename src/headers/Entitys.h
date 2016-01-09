#ifndef ENTITYS_H
#define ENTITYS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace si {
	namespace model {
		// Forward declaration of Game to break cyclic dependency
		class Game;
	}

	class Entity {
	private:
		std::vector<float> position = {0, 0}; // Pixels
		std::vector<float> speed = {0, 0};    // Pixels per ms
		int rotation = 0;                     // Degrees

		sf::Texture texture;
		std::string textureFileName;
		sf::Sprite sprite;

	public:
		friend class Bullet;
		friend class Ship;
		friend class Wall;

		Entity();
		Entity(const Entity& from);
		Entity(std::string textureFileName);

		// Apply the texture to the sprite
		void applyTexture (std::string textureFileName);

		// Draw the entity using its sprite on the window in the correct pos.
		void virtual draw(sf::RenderWindow* window);

		// Update the entity for 1 frame
		void virtual update(int deltaTime, si::model::Game& game);     // Deltatime = ms

		// Notify the entity that it collided with another one, this function
		// is called within one frame before update
		void virtual collision(Entity& with);

		// Set the position and speed in pixels and pixels per ms respectively
		void virtual setPosition(float x, float y);
		void virtual setSpeed(float x, float y);
	};

	class Bullet : Entity {
	public:
		Bullet();
		Bullet(std::string textureFileName);
	};

	class Ship : public Entity {
	private:
		// Ratio, 1 means go full thrust in the given direction
		std::vector<float> thrust = {0, 0};

		// Pixels per ms per ms that the thrusters can give in that direction
		std::vector<float> thrustPower = {0.05, 0.05};

		// FireSpeed = ms per bullet, if this is smaller than the deltaTime
		// used in the updatefunction only one bullet will be fired per tick
		int fireSpeed = 1000;
		int msSinceLastBullet = 0;
		bool fireing = false;

	public:
		Ship();
		Ship(std::string textureFileName);

		// Set the thrust of the ship in ratio (0 = no thrust, 1 = full thrust)
		// 2 = double thrust, negative values are in the opposite direction
		// The ship never goes faster than the thrustPower so giving anything
		// above 1 is futile
		void setThrustX(float x);
		void setThrustY(float y);

		void virtual update(int deltaTime, si::model::Game& game);     // Deltatime = ms
	};

	class Wall : public Entity {
	public:
		Wall();
		Wall(std::string textureFileName);
	};

}

#endif /* ENTITYS_H */
