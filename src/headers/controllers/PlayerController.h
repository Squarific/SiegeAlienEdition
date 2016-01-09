#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <memory>
#include "Controller.h"

namespace si {
	namespace controller {

		class PlayerController : Controller {
		public:
			std::shared_ptr<Entity> target;

			PlayerController();
			PlayerController(std::shared_ptr<Entity> target);

			virtual void update();
		};

	}
}

#endif /* PLAYERCONTROLLER_H */