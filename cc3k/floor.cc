#include "floor.h"
#include "info.h"
#include "treasure.h"
#include "dragon.h"
#include "dragonhorde.h"
#include "drow.h"
#include "dwarf.h"
#include "elf.h"
#include "goblin.h"
#include "halfling.h"
#include "human.h"
#include "merchant.h"
#include "merchanthorde.h"
#include "normaltreasure.h"
#include "orc.h"
#include "shade.h"
#include "smalltreasure.h"
#include "treasure.h"
#include <sstream>
using namespace std;

Floor::Floor(shared_ptr<Player> player, string race, int level)
: player{player}, playerRace{race}, level{level} {
	// rooms[0]
	vector<Point> rooms0;
	for(int i = 0; i < (26*4) ; i++) {
		rooms0.emplace_back(Point{(i%26)+3, (i/26)+3});
	}
	//rooms[1]
	vector<Point> rooms1;
	for(int i = 0; i < (21*7); i++) {
		rooms1.emplace_back(Point{(i%21)+4, (i/21)+15});
	}
	//room[2]
	vector<Point> rooms2;
	for(int i = 0; i < (12*3); i++) {
		rooms2.emplace_back(Point{(i%12)+38, (i/12)+10});
	}
	//room[3]
	vector<Point> rooms3;
	for(int i = 0; i < 23*2; i++) {
		rooms3.emplace_back(Point{39+(i%23), 3+(i/23)});
	}
	for(int i = 0; i < 31; i++) {
		rooms3.emplace_back(Point{39 + i, 5});
	}
	for(int i = 0; i < 33; i++) {
		rooms3.emplace_back(Point{39 + i, 6});
	}
	for(int i = 0; i < 15*6; i++) {
		rooms3.emplace_back(Point{61+(i%15), 7+(i/15)});
	}

	//room[4]
	vector<Point> rooms4;
	for(int i = 0; i < 11*3; i++) {
		rooms4.emplace_back(Point{65+(i%11), 16+(i/11)});
	}
	for(int i = 0; i < 39*3; i++) {
		rooms4.emplace_back(Point{37+(i%39), 19+(i/39)});
	}
	rooms.emplace_back(rooms0);
	rooms.emplace_back(rooms1);
	rooms.emplace_back(rooms2);
	rooms.emplace_back(rooms3);
	rooms.emplace_back(rooms4);
	display = make_shared<TextDisplay>();

	player -> attach(display);
}


Point Floor::dirToPoints(string dir) {
	Point location {player->getInfo().x, player->getInfo().y};
	if(dir == "no") {
		location.y--;
	}else if(dir == "so") {
		location.y++;
	}else if(dir == "ea") {
		location.x++;
	}else if(dir == "we") {
		location.x--;
	}else if(dir == "ne") {
		location.x++;
		location.y--;
	}else if(dir == "nw") {
		location.x--;
		location.y--;
	}else if(dir == "se") {
		location.x++;
		location.y++;
	}else {
		location.x--;
		location.y++;
	}
	return location;
}


void Floor::attackEnemies(string dir, bool enemyMovable) {
	//modify needed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	Point enemyLocation = dirToPoints(dir);
	for(auto it = enemies.begin(); it != enemies.end(); it++) {
		auto e = *it;
		if(e->getInfo().x == enemyLocation.x && e->getInfo().y == enemyLocation.y) {
			player->attack(e); 
			bool isDead = false;
			if(e -> getHp() <= 0) {
				isDead = true;
				if(e->getDisplay() == 'M') {
					 shared_ptr<Treasure> tr{new MerchantHorde{4}};
					 golds.emplace_back(tr);
					 tr -> attach(display);
                                         player -> attach(tr);
					 tr->setX(e->getInfo().x);
					 tr->setY(e->getInfo().y);
					 tr -> notifyObservers(SubscriptionType::All);
        	                        player->detach(e);
	                                enemies.erase(it);
					 
				} else if(e->getDisplay() == 'H') {
					 shared_ptr<Treasure> tr{new NormalTreasure{4}};
					 golds.emplace_back(tr);
                                         tr -> attach(display);
                                         player -> attach(tr);
                                         tr->setX(e->getInfo().x);
                                         tr->setY(e->getInfo().y);
                                         tr -> notifyObservers(SubscriptionType::All);

	                                player->detach(e);
        	                        enemies.erase(it);

				} else {
				e->setDisplay('.');
				e->notifyObservers(SubscriptionType::All);
				player->detach(e);
				enemies.erase(it);
				}
			}
			if(enemyMovable) {moveEnemies();}
			
                        if(!isDead) {
				 if(enemyMovable) {player->notifyObservers(SubscriptionType::PlayerToEnemy);}
			}
			// here
			draw();
			break;
		}
	}
}

