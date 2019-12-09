#pragma once
#include<exception>
#include<iostream>
using namespace std;

class commands_exceptions : public exception {
private:
	string message;
	string ex_type = "commands exception: ";
public:
	commands_exceptions(const string& mess) : message(mess) {};
	string error() const noexcept {
		return ex_type + message; 
	}
	~commands_exceptions() {};
};
class parsing_exceptions : public exception {
private:
	string message;
	string ex_type = "parsing exception: ";
public:
	parsing_exceptions(const string& mess) : message(mess) {};
	string error()const noexcept {
		return ex_type + message;
	}
	~parsing_exceptions() {};
};
class command_string_exceptions : public exception {
private:
	string message;
	string ex_type = "command string exceptions: ";
public:
	command_string_exceptions(const string& mess) : message(mess) {};
	string error()const noexcept {
		return ex_type + message;
	}
	~command_string_exceptions() {};
};