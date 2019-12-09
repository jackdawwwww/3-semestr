#include<iostream>
#include"Commands.h"
#include"Factory.h"
class Commands;
using namespace std;
Commands* read_factory::create_command() {
	return new read_file;
}
Commands* replace_factory::create_command() {
	return new replace;
}
Commands* sort_factory::create_command() {
	return new sorting;
}
Commands* grep_factory::create_command() {
	return new grep;
}
Commands* dump_factory::create_command() {
	return new dump;
}
Commands* write_factory::create_command() {
	return new write_file;
}