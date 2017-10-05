//CommandPlus.cpp
#include "CommandPlus.h"

//Here are 3 constructors that are specifically made to compensate for the 2 kinds of CommandPlus
CommandPlus::CommandPlus(){

}
//this one is for navigation
CommandPlus::CommandPlus(string c){
	command = c;
	savedValue = "";
}
//this one is for deleting a line or character
CommandPlus::CommandPlus(string c, string str){
	command = c;
	savedValue = str;
}
//this method returns the command stored
char CommandPlus::getCommand(){
	return command[0];
}
//this method returns the value sotred
string CommandPlus::getSavedValue(){
	return savedValue;
}