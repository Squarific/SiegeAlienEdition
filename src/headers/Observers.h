#ifndef OBSERVERS_H
#define OBSERVERS_H

namespace si {
	class Observable;

	class Observer {
	public:
		Observer(){};
		virtual void notify (Observable& subject)=0;
	};

	class Observable {
	public:
		Observable(){};
		std::vector <std::shared_ptr<Observer>> observers;
		virtual void notifyObservers()=0;
		virtual void registerObserver(std::shared_ptr<Observer> observer)=0;
	};
}

#endif /* OBSERVERS_H */