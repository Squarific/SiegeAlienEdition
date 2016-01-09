#ifndef CONTROLLERCOLLECTION_H
#define CONTROLLERCOLLECTION_H

#include <vector>
#include <memory>
#include "Controller.h"

namespace si {
	namespace controller {

		class ControllerCollection {
		public:
			std::vector< std::shared_ptr< si::controller::Controller >> controllers;

			ControllerCollection();

			// Let all controllers update
			void update();
		};

	}
}

#endif /* CONTROLLERCOLLECTION_H */