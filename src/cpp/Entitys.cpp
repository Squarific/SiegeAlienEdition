#include "Entitys.h"
#include "Errors.h"

si::Entity::Entity () {
	if (!this->texture.loadFromFile("assets/image/noimg.png"))
		throw TextureFileException();

	this->textureFileName = "assets/image/noimg.png";
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);

	// This is probably unexpected behaviour as making an entity without sprite
	// makes little sens, so we'll throw an exception
	throw NoTextureArgument();
}

si::Entity::Entity (std::string textureFileName) {
	if (!this->texture.loadFromFile(textureFileName))
		throw TextureFileException();

	this->textureFileName = textureFileName;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
}

si::Entity::Entity (const si::Entity& from) {
	if (!this->texture.loadFromFile(from.textureFileName))
		throw TextureFileException();

	this->textureFileName = from.textureFileName;
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
}

si::Bullet::Bullet () {

}

si::Bullet::Bullet (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

si::Ship::Ship () {

}

si::Ship::Ship (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

si::Wall::Wall () {

}

si::Wall::Wall (std::string textureFileName) : si::Entity::Entity(textureFileName) {

}

void si::Entity::draw (sf::RenderWindow* window) {
	window->draw(this->sprite);
}