#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include "../include/GameSettings.h"
#include "../include/Modes.h"

using namespace std;


enum class Cell { EMPTY, SHIP, MISS, HIT};

class GameModel {
private:
	Cell board[SIZE][SIZE]{};
public:
	const Cell& getCell(const size_t&, const size_t&) const;
	void setCell(const size_t&, const size_t&, const Cell&);
	bool possibleToSet(const size_t&, const size_t&);
	GameModel();
};

#endif //GAMEMODEL_H
