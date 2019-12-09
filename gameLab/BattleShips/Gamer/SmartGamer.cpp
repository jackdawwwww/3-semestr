#include "SmartGamer.h"
#include <string>
#include <vector>
#include "../include/GameSettings.h"
#include "../View/GameView.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void SmartGamer::inputCoords(int& x, int& y, GameModel& board) {}

void SmartGamer::askCoords(int& x0, int& y0, int& x1, int& y1, GameModel& board) {}

pair<size_t, size_t> SmartGamer::attack() {
	size_t x, y, step;
	while (true) {
		x = rand() % SIZE;
		y = rand() % SIZE;
		if (attackBoard.getCell(x, y) == Cell::EMPTY) {
			return make_pair(x, y);
		}
		if (attackBoard.getCell(x, y) == Cell::HIT) {
			if ((x > 1) && attackBoard.getCell(x - 1, y) == Cell::HIT || (x < 8) && attackBoard.getCell(x + 1, y) == Cell::HIT) {
				if ((x > 2) && attackBoard.getCell(x - 2, y) == Cell::EMPTY) {
					return make_pair(x - 2, y);
				}
				if ((x < 7) && attackBoard.getCell(x + 2, y) == Cell::EMPTY) {
					return make_pair(x + 2, y);
				}
				continue;
			}
			if ((y > 1) && attackBoard.getCell(x, y - 1) == Cell::HIT || (y < 8) && attackBoard.getCell(x, y + 1) == Cell::HIT) {
				if ((y > 2) && attackBoard.getCell(x, y - 2) == Cell::EMPTY) {
					return make_pair(x, y - 2);
				}
				if ((y < 7) && attackBoard.getCell(x, y + 2) == Cell::EMPTY) {
					return make_pair(x, y + 2);
				}
				else {
					while (1) {
						step = rand() % (SIZE - x);
						for (size_t i = 0; i < step; i++) {
							step -= i;
							if (x < 9 - step && attackBoard.getCell(x + step, y) == Cell::EMPTY) return make_pair(x + step, y);
							if (y < 9 - step && attackBoard.getCell(x, y + step) == Cell::EMPTY) return make_pair(x, y + step);
							if (x > step && attackBoard.getCell(x - step, y) == Cell::EMPTY) return make_pair(x - step, y);
							if (y > step && attackBoard.getCell(x, y + step) == Cell::EMPTY) return make_pair(x, y - step);

							if (x < 9 - step && y < 9 - step && attackBoard.getCell(x + step, y + step) == Cell::EMPTY) return make_pair(x + step, y + step);
							if (y < 9 - step && x > step && attackBoard.getCell(x, y + step) == Cell::EMPTY) return make_pair(x - step, y + step);
							if (x > step && y > step && attackBoard.getCell(x - step, y) == Cell::EMPTY) return make_pair(x - step, y - step);
							if (y > step && x < 9 - step && attackBoard.getCell(x, y + step) == Cell::EMPTY) return make_pair(x + step, y - step);
						}
						break;
					}
				}
			}

		}
	}
}


void SmartGamer::fillBoard(GameModel& board) {
	vector<pair<int, int>> coord = { make_pair(4,0), make_pair(6,4), make_pair(4,8), make_pair(9,0),
		make_pair(0,5), make_pair(0,6), make_pair(0,8), make_pair(0,9), make_pair(2,4),make_pair(2,5),
		make_pair(2,0), make_pair(2,1), make_pair(2,7), make_pair(2,8),
		make_pair(0,0), make_pair(0,1) };

	GameView view;
	view.drawBoard(board);
	int i = 0;

	for (; i < SINGE_DESK; ++i) {
		board.setCell(coord[i].first, coord[i].second, Cell::SHIP);
		view.drawBoard(board);
	}

	for (int j = 0; j < TWO_DESK; j++, i += 2) {
		board.setCell(coord[i].first, coord[i].second, Cell::SHIP);
		board.setCell(coord[i + 1].first, coord[i + 1].second, Cell::SHIP);
		view.drawBoard(board);
	}
	for (int j = 0; j < THREE_DESK; j++, i += 2) {
		board.setCell(coord[i].first, coord[i].second, Cell::SHIP);
		board.setCell(coord[i + 1].first, coord[i + 1].second, Cell::SHIP);
		board.setCell(coord[i].first + 2 * (coord[i + 1].first - coord[i].first), coord[i].second + 2 * (coord[i + 1].second - coord[i].second), Cell::SHIP);
		view.drawBoard(board);
	}

	board.setCell(coord[i].first, coord[i].second, Cell::SHIP);
	board.setCell(coord[i + 1].first, coord[i + 1].second, Cell::SHIP);
	board.setCell(coord[i].first + 2 * (coord[i + 1].first - coord[i].first), coord[i].second + 2 * (coord[i + 1].second - coord[i].second), Cell::SHIP);
	board.setCell(coord[i].first + 3 * (coord[i + 1].first - coord[i].first), coord[i].second + 3 * (coord[i + 1].second - coord[i].second), Cell::SHIP);

	view.drawBoard(board);
}