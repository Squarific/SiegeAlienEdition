#ifndef ENTITYS_H
#define ENTITYS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace si {

	class Entity {
	public:
		std::vector<float> position = {0, 0}; // Pixels
		std::vector<float> speed = {0, 0};    // Pixels per ms
		int rotation = 0;                     // Degrees

		sf::Texture texture;
		std::string textureFileName;
		sf::Sprite sprite;

		Entity();
		Entity(const Entity& from);
		Entity(std::string textureFileName);

		void virtual draw(sf::RenderWindow* window);
		void virtual update(int deltaTime);                  // Deltatime = ms
		void virtual collision(Entity& with);
	};

	class Bullet : public Entity {
	public:
		Bullet();
		Bullet(std::string textureFileName);
	};

	class Ship : public Entity {
	public:
		// Ratio, 1 means go full thrust in the given direction
		std::vector<float> thrust = {0, 0};

		// Pixels per ms that the thrusters can give in that direction
		std::vector<float> thrustPower = {0.05, 0.05};

		Ship();
		Ship(std::string textureFileName);
	};

	class Wall : public Entity {
	public:
		Wall();
		Wall(std::string textureFileName);
	};

}

#endif /* ENTITYS_H */
