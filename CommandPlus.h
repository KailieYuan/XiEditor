//CommandPlus.h

#include <iostream>
#include <string>
#include <conio.h>
#include "LinkedStack.h"
#include "StackInterface.h"
#include "Node.h"
using namespace std;

#pragma once

class CommandPlus {
public:
	CommandPlus(); //constructor
	CommandPlus(string);  // this constructor only takes in navigation
	CommandPlus(string, string);  //this constructor takes in the character and lines deleted
	char getCommand();	//accessor
	string getSavedValue();	//accessor
private:
	string command;
	string savedValue;
};