void Floor::potionUsed(string dir, bool enemyMovable) {
	Point potionLocation = dirToPoints(dir);
	for(auto it = pots.begin(); it != pots.end(); it++) {
		auto p = *it;
		if(p->getInfo().x == potionLocation.x && p->getInfo().y == potionLocation.y){
			string ps = p->getType();
			player->useItem(p);
			p->setDisplay('.');
			p->notifyObservers(SubscriptionType::All);
			pots.erase(it);
			if(enemyMovable) {moveEnemies();}
			if(enemyMovable) {player->notifyObservers(SubscriptionType::PlayerToEnemy);}
			draw();
			
			
			break;
		}
	}
	
}

void Floor::draw() {
	cout << *display << endl;
	if(player) {
		cout << "Race: " << playerRace << " Gold: " << player->getGold();
		cout << "                                           Floor " << level << endl;
		cout << "HP: " << player->getHp() << endl;
		cout << "Atk: " << player->getAtk() << endl;
		cout << "Def: " << player->getDef() << endl;
		player -> printLog();
	}
}

void Floor::mapEmptyTiles() {
	emptyTiles.resize(0);
	for (int i = 0; i < display -> rows; i++) {
		for(int j = 0; j < display -> cols; j++) {
			if((display -> theDisplay)[i][j] == '.') {
				emptyTiles.emplace_back(Point{j, i});
			}
		}
	}
}


vector<Point> Floor::getSurroundingEmptyTiles(int y, int x) {
    vector <Point> pointList;
    Point p;
	if ((display -> theDisplay)[x+1][y] == '.') {
		p = {y,x+1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x+1][y+1] == '.') {
		p = {y+1,x+1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x][y-1] == '.') {
		p = {y-1,x};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x+1][y-1] == '.') {
		p = {y-1,x+1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x-1][y+1] == '.') {
		p = {y+1,x-1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x-1][y] == '.') {
		p = {y,x-1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x-1][y-1] == '.') {
		p = {y-1,x-1};
		pointList.emplace_back(p);
	}
	if ((display -> theDisplay)[x-1][y+1] == '.') {
		p = {y+1,x-1};
		pointList.emplace_back(p);
	}
	return pointList;
}

void Floor::generateStairWay(){
	srand(time(NULL));
	mapEmptyTiles();
	int r = rand()%(emptyTiles.size());
	(display -> theDisplay)[emptyTiles[r].y][emptyTiles[r].x] = '\\';
}

