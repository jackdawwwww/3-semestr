#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include<list>
#include"Factory.h"
#include"Commands.h"
#include"Exceptions.h"
#include<exception>
#include<memory>

class Commands;
using namespace std;

class executor {
private:
	enum class Regime { NUMBER, ASSIGNMENT, COMMAND, OPERATORS, TAIL, NEXT };
	ifstream pars_file;
	list<pair<string, Commands*>>commands_list;
	map<int, string>com_map;
	size_t curr_pos_in_pars_file;
	string text;
	Regime regime;
	bool curr_opened = false;
public:
	executor(string);
	~executor();
	
	bool my_exceptions = false, added_out_file = false;
	pair<bool,bool> read_block();
	void read_last_string();
	void push_to_list(int);

	string get_word(string, size_t)const;
	string get_word(size_t, size_t)const;
	void add_input(string);
	void add_output(string);

	void edit_text(string);
	void edit_text(bool);
	string get_text()const;
	void work();
};