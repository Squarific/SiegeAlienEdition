#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <memory>
#include "Entitys.h"
#include "Controller.h"

namespace si {
	namespace controller {

		class PlayerController : public Controller {
		public:
			std::shared_ptr<si::Ship> target;

			PlayerController();
			PlayerController(std::shared_ptr<Ship> target);

			virtual void update();
		};

	}
}

#endif /* PLAYERCONTROLLER_H */