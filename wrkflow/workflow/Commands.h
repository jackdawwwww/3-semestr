#pragma once
#include<string>
#include<iostream>
#include"executor.h"
#include<string>

class executor;

using namespace std;

class Commands {
public:
	virtual void doing(executor*, size_t) = 0;
};

class read_file :public Commands {
public:
	void doing(executor*, size_t);
};
class replace :public Commands {
public:
	void doing(executor*, size_t);
};
class sorting :public Commands {
public:
	void doing(executor*, size_t);
};
class grep :public Commands {
public:
	void doing(executor*, size_t);
};
class dump :public Commands {
public:
	void doing(executor*, size_t);
};
class write_file :public Commands {
public:
	void doing(executor*, size_t);
};