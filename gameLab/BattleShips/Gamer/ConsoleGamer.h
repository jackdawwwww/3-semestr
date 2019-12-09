#ifndef CONSOLEGAMER_H
#define CONSOLEGAMER_H


#include "Gamer.h"
using namespace std;

class ConsoleGamer : public Gamer {
	pair<size_t, size_t> attack() override;
	void fillBoard(GameModel&) override;
	void inputCoords(int&, int&, GameModel&) override;
	void askCoords(int&, int&, int&, int&, GameModel&) override;
};


#endif //CONSOLEGAMER_H