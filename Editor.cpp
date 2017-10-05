//Editor.cpp
#include "Editor.h"
#include "windows.h"

//In this constructor, first, we make sure the file exists. 
//The text will be stored into the LinkedList: buffer 
//A variable will store the number of lines in the file
//And the keywords binary tree will be created

XiEditor::XiEditor(string fileName) {

	_currentLine = 1;
	_currentPos = 0;
	ifstream file(fileName);

	if (!file.is_open()) {
		cout << "FILE CAN NOT BE FOUND" << endl;
		system("pause");
		exit(1);
	}

	string line;
	_numLines = 0;

	for (int i = 1; !file.eof(); i++){
		getline(file,line);
		_buffer.insert(i, line);
		_numLines++;
	}

	file.close();

	ifstream file2("keywords.txt");

	if (!file2.is_open()) {
		cout << "FILE CAN NOT BE FOUND" << endl;
		system("pause");
		exit(1);
	}

	k = new BinarySearchTree <string>();
	string word;

	while (!file2.eof()) {
		file2 >> word;
		k->add(word);
	}

	
	
}

//This method prints the text in buffer
// It will print keywords in blue
// and have a cursor thing that follows you as you navigate

void XiEditor::printLines() {
	int i, j;
	for (i = 1; i < _numLines + 1; i++) {
		myLine = _buffer.getEntry(i);

		istringstream streamWords{ myLine };

		vector<string> words{
			istream_iterator<string>(streamWords), istream_iterator<string>()
		};

		for (string w : words){
			if (!k->contains(w))
				colorText(1);  //blue 
			else
				colorText(0);
			cout << " " << w << " ";
		}
		cout << endl;
	}
	goToXY(_currentPos , _currentLine - 1);
}

void XiEditor::goToXY(int column, int line){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}
void XiEditor::colorText(int value){
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value + 240);
}

//This method takes in the command you give it and moves the ^ accordingly
// j moves down, k moves up, h moves left and l moves right

void XiEditor::processCommand(char c) {

	switch (c) {
	case 'j':
		if (_currentLine < _numLines) {
			CommandPlus command("j");
			myStack.push(command);
			down();
			break;
		}
		else
			break;
	case 'k':
		if (_currentLine > 0) {
			CommandPlus command("k");
			myStack.push(command);
			up();
			break;
		}
		else
			break;
	case 'h':
		if (_currentPos > 1) {
			CommandPlus command("h");
			myStack.push(command);
			left();
			break;
		}
		else
			break;
	case 'l':
		if (_currentPos < _buffer.getEntry(_currentLine).length()) {
			CommandPlus command("l");
			myStack.push(command);
			right();
			break;
		}
		else
			break;
	case 'x':
		if (_buffer.getEntry(_currentLine).length() > 0){
			string line = _buffer.getEntry(_currentLine);
			string savedChar = string(1, line[_currentPos]);//converts a single char into a string
			CommandPlus command("x", savedChar);
			myStack.push(command);
			deletechar();
			break;
		}
		else
			break;
	case 'd':
		if (_currentLine > -1 && _currentLine < _numLines){
			string lineToDelete = _buffer.getEntry(_currentLine);
			CommandPlus command("d", lineToDelete);
			myStack.push(command);
			deleteline();
			break;
		}
	case 'u':
		if (!myStack.isEmpty()){
			undo();
			break;
		}
		else
			break;
	case 'i':{
		string letters = "";
		char let = _getch();
		letters += let; //converts a single char into a string	
		do {
			system("cls");
			CommandPlus command("i", letters);
			myStack.push(command);
			insertchar(letters);
			printLines();
			_currentPos++;
			letters = "";
			let = _getch();
			letters += let;
		} while (let != '\x1b'); 
		break;
	}
//for insert line, I only put in an empty line
 //If the user wants to type words, they will need to press 'i'
	case 'I':			
		string nline = "";
		CommandPlus command("I",nline);
		myStack.push(command);
		insertline(nline);
		_currentPos = 0;
		break;
	}

}

// The following methods are for the movement of the blinking cursor

void XiEditor::up() {
	_currentLine--;
}

void XiEditor::down() {
	_currentLine++;
}

void XiEditor::right() {
	_currentPos++;
}


void XiEditor::left() {
	_currentPos--;
}

void XiEditor::deletechar(){
	string temp = _buffer.getEntry(_currentLine);		//store get entry on a string
	temp.erase(_currentPos, 1);							//modify it with erase
	_buffer.replace(_currentLine, temp);				//replace it
}
void XiEditor::insertchar(string savedValue){
	string temp = _buffer.getEntry(_currentLine);
	string putIn;
	_buffer.remove(_currentLine);
	putIn = temp.substr(0, _currentPos) + savedValue + temp.substr(_currentPos);
	_buffer.insert(_currentLine, putIn);
}

void XiEditor::deleteline(){
	_buffer.remove(_currentLine);	
	_numLines--;
}

void XiEditor::insertline(string savedValue){
	_numLines++;
	_buffer.insert(_currentLine, savedValue); // and insert the line deleted back into the right spot
}

void XiEditor::undo(){
	if (!myStack.isEmpty()){
		CommandPlus commandplus = myStack.peek();
		char command = commandplus.getCommand();
		string savedValue = commandplus.getSavedValue();
		myStack.pop();
		switch (command){
		case 'j':
			up();
			break;
		case 'k':
			down();
			break;
		case 'h':
			right();
			break;
		case 'l':
			left();
			break;
		case 'x':
			insertchar(savedValue);
			break;
		case 'd':
			insertline(savedValue);
			break; 
		case 'i':
			_currentPos--;
			deletechar();
			break;
		case 'I':
			deleteline();
			break;
		}
	}
} 