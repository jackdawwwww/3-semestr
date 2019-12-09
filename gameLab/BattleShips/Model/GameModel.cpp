#include "GameModel.h"
#include "../include/Modes.h"

GameModel::GameModel() {
	for (auto& i : board) {
		for (auto& j : i) {
			j = Cell::EMPTY;
		}
	}
}

const Cell& GameModel::getCell(const size_t& x, const size_t& y) const {
	return board[y][x];
}

void GameModel::setCell(const size_t& x, const size_t& y, const Cell& new_cell) {
	board[y][x] = new_cell;
}

bool GameModel::possibleToSet(const size_t& y, const size_t& x) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (!((x + i) >= 0 && (x + i) <= 9 && (y + j) >= 0 && (y + j) <= 9)) continue;
			if (board[x + i][y + j] != Cell::EMPTY) return false;
		}
	}
	return true;
}
