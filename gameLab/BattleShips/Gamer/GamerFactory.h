#ifndef  GAMERFACTORY_H
#define  GAMERFACTORY_H

#include "Gamer.h"
#include "ConsoleGamer.h"
#include "RandomGamer.h"
#include "SmartGamer.h"
#include "../Model/GameModel.h"

using namespace std;
class Gamer;

class GamerFactory {
public:
	Gamer* createGamer(GamerMode& gamerMode) {
		switch (gamerMode) {
		case GamerMode::CONSOLE: return new ConsoleGamer;
		case GamerMode::RANDOM: return new RandomGamer;
		case GamerMode::SMART: return new SmartGamer;
		default: return nullptr;
		}
	}
};


#endif //  GAMERFACTORY_H

