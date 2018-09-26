#ifndef __EVENT_H__
#define __EVENT_H__
#include <iostream>

class Event {
	std::string event;
public:
	Event();
	void log(std::string str);
	std::string getEvent() const;
	~Event();
	void print();
};


#endif

