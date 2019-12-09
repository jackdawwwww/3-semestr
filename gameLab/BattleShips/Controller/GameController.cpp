#include "GameController.h"
#include "../Gamer/ConsoleGamer.h"
#include "../Gamer/RandomGamer.h"
#include "../Gamer/SmartGamer.h"
#include "../View/GameView.h"
#include "..//Gamer/GamerFactory.h"
#include <memory>
#include <cstdlib>
#include <ctime>

using namespace std;


Gamer* GameController::createGamer(GamerMode mode) {
	unique_ptr<GamerFactory> gm(new GamerFactory);
	return gm->createGamer(mode);
}

GameController::GameController(const GamerMode& mode1, const GamerMode& mode2) {
		gamerTurn = true;
		gameStep = make_pair(0, 0);
		gameScore = make_pair(0, 0);
		gamerMode = mode1;
		enemyMode = mode2;
		hitEnemy = 0;
		hitGamer = 0;
}

void GamerTurn(GameView& view, Gamer* gamer, Gamer* enemy, pair<size_t, size_t>& gameStep, bool& gamerTurn, GameModel enemyBoard,
	int& hitEnemy, int maxDeskCount, GameMode& mode, pair<size_t,size_t>& gameScore, int num) {
	view.drawAttack(gamer->attackBoard);
	gameStep = gamer->attack();

	if (gamer->attackBoard.getCell(gameStep.first, gameStep.second) != Cell::EMPTY) {
		if (num == 1) gamerTurn = false;
		if (num == 2) gamerTurn = true;
		return;
	}
	if (enemyBoard.getCell(gameStep.first, gameStep.second) == Cell::SHIP) {
		gamer->attackBoard.setCell(gameStep.first, gameStep.second, Cell::HIT);
		hitEnemy++;

		if (hitEnemy == maxDeskCount) {
			mode = GameMode::GAMER_WIN;
			++gameScore.first;
			view.drawAttack(gamer->attackBoard);
			return;
		}
	}
	else {
		gamer->attackBoard.setCell(gameStep.first, gameStep.second, Cell::MISS);
		if (num == 1) gamerTurn = false;
		if (num == 2) gamerTurn = true;
	}
}
void GameController::start(const size_t& countGames) {
	if (countGames <= 0) return;
	constexpr auto maxDeskCount = SINGE_DESK + 2 * TWO_DESK + 3 * THREE_DESK + 4 * FOUR_DESK;
	srand(static_cast<unsigned int>(time(nullptr)));
	for (size_t i = 0; i < countGames; i++) {
		mode = GameMode::GAME_IN_PROCESS;
		gamer = createGamer(gamerMode);
		enemy = createGamer(enemyMode);
		gamerBoard = GameModel();
		enemyBoard = GameModel();
		gamer->fillBoard(gamerBoard);
		enemy->fillBoard(enemyBoard);

		while (mode == GameMode::GAME_IN_PROCESS) {
			while (gamerTurn) {
				GamerTurn(view, gamer, enemy, gameStep, gamerTurn, enemyBoard, hitEnemy, maxDeskCount, mode, gameScore, 1);
			}

			while (!gamerTurn) {
				GamerTurn(view, enemy, gamer, gameStep, gamerTurn, gamerBoard, hitGamer, maxDeskCount, mode, gameScore, 2);
			}
		}
		view.printScore(gameScore);;
		view.printLapWinner(mode, i+1);

		hitEnemy = 0;
		hitGamer = 0;
		delete gamer;
		delete enemy;
	}
	view.printWinner(mode);
}
