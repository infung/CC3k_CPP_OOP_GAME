#ifndef FLOOR_H
#define FLOOR_H
#include "textdisplay.h"
#include "enemy.h"
#include "player.h"
#include "item.h"
#include "potion.h"
#include "point.h"
#include <iostream>
#include <memory>


class Floor{
private:
	std::string playerRace;
	int level;
	std::shared_ptr<TextDisplay> display;
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Potion>> pots;
	std::vector<std::shared_ptr<Treasure>> golds;
	std::vector<Point> emptyTiles;
	std::shared_ptr<Player> player;
	std::vector<std::vector<Point>> rooms;
	void mapEmptyTiles(); 
	std::vector<Point> getSurroundingEmptyTiles(int y, int x);
	Point dirToPoints(std::string dir);
public:
	Floor(std::shared_ptr<Player> player, std::string race, int level);
	void draw();
	void generateEnemies();
	void generatePotions();
	void generateTreasures();
	void moveToNextLevel();
	//void reset();
	void placePlayer();
	void generateStairWay();
	void moveEnemies();
	void movePlayer(std::string dir, bool enemyMovable);
	void attackEnemies(std::string dir, bool enemyMovable);
	void potionUsed(std::string dir, bool enemyMovable);
	bool isPlayerOnStair(std::string dir);
};

#endif


