#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <vector>
#include "observer.h"
#include <iostream>
#include "subject.h"
class TextDisplay: public Observer {
	int rows, cols;
	std::vector<std::vector<char>> theDisplay;
	std::vector<std::vector<char>> floorLayout;
public:
	TextDisplay();
	void notify(Subject &whoNotified) override;
	SubscriptionType subType() const override;
	~TextDisplay();
	friend class Floor;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

//friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif

