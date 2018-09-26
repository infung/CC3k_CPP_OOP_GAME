#include "game.h"
#include <string>
using namespace std;

const int numFloor = 1;

Game::Game(): currLevel{1}{}
Game::~Game() {}
void Game::init(char race) {
	string Race;
	if(currLevel == 1) {
	if(race == 's') {
		player = make_shared<Shade>();
		Race = "Shade";
	} else if(race == 'd') {
		player = make_shared<Drow>();
		Race = "Drow";
	} else if(race == 'v') {
		player = make_shared<Vampire>();
		Race = "Vampire";
	} else if(race == 't') {
		player = make_shared<Troll>();
		Race = "Troll";
	} else if(race == 'g') {
		player = make_shared<Goblin>();
		Race = "Goblin";
	}}
	floors.emplace_back(make_shared<Floor>(player, Race, currLevel));
	int j = currLevel-1;
	//floors[currLevel-1] -> draw();
	//cout << "Action:" << endl;
	floors[j]->generateStairWay();
	floors[j]->placePlayer();
	floors[j]->generatePotions();
	floors[j]->generateTreasures();
	floors[j]->generateEnemies();
	floors[currLevel-1] -> draw();
}

void Game::restart() {
	currLevel = 1;
	enemyMove = true;
	floors.resize(0);
        player.reset(new Shade());
}

void Game::freeze() {
	enemyMove = !enemyMove;
}

void Game::quit() {
	cout << "Thanks for your play!"<< endl;
}

void Game::moveToNext() {
	if(currLevel == 6) {return;}
	char race = player->getRace();
	init(race);

}



int Game::getScore()  {
	int score = player->getGold();
	auto pl = dynamic_pointer_cast<Shade>(player);
	if (pl) {
		score = 1.5 * score;
	}
	return score;
}

bool Game::isLost() {
	if (player->getHp() <= 0) {
                cout << "Your final score is " << getScore() << endl;
                this->quit();
                return true;
        }	
	return false;
}

bool Game::isWon() {
	if (currLevel == 6) {
		cout << "Congratulations! " <<
			"You got to the stair on the top floor!" << endl;
		cout << "Your final score is " << getScore() << '!' << endl;
		this->quit();
		return true;
	}
	return false;
}


void Game::playerMove(string dir) {
	if(floors[currLevel-1]->isPlayerOnStair(dir)) {
		currLevel++;
		moveToNext();
	} else {
		floors[currLevel-1]->movePlayer(dir, enemyMove);
	}
}

void Game::playerAttack(string dir) {
	floors[currLevel-1]->attackEnemies(dir, enemyMove);
	//if(enemyMove) {floors[currLevel-1]->moveEnemies();}
}
void Game::usePotion(string dir) {
	floors[currLevel-1]->potionUsed(dir, enemyMove);
	//if(enemyMove) {floors[currLevel-1]->moveEnemies();}
}

