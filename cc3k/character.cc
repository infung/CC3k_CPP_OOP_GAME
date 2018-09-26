#include "character.h"
#include "info.h"
using namespace std;

int Character::getPrevX() const{
	return prevX;
}

int Character::getPrevY() const{
	return prevY;
}


void Character::setPrevX(int x){
	this -> prevX = x;
}

void Character::setPrevY(int y){
	this -> prevY = y;
}

Character::Character(int hp, int atk, int def, char display) 
	:Subject{display}, health{hp}, atk{atk}, def{def} {}

int Character::getAtk(){
	return atk;
}

void Character::setAtk(int attack) {
	atk = attack;
}

int Character::getHp(){
	return health;
}

void Character::setHp(int hp){
	health = hp;
}

int Character::getDef(){
	return def;
}

void Character::setDef(int defence){
	def = defence;
}

void Character::move(string dir){
	prevX = getX();
	prevY = getY();

	if(dir == "no") {
		setY(getY()-1);
	}else if(dir == "so") {
		
		setY(getY()+1);
	}else if(dir == "ea") {
		setX(getX()+1);
	}else if(dir == "we") {
		setX(getX()-1);
	}else if(dir == "ne") {
		setX(getX()+1);
		setY(getY()-1);
	}else if(dir == "nw") {
		setX(getX()-1);
		setY(getY()-1);
	}else if(dir == "se") {
		setX(getX()+1);
		setY(getY()+1);
	}else {
		setX(getX()-1);
		setY(getY()+1);
	}
}

Info Character::getInfo() const{
	return Info{getX(), getY(), prevX, prevY, getDisplay()};
}


