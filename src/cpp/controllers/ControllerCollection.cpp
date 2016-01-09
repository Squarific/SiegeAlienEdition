#include "ControllerCollection.h"

si::controller::ControllerCollection::ControllerCollection () {

}

void si::controller::ControllerCollection::update () {
	for (auto& controllerPtr : this->controllers) {
		controllerPtr->update();
	}
}