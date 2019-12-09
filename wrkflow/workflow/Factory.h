#pragma once
#include<iostream>
#include"Commands.h"

using namespace std;
class Commands;

class commands_factory {
public:
	virtual Commands* create_command() = 0;
};
class read_factory :public commands_factory {
public:
	Commands* create_command();
};
class replace_factory :public commands_factory {
public:
	Commands* create_command();
};
class sort_factory :public commands_factory {
public:
	Commands* create_command();
};
class grep_factory :public commands_factory {
public:
	Commands* create_command();
};
class dump_factory :public commands_factory {
public:
	Commands* create_command();
};
class write_factory :public commands_factory {
public:
	Commands* create_command();
};