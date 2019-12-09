#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "../Model/GameModel.h"
#include "../include/Modes.h"

using namespace std;

class GameView {
public:
	void drawBoard(const GameModel&);
	void drawAttack(const GameModel&);
	void printWinner(const GameMode&);
	void printScore(const pair<size_t, size_t>&);

};

#endif //GAMEVIEW_H
