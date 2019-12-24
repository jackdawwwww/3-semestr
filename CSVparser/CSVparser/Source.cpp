#include <iostream>
#include "CSVparser.h"

int main() {

	std::ifstream file("in.csv");

	CSVparser<int, std::string> parser(file);

	for (const std::tuple<int, std::string>& pars : parser) {
		std::cout << pars << std::endl;
	}

	return 0;
}