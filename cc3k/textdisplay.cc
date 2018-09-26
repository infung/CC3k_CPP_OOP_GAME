#include "textdisplay.h"
#include <fstream>
#include <iostream>
#include <string>
#include "info.h"
using namespace std;

TextDisplay::TextDisplay() : rows{25}, cols{79} {
	ifstream file{"basefloor.txt"};
	string s;
	int i = 0;	
	theDisplay.resize(rows);
	floorLayout.resize(rows);
	while(!file.eof() && i < rows) {
		getline(file, s);
		theDisplay[i].resize(cols);
		floorLayout[i].resize(cols);
		for(int j = 0; j < cols; j++) {
			this -> theDisplay[i][j] = s[j];
			floorLayout[i][j] = s[j];
		}
		i++;
	}
}

void TextDisplay::notify(Subject &whoNotified) {
	Info info = whoNotified.getInfo();
	if(info.x <= cols && info.x > 0 && info.y <= rows && info.y > 0) {
		this -> theDisplay[info.y][info.x] = whoNotified.getDisplay();
	}
	//need to set the object's previous position to . 
	if(info.prevX != info.x || info.prevY != info.y) {
		if(info.prevX <= cols && info.prevX > 0 && info.prevY <= rows && info.prevY > 0) {
			this -> theDisplay[info.prevY][info.prevX] 
				= floorLayout[info.prevY][info.prevX];
		}
	}
}

SubscriptionType TextDisplay::subType() const {
	return SubscriptionType::All;
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	for(int i = 0; i < td.rows; i++) { 
		for(int j = 0; j < td.cols; j++) {
			out << (td.theDisplay)[i][j];
		}
		out << endl;
	} 
  return out;
}

