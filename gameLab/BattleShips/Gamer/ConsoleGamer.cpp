#include <string>
#include <cmath>
#include "ConsoleGamer.h"
#include "../include/GameSettings.h"
#include "../View/GameView.h"

using namespace std;

void ConsoleGamer::inputCoords(int& x, int& y, GameModel& board) {
	cout << "x: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	while (x < 0 || x > 9 || y < 0 || y > 9 || board.getCell(x, y) != Cell::EMPTY) {
		cout << "\nWrite correct coords\n";
		inputCoords(x, y, board);
	}
}

void ConsoleGamer::askCoords(int& x0, int& y0, int& x1, int& y1, GameModel& board) {
	cout << "x0 y0:\n";
	inputCoords(x0, y0, board);
	while (!board.possibleToSet(x0, y0)) {
		cout << "\nWrite correct coords\nx0 y0:\n";
		inputCoords(x0, y0, board);
	}
	cout << "x1 y1:\n";
	inputCoords(x1, y1, board);
	while (!board.possibleToSet(x1, y1)) {
		cout << "\nWrite correct coords\nx1 y1:\n";
		inputCoords(x1, y1, board);
	}
}

pair<size_t, size_t> ConsoleGamer::attack() {
	size_t x, y;
	cout << "Input coord \nx: ";
	cin >> x;
	cout << "y: ";
	cin >> y;
	return make_pair(x, y);
}

void ConsoleGamer::fillBoard(GameModel& board) {
	int x0, y0, x1, y1;
	GameView view;

	view.drawBoard(board);

	for (int i = 0; i < SINGE_DESK; ++i) {
		cout << "Input coodrs x y for single ship\n";
		inputCoords(x0, y0, board);
		while (!board.possibleToSet(x0, y0)) {
			cout << "\nWrite correct coords\n";
			inputCoords(x0, y0, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		view.drawBoard(board);
	}


	for (int i = 0; i < TWO_DESK; ++i) {
		cout << "Input coodrs x0 y0, x1 y1 for two-desk ship\n";
		askCoords(x0, y0, x1, y1, board);
		while (((x0 - x1) != 0 || (abs(y0 - y1)) != 1) && ((y0 - y1) != 0 || (abs(x0 - x1))!= 1)) {
			cout << "\nWrite correct coords\n";
			inputCoords(x1, y1, board);
		}
		board.setCell(x0, y0, Cell::SHIP);
		board.setCell(x1, y1, Cell::SHIP);

		view.drawBoard(board);
	}

	for (int i = 0; i < THREE_DESK; ++i) {
		cout << "Input two guiding coodrs x0 y0, x1 y1 for three-desk ship\n";
		askCoords(x0, y0, x1, y1, board);
		while ((x0 + 2 * (x1 - x0)) < 0 && (x0 + 2 * (x1 - x0)) > 9 && (y0 + 2 * (y1 - y0)) < 0 && (y0 + 2 * (y1 - y0)) > 9) {
			cout << "\nWrite correct coords\n";
			askCoords(x0, y0, x1, y1, board);
		}
		while (!(((x0 - x1) == 0 && ((abs(y0 - y1)) == 1)) || ((y0 - y1) == 0 && ((abs(x0 - x1)) == 1))) || !board.possibleToSet(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0))) {
			cout << "\nWrite correct coords\n";
			inputCoords(x1, y1, board);
		}
			board.setCell(x0, y0, Cell::SHIP);
			board.setCell(x1, y1, Cell::SHIP);
			board.setCell(x0 + 2*(x1 - x0), y0 + 2*(y1 - y0), Cell::SHIP);
		view.drawBoard(board);
	}


	for (int i = 0; i < FOUR_DESK; ++i) {
		cout << "Input two guiding coodrs x0 y0, x1 y1 for four-desk ship\n";
		askCoords(x0, y0, x1, y1, board);
		while ((x0 + 3 * (x1 - x0)) < 0 && (x0 + 3 * (x1 - x0)) > 9 && (y0 + 3 * (y1 - y0)) < 0 && (y0 + 3 * (y1 - y0)) > 9) {
			cout << "\nWrite correct coords\n";
			askCoords(x0, y0, x1, y1, board);
		}
		while (!((x0 - x1) == 0 && ((abs(y0 - y1)) == 1) || ((y0 - y1) == 0 && ((abs(x0 - x1)) == 1))) || !board.possibleToSet(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0)) || !board.possibleToSet(x0 + 3 * (x1 - x0), y0 + 3 * (y1 - y0))) {
			cout << "\nWrite correct coords\n";
			inputCoords(x1, y1, board);
		}
			board.setCell(x0, y0, Cell::SHIP);
			board.setCell(x1, y1, Cell::SHIP);
			board.setCell(x0 + 2 * (x1 - x0), y0 + 2 * (y1 - y0), Cell::SHIP);
			board.setCell(x0 + 3 * (x1 - x0), y0 + 3 * (y1 - y0), Cell::SHIP);

		view.drawBoard(board);
	}
}