#include "drow.h"
#include "potion.h"

using namespace std;

const int baseHp = 125;
const int baseAtk = 25;
const int baseDef = 15;

Drow::Drow() : Player{baseHp, baseAtk, baseDef, baseHp, 'D'} {}
Drow::~Drow(){};