void Floor::generateEnemies() {
	//initialize
	srand(time(NULL));
	for(int i = 0; i < 20; i++) {
		int x = rand() % 18;
		if(x <= 2) {
			//dwarf
			shared_ptr<Enemy> en{new Dwarf{}};
			enemies.emplace_back(en);
		} else if (x <= 7) {
			//Halfling
			shared_ptr<Enemy> en{new Halfling{}};
			enemies.emplace_back(en);
		} else if (x <= 9) {
			//Elf
			shared_ptr<Enemy> en{new Elf{}};
			enemies.emplace_back(en);
		} else if (x <= 11) {
			//Orc
			shared_ptr<Enemy> en{new Orc{}};
			enemies.emplace_back(en);
		} else if (x <= 13) {
			//Merchant
			shared_ptr<Enemy> en{new Merchant{}};
			enemies.emplace_back(en);
		} else {
			//human
			shared_ptr<Enemy> en{new Human{}};
			enemies.emplace_back(en);
		}
	}
	//add to player's observer
	for(auto e : enemies) {
		e -> attach(display);
		player -> attach(e);
	}
	//place them
	for(auto e : enemies) {
		int rn;
		shared_ptr<Dragon> d = dynamic_pointer_cast<Dragon>(e);
		if(d) {
			//cout << "generated a dragon!" << endl;
			vector<Point> surroundingTiles 
						= getSurroundingEmptyTiles((d -> dh) -> getInfo().x, (d -> dh) -> getInfo().y);
			rn = rand()%(surroundingTiles.size());
			e -> setX(surroundingTiles[rn].x);
			e -> setY(surroundingTiles[rn].y);
			e -> notifyObservers(SubscriptionType::All);
			continue;
		}
		this -> mapEmptyTiles();
		rn = rand()%(emptyTiles.size());
		e -> setX(emptyTiles[rn].x);
		e -> setY(emptyTiles[rn].y);
		e -> notifyObservers(SubscriptionType::All);
	}
}

void Floor::generatePotions() {
	//initialize
	srand(time(NULL));
	for(int i = 0; i < 10; i++) {
		int x = rand() % 6;
		if(x <= 1) {
			//RH
			shared_ptr<Potion> pn{new Potion{"RH"}};
			pots.emplace_back(pn);
		} else if (x <= 2) {
			//BA
			shared_ptr<Potion> pn{new Potion{"BA"}};
			pots.emplace_back(pn);
		} else if (x <= 3) {
			//BD
			shared_ptr<Potion> pn{new Potion{"BD"}};
			pots.emplace_back(pn);
		} else if (x <= 4) {
			//PH
			shared_ptr<Potion> pn{new Potion{"PH"}};
			pots.emplace_back(pn);
		} else if (x <= 5) {
			//WA
			shared_ptr<Potion> pn{new Potion{"WA"}};
			pots.emplace_back(pn);
		} else {
			//WD
			shared_ptr<Potion> pn{new Potion{"WD"}};
			pots.emplace_back(pn);
		}
	}
	//add to player's observer
	for(auto p: pots) {
		p -> attach(display);
	}
	//place them
	for(auto p: pots) {
		this -> mapEmptyTiles();
		int rn = rand()%(emptyTiles.size());
		p -> setX(emptyTiles[rn].x);
		p -> setY(emptyTiles[rn].y);
		p -> notifyObservers(SubscriptionType::All);
	}
}

void Floor::generateTreasures() {
	//initialize
	srand(time(NULL));
	for(int i = 0; i < 10; i++) {
		int x = rand() % 8;
		if(x <= 4) {
			//Normal
			shared_ptr<Treasure> tr{new NormalTreasure{2}};
			golds.emplace_back(tr);
		} else if (x <= 5) {
			//Dragon Horde
			shared_ptr<Treasure> tr{new DragonHorde{6}};
			golds.emplace_back(tr);
			auto dh = dynamic_pointer_cast<DragonHorde>(tr);
			shared_ptr<Enemy> en{new Dragon{dh}};
			enemies.emplace_back(en);
		} else{
			//Small 
			shared_ptr<Treasure> tr{new SmallTreasure{1}};
			golds.emplace_back(tr);
		}
	}
	//add to player's observer
	for(auto g: golds) {
		g -> attach(display);
		player -> attach(g);
	}
	//place them
	for(auto g: golds) {
		this -> mapEmptyTiles();
		int rn = rand()%(emptyTiles.size());
		g -> setX(emptyTiles[rn].x);
		g -> setY(emptyTiles[rn].y);
		g -> notifyObservers(SubscriptionType::All);
	}
}

void Floor::placePlayer() {
	srand(time(NULL));
	int random, flag = 1;
	//make sure player and stair are not in the same chamber
	while(flag){
		flag = 0;
		random = rand()%5;
		for(auto p: rooms[random]) {
			if((display -> theDisplay)[p.y][p.x] == '\\')
				flag = 1;
		}
	}
	while(true) {
		int random2 = rand()%(rooms[random].size());
		if((display -> theDisplay)[rooms[random][random2].y][rooms[random][random2].x] == '.'){
			player -> setX(rooms[random][random2].x);
			player -> setY(rooms[random][random2].y);
			player -> notifyObservers(SubscriptionType::All);
			break;
		}
	}
	player -> log("Player character has spawned");
}

