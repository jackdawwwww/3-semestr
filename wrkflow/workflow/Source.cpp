#include<iostream>
#include"Commands.h"
#include"executor.h"
#include"Exceptions.h"
using namespace std;
enum class keys { NO, EX, IN, OUT, BOTH};

void exceptions(string str) {
	try {
		 throw commands_exceptions("in keys " + str);
	}
	catch (commands_exceptions& e) {
		cout << e.error() << endl;
	}
}
keys key_check(pair<bool, bool> info, int num) {
	if (info.first == false || info.second == false) {
		if (info.first == false && info.second == false) {
			if (num < 6) {
				exceptions("expected in and out files");
				return keys::EX;
			}
			else return keys::BOTH;
		}
		else{
			if (info.first == false) {
				if (num < 4) {
					exceptions("expected in file");
					return keys::EX;
				}
				else return keys::IN;
			}
			else {
				if (num < 4) {
					exceptions("expected out file");
					return keys::EX;
				}
				else return keys::OUT;
			}
		}
	}
	return keys::NO;
}

int main(int argc, char** argv) {
	if (argc < 1) {
		exceptions("expected workflow file");
		return -1;
	}
	executor pars(argv[1]);
	const char* str1 = "-i", *str2 = "-o";

	pair<bool,bool> info = pars.read_block();
	if (pars.my_exceptions == true) return -1;

	keys check = key_check(info, argc);
	switch (check)
	{
	case keys::NO:
		pars.read_last_string();
		break;
	case keys::EX:
		return -1;
	case keys::IN:
		if (strcmp(argv[2], "-i")) {
			exceptions("expected in file");
			return -1;
		}
		pars.add_input(argv[3]);
		break;
	case keys::OUT:
		if (strcmp(argv[2], "-o")) {
			exceptions("expected out file");
			return -1;
		}
		pars.added_out_file = true;
		pars.read_last_string();
		pars.add_output(argv[3]);
		break;
	case keys::BOTH:
		if ((strcmp(argv[2], "-i")|| strcmp(argv[4], "-o")) && (strcmp(argv[2], "-i") || strcmp(argv[2], "-o"))) {
			exceptions("expected in and out files");
			return -1;
		}
		pars.added_out_file = true;
		if (!strcmp(argv[2], "-i")) {
			pars.add_input(argv[3]);
			pars.read_last_string();
			pars.add_output(argv[5]);
		}
		else {
			pars.add_input(argv[5]);
			pars.read_last_string();
			pars.add_output(argv[3]);
		}
		break;
	}
	if (pars.my_exceptions) return -1;
	pars.work();
	return 0;
}