#ifndef _POTION_H_
#define _POTION_H_
#include <string>
#include "item.h"

class Player;

class Potion : public Item{
	std::string type;
public:
	Potion(std::string type);
	void usedBy(Player * player);
	Info getInfo() const;
	~Potion();
	std::string getType();
};

#endif


