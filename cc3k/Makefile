CXX = g++-5
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
EXEC = cc3k
OBJECTS = subject.o textdisplay.o event.o item.o potion.o treasure.o merchanthorde.o smalltreasure.o normaltreasure.o dragonhorde.o character.o enemy.o player.o dwarf.o goblin.o human.o dragon.o elf.o halfling.o merchant.o shade.o troll.o drow.o orc.o vampire.o floor.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
