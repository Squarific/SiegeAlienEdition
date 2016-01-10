#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "tinyxml.h"
#include "Game.h"
#include "Entitys.h"
#include <memory>

namespace si {
	class XmlParser {
	public:
		void fillGame(const char* filename, si::model::Game& game);
		std::shared_ptr<si::EnemyShip> createEnemy(TiXmlElement* enemyElem);
	};
}

#endif