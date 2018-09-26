#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "player.h"
#include "info.h"
#include <memory>
class Enemy;
class Goblin : public Player {

public:
        Goblin();
        ~Goblin();
        void attack(std::shared_ptr<Enemy> e) override;
        void acceptAttack(Enemy * e) override;
};


#endif


