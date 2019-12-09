#ifndef GAMER_H
#define GAMER_H

#include <iostream>
#include "../Model/GameModel.h"
#include "../include/Modes.h"

class Gamer {
public:
	virtual std::pair<size_t, size_t> attack() = 0;
	virtual void fillBoard(GameModel&) = 0;
	virtual void inputCoords(int&, int&, GameModel&) = 0;
	virtual void askCoords(int&, int&, int&, int&, GameModel&) = 0;

	GameModel attackBoard;

	Gamer() {
		attackBoard = GameModel();
	}
};

#endif //GAMER_H