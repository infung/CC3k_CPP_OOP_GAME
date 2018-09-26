#include "subject.h"
#include "observer.h"
#include "subscriptiontype.h"
using namespace std;

void Subject::reset() {
	for(auto on: observers) {
		on.reset();
	}
	observers.resize(0);
	observers.clear();
}

Subject::Subject(char c) :display{c} {}

int Subject::getX() const{return x;}

int Subject::getY() const{return y;}

void Subject::setX(int X) {x = X;}

void Subject::setY(int Y) {y = Y;}

char Subject::getDisplay() const{return display;}

void Subject::setDisplay(char c) {display = c;}

void Subject::attach(shared_ptr<Observer> o) { 
	(this -> observers).emplace_back(o);
}

void Subject::detach(shared_ptr<Observer> o) {
	 
	for(unsigned int i = 0; i < observers.size(); i++) {
		if(observers[i] == o) 
			observers.erase(observers.begin() + i);
	}
}

void Subject::notifyObservers(SubscriptionType t) {
	for(auto ob : (this -> observers)) {
		if(ob -> subType() == t) {
			ob -> notify(*this);
		}
	}
}

Subject::~Subject() {}

