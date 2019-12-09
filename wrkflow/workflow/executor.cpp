<<<<<<< HEAD
﻿#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
#include"executor.h"
#include"Factory.h"
#include"Commands.h"
#include"Exceptions.h"
#include<exception>
#include<memory>
#include"str_switch.h"

map<string, short> cmnds = {{"readfile", 1}, {"writefile", 1}, {"grep", 1}, {"replace", 2}, {"dump", 1}, {"sort", 0}};

executor::executor(string file) {
	pars_file.open(file);
	curr_pos_in_pars_file = 0;
	regime = Regime::NUMBER;
	try {
		pars_file.exceptions(ifstream::failbit | ifstream::badbit);
	}
	catch (exception const& ex) {
		cout << ex.what() << endl;
	}
}
executor::~executor() {
	pars_file.close();
}
string executor::get_word(string str, size_t words_num) const {
	string tmp, delimitr = " ";
	size_t prev = 0, next, delta = delimitr.length(), num = 0;
	bool flag = true;
	while (flag) {
		if ((next = str.find(delimitr, prev)) != string::npos) {
			tmp = str.substr(prev, next - prev);
		}
		else {
			tmp = str.substr(prev);
			flag = false;
		}
		if (num == words_num) return tmp;
		prev = next + delta;
		num++;
		tmp.clear();
	}
	return "";
}

string executor::get_word(size_t num_in_list, size_t num) const {
	string str;
	list<pair<string, Commands*>>::const_iterator it = commands_list.begin();
	int i = 0;
	for (auto t: commands_list){
		if (i == num_in_list) {
			str = t.first;
			break;
		}
		i++;
	}
	str = get_word(str, num);
	return str;
}

void executor::read_last_string() {
	string buf, tmp, delimitr = " ";
	unsigned int command_number;
	bool last_word = false;
	size_t next, delta = delimitr.length();
	while (!(this->pars_file).eof()) {
		getline(pars_file, buf);

		while (!last_word) {
			if ((next = buf.find(delimitr, curr_pos_in_pars_file)) != string::npos) {
				tmp = buf.substr(curr_pos_in_pars_file, next - curr_pos_in_pars_file);
			}
			else {
				tmp = buf.substr(curr_pos_in_pars_file);
				last_word = true;
			}

			switch (regime) {
			case Regime::TAIL: {
				if (tmp == "->") {
					regime = Regime::NEXT;
					curr_pos_in_pars_file = next + delta;
				}
				break;
			}

			case Regime::NEXT: {
				command_number = stoi(tmp);
				push_to_list(command_number);
				curr_pos_in_pars_file = next + delta;
				regime = Regime::TAIL;
				break;
			}
			}
			tmp.clear();
		}
		tmp.clear();
		last_word = false;
		buf.clear();
	}
	try {
		if (curr_opened && !added_out_file)throw parsing_exceptions("Text is not saved!");
	}
	catch (parsing_exceptions& ex) {
		cout << ex.error() << endl;
		my_exceptions = true;
	}
}

