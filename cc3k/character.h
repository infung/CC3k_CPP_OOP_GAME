#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "subject.h"
#include <string>

class Character : public Subject{
	
	int health;
	int atk;
	int def;
	int prevX;
	int prevY;
protected:
	int getPrevX() const;
	int getPrevY() const;
	void setPrevX(int x);
	void setPrevY(int y);
public:
	Character(int hp, int atk, int def, char display);
	int getAtk();
	void setAtk(int attack);
	int getHp();
	void setHp(int hp);
	int getDef();
	void setDef(int defence);
	Info getInfo() const override;
	virtual void move(std::string dir);
};

#endif

