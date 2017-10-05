//main.cpp
#include "Editor.h"
#include "CommandPlus.h"

void main(int argc, char *argv[]) {
	XiEditor editor(argv[1]);		//creates an instance of Editor
	CommandPlus commandPlus;		//creates an instance of commandPlus
	editor.printLines();
	char ch = _getch();
	do {
		editor.processCommand(ch);
		system("cls");
		editor.printLines();
		ch = _getch();
	} while (ch != 'q'); 
}