void Floor::moveEnemies() {
	srand(time(NULL));
	for(auto e: enemies) {
	  if((e->getInfo().x - player->getInfo().x >= -1 &&
	      e->getInfo().x - player->getInfo().x <= 1) &&
             (e->getInfo().y - player->getInfo().y >= -1 &&                
	      e->getInfo().y - player->getInfo().y <= 1)) {
		//notify enimies to attack
	  } else {                
		vector<Point> surroundingTiles = getSurroundingEmptyTiles(e -> getInfo().x, e -> getInfo().y);
		if(surroundingTiles.size() == 0) continue;
		int rn = rand()%(surroundingTiles.size());
		e -> moveTo(surroundingTiles[rn].x, surroundingTiles[rn].y);
		e -> notifyObservers(SubscriptionType::All);
	  }
	}
}

void Floor::movePlayer(string dir, bool enemyMovable) {
		//update Hp before draw!!!!!!needed to modify!!!!!!!************
		Point Location = dirToPoints(dir);
		if((display -> theDisplay)[Location.y][Location.x] != '.' 
		    && (display -> theDisplay)[Location.y][Location.x] != 'G' 
		    && (display -> theDisplay)[Location.y][Location.x] != '+'
		    && (display -> theDisplay)[Location.y][Location.x] != '#') {return;}

		player -> move(dir);
		player -> notifyObservers(SubscriptionType::All);
		if(enemyMovable) {moveEnemies();}
		
		int prevGold = player->getGold();
		player -> notifyObservers(SubscriptionType::PlayerToItem);
		int Goldgot = 0;
		for(auto it = golds.begin(); it != golds.end(); it++) {
			auto g = *it;
                        if(g->getInfo().x == player->getInfo().x && g->getInfo().y == player->getInfo().y) {
				if(prevGold != player->getGold()) {
					Goldgot = g->getGold();
					player->detach(g);
					golds.erase(it);
					break;
				}
			}
		}

		ostringstream ss;
		string Direction;
		if(dir == "no") {
			Direction = "North";
		}else if(dir == "so") {
			Direction = "South";
		}else if(dir == "ea") {
			Direction = "East";
		}else if(dir == "we") {
			Direction = "West";
		}else if(dir == "ne") {
			Direction = "Northeast";
		}else if(dir == "nw") {
			Direction = "Northwest";
		}else if(dir == "se") {
			Direction = "Southeast";
		}else {
			Direction = "Southwest";
		}
		ss << "PC moved " << Direction;
		player -> log(ss.str());
//		if(Goldgot) {
//			cout << " and PC gains golds " << Goldgot;
//		}
		if(enemyMovable) {player -> notifyObservers(SubscriptionType::PlayerToEnemy);}
		//player -> notifyObservers(SubscriptionType::All);
		for(auto p: pots) {
			if((p->getInfo().x - Location.x >= -1 &&
				p->getInfo().x - Location.x <= 1) &&
				(p->getInfo().y - Location.y >= -1 &&
				p->getInfo().y - Location.y <= 1)) {
				player -> log( "PC sees an unknown potion");
				break;
			}
		}
		for(auto g: golds) {
			if(g->getInfo().x - Location.x >= -1 &&
                                g->getInfo().x - Location.x <= 1 &&
                                g->getInfo().y - Location.y >= -1 &&
                                g->getInfo().y - Location.y <= 1 ) {
				player -> log( " sees an unknown gold");
				break;
			}
		}
		draw();
}

void Floor::moveToNextLevel() {
	enemies.clear();
	golds.clear();
	pots.clear();
	display.reset();;
	display = make_shared<TextDisplay>();
	player->attach(display);
	mapEmptyTiles();
}

bool Floor::isPlayerOnStair(string dir) {
	Point Location = dirToPoints(dir);
	return (display -> theDisplay)[Location.y][Location.x] == '\\';
}

