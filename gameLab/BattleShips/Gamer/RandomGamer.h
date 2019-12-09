#ifndef RANDOMGAMER_H
#define RANDOMGAMER_H

#include "Gamer.h"
using namespace std;

class RandomGamer : public Gamer {
	pair<size_t, size_t> attack() override;
	void fillBoard(GameModel&) override;
	void inputCoords(int&, int&, GameModel&) override;
	void askCoords(int&, int&, int&, int&, GameModel&) override;
};


#endif //RANDOMGAMER_H