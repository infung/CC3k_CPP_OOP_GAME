#include "event.h"
#include <iostream>
using namespace std;


Event::Event()
: event{""} {}

void Event::log(string str) {
	if(event.length() > 1) {
		event += (" and ");
	}
	event += str;
}

string Event::getEvent() const{
	return event;
}

void Event::print() {
	cout << "Action: " << getEvent() << ((event.length() == 0)? "" : ".") << endl; 
	event = "";
}

Event::~Event() {}


