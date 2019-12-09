#include "GameView.h"
#include "../include/Modes.h"
#include <iostream>

using namespace std;

void GameView::drawBoard(const GameModel& board) {
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
	for (size_t i = 0; i < 10; ++i) {
		cout << i << ' ' << "|";
		for (size_t j = 0; j < 10; ++j) {
			char c = board.getCell(j, i) == Cell::EMPTY ? '_' : '$';
			cout << c << '|';
		}
		cout << endl;
	}
}

void GameView::drawAttack(const GameModel& board) {
	cout << "\n\n\n\n\n\n\n\n\n";
	cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
	for (size_t i = 0; i < 10; ++i) {
		cout << i << ' ' << "|";
		for (size_t j = 0; j < 10; ++j) {
			char c;
			switch (board.getCell(j, i)) {
			case Cell::EMPTY: c = '_'; break;
			case Cell::HIT: c = 'x'; break;
			case Cell::MISS: c = 'o'; break;
			default: c = '\0';
			}
			cout << c << '|';
		}
		cout << endl;
	}
}


void GameView::printScore(const pair<size_t, size_t>& score) {
	cout << "First player score: " << score.first << endl;
	cout << "Second player score: " << score.second << endl;
}

void GameView::printWinner(const GameMode& mode) {
	if (mode == GameMode::ENEMY_WIN) {
		cout << "Second player win!" << endl;
	}
	else cout << "First player win!" << endl;
}

