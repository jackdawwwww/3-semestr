#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_
#include "../include/Modes.h"
#include "../View/GameView.h"
#include "../Gamer/Gamer.h"

using namespace std;

class GameController {
private:
	bool gamerTurn;
	pair<size_t, size_t> gameStep;
	pair<size_t, size_t> gameScore;
	GameMode mode;
	GameView view;
	GamerMode gamerMode, enemyMode;
	GameModel gamerBoard;
	GameModel enemyBoard;
	Gamer* gamer,*enemy;
	int hitGamer, hitEnemy;
public:
	GameController(const GamerMode&, const GamerMode&);
	void start(const size_t& countGames);
	Gamer* createGamer(GamerMode);
	~GameController() {}
};

#endif  //GAMECONTROLLER_H_
