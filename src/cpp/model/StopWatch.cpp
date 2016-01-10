#include "StopWatch.h"
#include "Errors.h"

#include <chrono>

si::model::StopWatch::StopWatch () {
	this->_lastTime = std::chrono::system_clock::now();
}

si::model::StopWatch::StopWatch (int delta) {
	this->setDeltaTime(delta);
}

void si::model::StopWatch::Reset () {
	this->_lastTime = std::chrono::system_clock::now();
}

int si::model::StopWatch::getFrames () {
	clocktime currentTime = std::chrono::system_clock::now();
	milliDuration elapsed = currentTime - this->_lastTime;
	double elapsedMillis = elapsed.count();

	int frames = elapsedMillis / this->_delta;
	this->_lastTime += std::chrono::milliseconds(frames * this->_delta);
	return frames;
}

int si::model::StopWatch::getFramesWithoutReset () {
	clocktime currentTime = std::chrono::system_clock::now();
	milliDuration elapsed = currentTime - this->_lastTime;
	double elapsedMillis = elapsed.count();

	int frames = elapsedMillis / this->_delta;
	return frames;
}

int si::model::StopWatch::getDeltaTime () {
	return this->_delta;
}

void si::model::StopWatch::setDeltaTime (int delta) {
	if (delta <= 0) {
		throw new ArgumentShouldBeStrictPositive();
	}

	this->_delta = delta;
	this->_lastTime = std::chrono::system_clock::now();
}