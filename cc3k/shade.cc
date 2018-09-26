#include "shade.h"
#include "enemy.h"
using namespace std;

const int baseHp = 125;
const int baseAtk = 25;
const int baseDef = 25;

Shade::Shade() : Player{baseHp, baseAtk, baseDef, baseHp, 'S'} {}

Shade::~Shade () {}

