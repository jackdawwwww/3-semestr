#include <iostream>
#include "../BattleShips/Controller/GameController.h"
#include "Getopt-for-Visual-Studio-master/getopt.h"
#include <vector>
#include <string>

void readInput(GamerMode& first, GamerMode& second, int& count, char** argv, int argc, bool& flag) {
	char* opts = _strdup("hc:f:s:");
	const struct option long_options[] = {
			{"help", 0, nullptr, 'h'},
			{"second", 1, nullptr, 's'},
			{"first", 1, nullptr, 'f'},
			{"count", 1, nullptr, 'c'}
	};

	int opt;
	while ((opt = getopt_long(argc, argv, opts, long_options, nullptr)) != -1) {
		switch (opt) {
		case 'h': flag = true;
			std::cout << "  --help, -h  \tPrint usage and exit" << endl;
			std::cout << "  --count, -c  \tGame session count" << endl;
			std::cout << "  --first, -f  \tFirst gamer type : random, smart, console" << endl;
			std::cout << "  --second, -s  \tSecond gamer type: random, smart, console" << endl;
			break;
		case 'c':
			count = atoi(optarg);
			break;
		case 'f':
			if (std::string(optarg) == "console") first = GamerMode::CONSOLE;
			if (std::string(optarg) == "smart") first = GamerMode::SMART;
			break;
		case 's':
			if (std::string(optarg) == "console") second = GamerMode::CONSOLE;
			if (std::string(optarg) == "smart") second = GamerMode::SMART;
			break;
		}
	}

	delete opts;
}


int main(int argc, char** argv) {
	GamerMode first = GamerMode::RANDOM;
	GamerMode second = GamerMode::RANDOM;
	int countGames = 1;
	bool help = false;

	readInput(first, second, countGames, argv, argc, help);

	if (!help) {
		GameController gm(first, second);
		gm.start(countGames);
	}

	return 0;
}