#include "game.h"
#include <iostream>
#include <string>
using namespace std;

const int notQuit = 1;
const int Quit = 0;

int main(){
	cin.exceptions(ios::eofbit|ios::failbit);
	Game cc3k;
	cout << "Game [CC3K] creats!" << endl;
	char race;
	string cmd;
	int quit = notQuit;
	bool win = false;
	//start game
	try{
		while(true) {
		//creat a player with speciific race
			cout << "[ENTER] your race(s-Shade, d-Drow, t-Troll, v-Vampire, g-Goblin): " << endl;
			cin >> race;
			if(race != 's' && race != 'd' && race != 't'  && race != 'v'  && race != 'g' ) {
				cout << "Invalid input." << endl; continue;
			}
			cc3k.init(race);
			while(!cc3k.isLost()){
				cout << "[ENTER] your action: " << endl;
				cin >> cmd;
				if(cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw"){
					cc3k.playerMove(cmd);
				} else if (cmd == "u") {
					cin >> cmd;
					cc3k.usePotion(cmd);
				} else if (cmd == "a") {
					cin >> cmd;
					cc3k.playerAttack(cmd);
				} else if (cmd == "f") {
					cc3k.freeze();
				} else if (cmd == "r") {
					cc3k.restart();
					break;//restarts the game,
					      //breaks the inner loop
					      //and selects a new race
				} else if (cmd == "q") {
					cc3k.quit();
					quit = Quit;
					break;
				}
				win = cc3k.isWon();
				if(win) {break;}
			}
			if(quit == Quit || win || cc3k.isLost()) {break;}
		}
	}
	catch (ios::failure &) {}
}

