#include "RandomGamer.h"
#include <string>
#include <cmath>
#include "../include/GameSettings.h"
#include "../View/GameView.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void RandomGamer::inputCoords(int& x, int& y, GameModel& board) {
	x = rand() % 10;
	y = rand() % 10;
	while (x < 0 || x > 9 || y < 0 || y > 9 || board.getCell(x, y) != Cell::EMPTY) {;
		inputCoords(x, y, board);
	}
}

void RandomGamer::askCoords(int& x0, int& y0, int& x1, int& y1, GameModel& board) {
	size_t stepx = rand() % 2;
	size_t stepy = 1 - stepx;
	inputCoords(x0, y0, board);
	while (!board.possibleToSet(x0, y0)) {
		inputCoords(x0, y0, board);
	}
	x1 = x0 + stepx;
	y1 = y0 + stepy;
	while (!board.possibleToSet(x1, y1)) {
		askCoords(x0, y0, x1, y1, board);
	}
}

pair<size_t, size_t> RandomGamer::attack() {
	size_t x, y;
	x = rand() % 10;
	y = rand() % 10;
	return make_pair(x, y);
}

void RandomGamer::fillBoard(GameModel& board) {
	int x0, y0, x1, y1;
	GameView view;
	view.drawBoard(board);

	for (int i = 0; i < FOUR_DESK; ++i) {
		askCoords(x0, y0, x1, y1, board);
		while ((x0 + 3 * (x1 - x0)) < 0 || (x0 + 3 * (x1 - x0)) > 9 || (y0 + 3 * (y1 - y0)) < 0 || (y0 + 3 * (y1 - y0)) > 9) {
			askCoords(x0, y0, x1, y1, board);
		}
		while (!((x0 - x1) == 0 && ((abs(y0 - y1)) == 1) || ((y0 - y1) == 0 && ((abs(x0 - x1)) == 1))) || !board.possibleToSet(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0)) || !board.possibleToSet(x0 + 3 * (x1 - x0), y0 + 3 * (y1 - y0))) {
			inputCoords(x1, y1, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		board.setCell(x1, y1, Cell::SHIP);
		board.setCell(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0), Cell::SHIP);
		board.setCell(x0 + 3 * (x1 - x0), y0 + 3 * (y1 - y0), Cell::SHIP);

		view.drawBoard(board);
	}

	for (int i = 0; i < THREE_DESK; ++i) {
		askCoords(x0, y0, x1, y1, board);
		while ((x0 + 2 * (x1 - x0)) < 0 || (x0 + 2 * (x1 - x0)) > 9 || (y0 + 2 * (y1 - y0)) < 0 || (y0 + 2 * (y1 - y0)) > 9) {
			askCoords(x0, y0, x1, y1, board);
		}
		while (!(((x0 - x1) == 0 && ((abs(y0 - y1)) == 1)) || ((y0 - y1) == 0 && ((abs(x0 - x1)) == 1))) || !board.possibleToSet(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0))) {
			inputCoords(x1, y1, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		board.setCell(x1, y1, Cell::SHIP);
		board.setCell(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0), Cell::SHIP);
		view.drawBoard(board);
	}

	for (int i = 0; i < TWO_DESK; ++i) {
		askCoords(x0, y0, x1, y1, board);
		while ((x0 + (x1 - x0)) < 0 || (x0 + (x1 - x0)) > 9 || (y0 + (y1 - y0)) < 0 || (y0 + (y1 - y0)) > 9) {
			askCoords(x0, y0, x1, y1, board);
		}
		while (((x0 - x1) != 0 || (abs(y0 - y1)) != 1) && ((y0 - y1) != 0 || (abs(x0 - x1)) != 1)) {
			inputCoords(x1, y1, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		board.setCell(x1, y1, Cell::SHIP);

		view.drawBoard(board);
	}


	for (int i = 0; i < SINGE_DESK; ++i) {
		inputCoords(x0, y0, board);
		while (!board.possibleToSet(x0, y0)) {
			inputCoords(x0, y0, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		view.drawBoard(board);
	}
	
}