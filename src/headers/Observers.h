#ifndef OBSERVERS_H
#define OBSERVERS_H

namespace si {

	class Observer {
	public:
		Observer();

	};

	class Observable {
	public:
		virtual void notifyObservers() {};
	};
}

#endif /* OBSERVERS_H */