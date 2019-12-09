#ifndef SMARTGAMER_H
#define SMARTGAMER_H

#include "Gamer.h"
#include "../Model/GameModel.h"
using namespace std;
class GameModel;

class SmartGamer : public Gamer {
	pair<size_t, size_t> attack() override;
	void fillBoard(GameModel&) override;
	void askCoords(int&, int&, int&, int&, GameModel&) override;
	void inputCoords(int&, int&, GameModel&) override;
};


#endif //SMARTGAMER_H