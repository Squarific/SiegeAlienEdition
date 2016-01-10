#include "tinyxml.h"
#include "XmlParser.h"
#include "Game.h"
#include "Entitys.h"
#include "Errors.h"

#include <string>

#include <iostream>

void si::XmlParser::fillGame (const char* filename, si::model::Game& game) {
	// Create xml dom
	TiXmlDocument doc(filename);

	// Load the document
	if (!doc.LoadFile()) throw new si::XmlFileException();

	TiXmlElement* level = doc.FirstChildElement();
 	if (level == NULL) throw new si::XMLNoRoot();
 	if (std::string(level->Value()) != "level") throw new si::XMLBadRoot();

 	TiXmlElement* enemies = level->FirstChildElement();
 	if (enemies == NULL) throw new si::XMLNoEnemies();

 	for (TiXmlElement* enemy = enemies->FirstChildElement();
 	     enemy != NULL;
 	     enemy = enemy->NextSiblingElement()) {

 		game.addEntity(this->createEnemy(enemy));
 	}
}

std::shared_ptr<si::EnemyShip> si::XmlParser::createEnemy (TiXmlElement* enemyElem) {
	// Default values
	std::string texture = "assets/images/noimg.png";

	double x = 50;
	double y = 50;

	int firespeed = 500;

	double thrustpowerx = 0.2;
	double thrustpowery = 0.2;

	TiXmlNode* TXNode = enemyElem->FirstChild();
	TiXmlText* text = TXNode->ToText();
	texture = text->Value();

	enemyElem->Attribute("x", &x);
	enemyElem->Attribute("y", &y);

	enemyElem->Attribute("firespeed", &firespeed);
	
	enemyElem->Attribute("thrustpowerx", &thrustpowerx);
	enemyElem->Attribute("thrustpowery", &thrustpowery);

	std::shared_ptr<EnemyShip> enemy =
		std::shared_ptr<EnemyShip>(
			new si::EnemyShip(texture));

	enemy->setRotation(180);
	enemy->setPosition(x, y);
	enemy->setFireSpeed(firespeed);
	enemy->setMaxThrust(thrustpowerx, thrustpowery);

	return enemy;
}