pair<bool,bool> executor::read_block() {
	string buf, tmp, delimitr = " ";
	size_t  next, delta = delimitr.length();
	string command_and_parametrs;
	short parameters_count = -1;
	int command_number;
	bool begin = false, end = false, last_word = false, input = false, output = false;

	while (!(this->pars_file).eof()) {
		getline(pars_file, buf);
<<<<<<< HEAD
		if (buf == "desc") {
=======
		if (buf == "dsed") {
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
			try {
				if (begin == false) {
					begin = true;
					continue;
				}
				else throw parsing_exceptions("in block begin");
			}
			catch (parsing_exceptions& e) {
				cout << e.error() << endl;
				my_exceptions = true;
				return make_pair(false, false);
			}
		}

		if (buf == "csed") {
			try{ 
				if (end == false) {
					end = true;
					regime = Regime::NEXT;
					return make_pair(input, output);
				}
				else throw parsing_exceptions("block end");
			}
			catch (parsing_exceptions& e) {
				cout << e.error() << endl;
				my_exceptions = true;
				return make_pair(false, false);
			}
		}

		while(!last_word) {
			if ((next = buf.find(delimitr, curr_pos_in_pars_file)) != string::npos) {
				tmp = buf.substr(curr_pos_in_pars_file, next - curr_pos_in_pars_file);
			}
			else {
				tmp = buf.substr(curr_pos_in_pars_file);
				last_word = true;
			}

			switch (regime) {
			case Regime::NUMBER: {
					try {
						command_number = stoi(tmp);
					}
					catch (exception const& ex) {
						parsing_exceptions pars_ex(typeid(ex).name());
						cout <<pars_ex.error()<< endl;
						my_exceptions = true;
						return make_pair(false, false);
					}
					try {
						if (!com_map[command_number].empty())throw parsing_exceptions("Not unique number");
						if (command_number < 0)throw parsing_exceptions("Negative number");
					}
					catch (parsing_exceptions& ex) {
						cout << ex.error() << endl;
						my_exceptions = true;
						return make_pair(false, false);
					}
				regime = Regime::ASSIGNMENT;
				curr_pos_in_pars_file = next + delta;
				break;
			}

			case Regime::ASSIGNMENT: {
				try {
					if (tmp != "=") throw parsing_exceptions("assign error");
				}
				catch (parsing_exceptions& ex) {
					cout << ex.error() << endl;
					my_exceptions = true;
					return make_pair(false, false);
				}
				regime = Regime::COMMAND;
				curr_pos_in_pars_file = next + delta;
				break;
			}

			case Regime::COMMAND: {
				for (auto t: cmnds) {
					if (tmp == t.first) {
						parameters_count = t.second;
						command_and_parametrs += tmp;
						curr_pos_in_pars_file = next + delta;
						if (parameters_count == 0) {
							com_map[command_number] = command_and_parametrs;
							regime = Regime::NUMBER;
							command_and_parametrs.clear();
							break;
						}
						regime = Regime::OPERATORS;
						if (t.first == "readfile") input = true;
						if (t.first == "writefile") output = true;
						break;
					}
				}
				try {
					if (regime == Regime::COMMAND) throw parsing_exceptions("Invalid command");
				}
				catch (parsing_exceptions& ex) {
					cout << ex.error() << endl;
					my_exceptions = true;
					return make_pair(false, false);
				}
				break;
			}
			case Regime::OPERATORS: {
				if (parameters_count != 0) {
					command_and_parametrs += ' ';
					command_and_parametrs += tmp;
					parameters_count--;
					curr_pos_in_pars_file = next + delta;
				}
				if (parameters_count == 0) {
					regime = Regime::NUMBER;
					com_map[command_number] = command_and_parametrs;
					command_and_parametrs.clear();
				}
				break;
			}
			}
			tmp.clear();
		}
		try {
			if (regime == Regime::OPERATORS && last_word) throw parsing_exceptions("Not enough parameters");
		}
		catch (parsing_exceptions& ex) {
			cout << ex.error() << endl;
			my_exceptions = true;
			return make_pair(false, false);
		}
		tmp.clear();
		last_word = false;
		buf.clear();

	}
	return make_pair(input, output);
}

bool no_text_exception(bool flag, string str) {
	try {
		if (!flag) throw parsing_exceptions("No text to " + str);
	}
	catch (parsing_exceptions& ex) {
		cout << ex.error() << endl;
		return true;
	}
	return false;
}

void executor::add_input(string input) {
	Commands* cm;
	string str = "readfile " + input;
	com_map[-1] = input;
	
	unique_ptr<read_factory> rd(new read_factory);
	curr_opened = true;
	try {
		cm = rd->create_command();
	}
	catch (commands_exceptions& e) {
		cout << e.error() << endl;
		my_exceptions = true;
		return;
	}
	commands_list.push_front(make_pair(str, cm));
}

void executor::add_output(string output) {
	com_map[com_map.size()] = "writefile " + output;
	push_to_list(com_map.size()-1);
}

void executor::push_to_list(int j) {
<<<<<<< HEAD

=======
	Commands* cm = nullptr;
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
	try {
		if (com_map[j].size() == 0) throw parsing_exceptions("Unknown number!");
	}
	catch (parsing_exceptions& ex) {
		cout << ex.error() << endl;
		my_exceptions = true;
		return;
	}
	string com = get_word(com_map[j], 0);
	for (auto t : cmnds) {
		if (com == t.first) {
			SWITCH(com) {
				CASE("readfile") : {
					try {
						if (curr_opened) throw parsing_exceptions("Second file to reading!");
					}
					catch (parsing_exceptions& ex) {
						cout << ex.error() << endl;
						break;
					}

<<<<<<< HEAD
					unique_ptr<read_factory> cm(new read_factory);
					curr_opened = true;
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
=======
					unique_ptr<read_factory> rd(new read_factory);
					curr_opened = true;
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
					break;
				}
				CASE("writefile") : {
					if (!added_out_file && no_text_exception(curr_opened, "write")) {
						my_exceptions = true;
						return;
					}
					curr_opened = false;
<<<<<<< HEAD
					unique_ptr<write_factory> cm(new write_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
=======
					unique_ptr<write_factory> wr(new write_factory);
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
					break;
				}
				CASE("grep") : {
					if (no_text_exception(curr_opened, "grep")) {
						my_exceptions = true;
						return;
					}

<<<<<<< HEAD
					unique_ptr<grep_factory> cm(new grep_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
=======
					unique_ptr<grep_factory> gr(new grep_factory);
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
				}
				CASE("replace") : {
					if (no_text_exception(curr_opened, "replace")) {
						my_exceptions = true;
						return;
					}

<<<<<<< HEAD
					unique_ptr<replace_factory> cm(new replace_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
=======
					unique_ptr<replace_factory> rp(new replace_factory);
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
					break;
				}
				CASE("dump") : {
					if (no_text_exception(curr_opened, "dump")) {
						my_exceptions = true;
						return;
					}

<<<<<<< HEAD
					unique_ptr<dump_factory> cm(new dump_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
=======
					unique_ptr<dump_factory> read(new dump_factory);
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
					break;
				}
				CASE("sort") : {
					if (no_text_exception(curr_opened, "sort")) {
						my_exceptions = true;
						return;
					}

<<<<<<< HEAD
					unique_ptr<sort_factory> cm(new sort_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
			}
=======
					unique_ptr<sort_factory> sort(new sort_factory);
					break;
				}
			}
			commands_list.push_back(make_pair(com_map[j], cm));
>>>>>>> ffe95a078f7cd3be62f64ce546ba251cbe744f7a
			return;
		}
	}
}

void executor::work() {
	int i = 0;
	for (auto &t: commands_list) {
		Commands* cm = t.second;
		cm->doing(this, i);
		i++;
	}
}

void executor::edit_text(string new_text) {
	this->text = new_text;
}

void executor::edit_text(bool end) {
	if (end) {
		this->text.clear();
	}
}

string executor::get_text() const {
	return this->text;
}

=======
﻿#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
#include"executor.h"
#include"Factory.h"
#include"Commands.h"
#include"Exceptions.h"
#include<exception>
#include<memory>
#include"str_switch.h"

const map<string, short> cmnds = {{"readfile", 1}, {"writefile", 1}, {"grep", 1}, {"replace", 2}, {"dump", 1}, {"sort", 0}};

executor::executor(string file) {
	pars_file.open(file);
	curr_pos_in_pars_file = 0;
	regime = Regime::NUMBER;
	try {
		pars_file.exceptions(ifstream::failbit | ifstream::badbit);
		if (pars_file.bad() || pars_file.fail()) throw commands_exceptions("no read access or no file");
	}
	catch (commands_exceptions & e) {
		cout << e.error() << endl;
		return;
	}
}
executor::~executor() {
	pars_file.close();
}
string executor::get_word(string str, size_t words_num) const {
	string tmp, delimitr = " ";
	size_t prev = 0, next, delta = delimitr.length(), num = 0;
	bool flag = true;
	while (flag) {
		if ((next = str.find(delimitr, prev)) != string::npos) {
			tmp = str.substr(prev, next - prev);
		}
		else {
			tmp = str.substr(prev);
			flag = false;
		}
		if (num == words_num) return tmp;
		prev = next + delta;
		num++;
		tmp.clear();
	}
	return "";
}

string executor::get_word(size_t num_in_list, size_t num) const {
	string str;
	list<pair<string, Commands*>>::const_iterator it = commands_list.begin();
	int i = 0;
	for (auto t: commands_list){
		if (i == num_in_list) {
			str = t.first;
			break;
		}
		i++;
	}
	str = get_word(str, num);
	return str;
}

void executor::read_last_string() {
	string buf, tmp, delimitr = " ";
	unsigned int command_number;
	bool last_word = false;
	size_t next, delta = delimitr.length();
	while (!(this->pars_file).eof()) {
		getline(pars_file, buf);

		while (!last_word) {
			if ((next = buf.find(delimitr, curr_pos_in_pars_file)) != string::npos) {
				tmp = buf.substr(curr_pos_in_pars_file, next - curr_pos_in_pars_file);
			}
			else {
				tmp = buf.substr(curr_pos_in_pars_file);
				last_word = true;
			}

			switch (regime) {
			case Regime::TAIL: {
				if (tmp == "->") {
					regime = Regime::NEXT;
					curr_pos_in_pars_file = next + delta;
				}
				break;
			}

			case Regime::NEXT: {
				command_number = stoi(tmp);
				push_to_list(command_number);
				curr_pos_in_pars_file = next + delta;
				regime = Regime::TAIL;
				break;
			}
			}
			tmp.clear();
		}
		tmp.clear();
		last_word = false;
		buf.clear();
	}
	try {
		if (curr_opened && !added_out_file)throw parsing_exceptions("Text is not saved!");
	}
	catch (parsing_exceptions& ex) {
		cout << ex.error() << endl;
		my_exceptions = true;
	}
}

pair<bool,bool> executor::read_block() {
	string buf, tmp, delimitr = " ";
	size_t  next, delta = delimitr.length();
	string command_and_parametrs;
	short parameters_count = -1;
	int command_number;
	bool begin = false, end = false, last_word = false, input = false, output = false;

	while (!(this->pars_file).eof()) {
		getline(pars_file, buf);
		if (buf == "desc") {
			try {
				if (begin == false) {
					begin = true;
					continue;
				}
				else throw parsing_exceptions("in block begin");
			}
			catch (parsing_exceptions& e) {
				cout << e.error() << endl;
				my_exceptions = true;
				return make_pair(false, false);
			}
		}

		if (buf == "csed") {
			try{ 
				if (end == false) {
					end = true;
					regime = Regime::NEXT;
					return make_pair(input, output);
				}
				else throw parsing_exceptions("block end");
			}
			catch (parsing_exceptions& e) {
				cout << e.error() << endl;
				my_exceptions = true;
				return make_pair(false, false);
			}
		}

		while(!last_word) {
			if ((next = buf.find(delimitr, curr_pos_in_pars_file)) != string::npos) {
				tmp = buf.substr(curr_pos_in_pars_file, next - curr_pos_in_pars_file);
			}
			else {
				tmp = buf.substr(curr_pos_in_pars_file);
				last_word = true;
			}

			switch (regime) {
			case Regime::NUMBER: {
					try {
						command_number = stoi(tmp);
					}
					catch (exception const& ex) {
						parsing_exceptions pars_ex(typeid(ex).name());
						cout <<pars_ex.error()<< endl;
						my_exceptions = true;
						return make_pair(false, false);
					}
					try {
						if (!com_map[command_number].empty())throw parsing_exceptions("Not unique number");
						if (command_number < 0)throw parsing_exceptions("Negative number");
					}
					catch (parsing_exceptions& ex) {
						cout << ex.error() << endl;
						my_exceptions = true;
						return make_pair(false, false);
					}
				regime = Regime::ASSIGNMENT;
				curr_pos_in_pars_file = next + delta;
				break;
			}

			case Regime::ASSIGNMENT: {
				try {
					if (tmp != "=") throw parsing_exceptions("assign error");
				}
				catch (parsing_exceptions& ex) {
					cout << ex.error() << endl;
					my_exceptions = true;
					return make_pair(false, false);
				}
				regime = Regime::COMMAND;
				curr_pos_in_pars_file = next + delta;
				break;
			}

			case Regime::COMMAND: {
				for (auto t: cmnds) {
					if (tmp == t.first) {
						parameters_count = t.second;
						command_and_parametrs += tmp;
						curr_pos_in_pars_file = next + delta;
						if (parameters_count == 0) {
							com_map[command_number] = command_and_parametrs;
							regime = Regime::NUMBER;
							command_and_parametrs.clear();
							break;
						}
						regime = Regime::OPERATORS;
						if (t.first == "readfile") input = true;
						if (t.first == "writefile") output = true;
						break;
					}
				}
				try {
					if (regime == Regime::COMMAND) throw parsing_exceptions("Invalid command");
				}
				catch (parsing_exceptions& ex) {
					cout << ex.error() << endl;
					my_exceptions = true;
					return make_pair(false, false);
				}
				break;
			}
			case Regime::OPERATORS: {
				if (parameters_count != 0) {
					command_and_parametrs += ' ';
					command_and_parametrs += tmp;
					parameters_count--;
					curr_pos_in_pars_file = next + delta;
				}
				if (parameters_count == 0) {
					regime = Regime::NUMBER;
					com_map[command_number] = command_and_parametrs;
					command_and_parametrs.clear();
				}
				break;
			}
			}
			tmp.clear();
		}
		try {
			if (regime == Regime::OPERATORS && last_word) throw parsing_exceptions("Not enough parameters");
		}
		catch (parsing_exceptions& ex) {
			cout << ex.error() << endl;
			my_exceptions = true;
			return make_pair(false, false);
		}
		tmp.clear();
		last_word = false;
		buf.clear();

	}
	return make_pair(input, output);
}

bool no_text_exception(bool flag, string str) {
	try {
		if (!flag) throw parsing_exceptions("No text to " + str);
	}
	catch (parsing_exceptions& ex) {
		cout << ex.error() << endl;
		return true;
	}
	return false;
}

void executor::add_input(string input) {
	Commands* cm;
	string str = "readfile " + input;
	com_map[-1] = input;
	
	unique_ptr<read_factory> rd(new read_factory);
	curr_opened = true;
	try {
		cm = rd->create_command();
	}
	catch (commands_exceptions& e) {
		cout << e.error() << endl;
		my_exceptions = true;
		return;
	}
	commands_list.push_front(make_pair(str, cm));
}

void executor::add_output(string output) {
	com_map[com_map.size()] = "writefile " + output;
	push_to_list(com_map.size()-1);
}

void executor::push_to_list(int j) {
	try {
		if (com_map[j].size() == 0) throw parsing_exceptions("Unknown number!");
	}
	catch (parsing_exceptions & ex) {
		cout << ex.error() << endl;
		my_exceptions = true;
		return;
	}
	string com = get_word(com_map[j], 0);
	for (auto t : cmnds) {
		if (com == t.first) {
			SWITCH(com) {
				CASE("readfile") : {
					try {
						if (curr_opened) throw parsing_exceptions("Second file to reading!");
					}
					catch (parsing_exceptions & ex) {
						cout << ex.error() << endl;
						break;
					}
					unique_ptr<read_factory> cm(new read_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));

					curr_opened = true;
					break;
				}
				CASE("writefile") : {
					if (!added_out_file && no_text_exception(curr_opened, "write")) {
						my_exceptions = true;
						return;
					}
					curr_opened = false;
					unique_ptr<write_factory> cm(new write_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
				CASE("grep") : {
					if (no_text_exception(curr_opened, "grep")) {
						my_exceptions = true;
						return;
					}
					unique_ptr<grep_factory> cm(new grep_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
				CASE("replace") : {
					if (no_text_exception(curr_opened, "replace")) {
						my_exceptions = true;
						return;
					}
					unique_ptr<replace_factory> cm(new replace_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
				CASE("dump") : {
					if (no_text_exception(curr_opened, "dump")) {
						my_exceptions = true;
						return;
					}
					unique_ptr<dump_factory> cm(new dump_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
				CASE("sort") : {
					if (no_text_exception(curr_opened, "sort")) {
						my_exceptions = true;
						return;
					}
					unique_ptr<sort_factory> cm(new sort_factory);
					commands_list.push_back(make_pair(com_map[j], cm->create_command()));
					break;
				}
			}
			return;
		}
	}
}

void executor::work() {
	int i = 0;
	for (auto &t: commands_list) {
		Commands* cm = t.second;
		cm->doing(this, i);
		i++;
	}
}

void executor::edit_text(string new_text) {
	this->text = new_text;
}

void executor::edit_text(bool end) {
	if (end) {
		this->text.clear();
	}
}

string executor::get_text() const {
	return this->text;
}

>>>>>>> d1902f0ab7cb51402609943373c05981c0958025
