//Editor.h

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include "CommandPlus.h"
#include "LinkedList.h"
#include "BinarySearchTree.h"
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;

#pragma once

class XiEditor {

public:
	XiEditor(string); //constructor
	void printLines();
	void goToXY(int, int);
	void colorText(int);
	void processCommand(char);
	void up();
	void down();
	void right();
	void left();
	void deletechar();
	void insertchar(string);
	void deleteline();
	void insertline(string);
	void undo();

private:
	LinkedList <string> _buffer;  //array of the text
	int _capacity;  //how many lines the text is
	int _numLines;  // how many elements there are
	int _currentLine; //used to keep track of where you are when navigating; starts at 0
	int _currentPos;  //used to keep track of where you are when navigating; starts at 0
	string myLine;
	LinkedStack <CommandPlus> myStack;
	BinarySearchTree <string> *k;
};