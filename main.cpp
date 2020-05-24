/*
	CIS 22C
	Lab 06 - Hashtable with Person objects
	Name: Santosh Lakshman 
	Program Description:
	This program creates a Hashtable for person objects based on an input file and allows the user to search for an item in the Hashtable
	Pseudocode:
	Ask user for path of input file
	If file path is valid
		open file
		Check how many person objects are in the file 
		Create a hashtable with the same size as the amount of Persons
		Read in all persons
	Else
		prompt user for new path
	Loop
		Ask user for menu option
		If selection is 1
			Print out Hashtable
		If selection is 2
			prompt user for a bday to search
		If selection is 3
			print menu
		If selection is 4
			Ask user if they are sure they want to exit
			If yes
				Exit

*/

#include <iostream>
#include <fstream>
#include <string>
#include "PersonHashTable.h"
#include "Person.h"

using namespace std;

void rePromptPath(ifstream&, string&);
void displayMenu();
int numPersons(ifstream&, ofstream&, string&, string&, int&, int&);
void readFile(ifstream&, ofstream&, PersonHashTable&, string&, string&);
bool isValidBday(std::string);
void find(PersonHashTable&);


int main()
{
	string path;
	string name;
	string bday;
	string selection;
	ifstream reader;
	ofstream nameKeyWriter;
	ofstream bdayKeyWriter;
	ofstream errorLog("Error Log.txt");
	ifstream errorLogReader("Error Log.txt");
	bool endOfFile = false;
	int nameLine = 0, bdayLine = 0, numReadIn = 0, numErrors = 0;
	
	cout << "Lab 6 by Santosh Lakshman" << endl;
	cout << "\nTo begin, enter the full path of the file from which the Person data is to be read from " << endl;
	cout << "(i.e. C:\\Users\\Gokul Satheesh Nair\\Repos\\BinarySearchTree\\Lab5_SL_GN\\Lab5_SL_GN\\text.txt): " << endl;
	cout << "If you want to use the same folder as the exe just type 0 and press enter." << endl;
	cout << "A file named testfile.txt is provided in the same folder as the exe for convenience" << endl;
	getline(cin, path);
	if (path == "0") {
		cout << "Enter the name of the text file to read." << endl;
		cout << "(i.e. text.txt): " << endl;
		getline(cin, path);
	}
	reader.open(path);
	if (!(reader.is_open())) rePromptPath(reader, path);
	cout << "\nFile opened successfully " << endl;
	PersonHashTable mainHashTable = PersonHashTable(numPersons(reader, errorLog, name, bday, numReadIn, numErrors));
	reader.close();
	reader.open(path);
	cout << "Reading from file... " << endl << endl;
	readFile(reader, errorLog, mainHashTable, name, bday);
	cout << "HashTable created" << endl;
	cout << "Printing table" << endl;
	cout << mainHashTable << endl;

	while (true)
	{
		displayMenu();
		getline(cin, selection);
		if (selection == "1" || selection == "PRINT") cout << mainHashTable << endl;
		else if (selection == "2" || selection == "FIND") find(mainHashTable);
		else if (selection == "3" || selection == "HELP") displayMenu();
		else if (selection == "4" || selection == "EXIT") {
			cout << "Press 0 to confirm exit" << endl;
			getline(cin, selection);
			if (selection == "0") break;
		}
		else {
			cout << "\nERROR: Improper command. Enter \'5\' or \'HELP\' to display menu " << endl;
			cout << "\nCommand: ";
		}
	}

	reader.close();
	nameKeyWriter.close();
	bdayKeyWriter.close();
	errorLog.close();
	errorLogReader.close();
	remove("Error Log");
	mainHashTable.~PersonHashTable();
	cout << "Deleted Hashtable" << endl;
	system("pause");
	return 0;
}


//Prompts user to enter valid path to file from which Person data is read from
//Pre: ifstream object exists and user has already given an invalid path once already in main
//Post: ifstream object is correctly initialized with valid path 
void rePromptPath(ifstream& reader, string& path)
{
	while (!reader.is_open())
	{
		cout << "\nError: Unable to open file. " << endl;
		cout << "Please enter FULL PATH of the file from which the Person data is to be read from properly " << endl;
		cout << "(i.e. C:\\Users\\Gokul Satheesh Nair\\Repos\\BinarySearchTree\\Lab5_SL_GN\\Lab5_SL_GN\\text.txt): " << endl;
		getline(cin, path);
		reader.open(path);
	}
}

//Counts the number of Persons in the file
//Pre: An input file of persons exists
//Post: the number of valid persons is returned
int numPersons(ifstream& reader, ofstream& errorLog, string& name, string& bday, int& read, int& error) {
	int nameLine = 0;
	int bdayLine = 0;

	while (true)
	{
		if (reader.eof()) break;
		nameLine = bdayLine;

		while (!(reader.eof()) && name.empty()) {
			nameLine++;
			getline(reader, name);
		}
		bdayLine = nameLine;

		while (!(reader.eof()) && bday.empty()) {
			bdayLine++;
			getline(reader, bday);
		}

		try {
			Person* newPerson = new Person(name, bday, NAME_PKEY);
			delete newPerson;
		}
		catch (string e) {
			error++;
		}

		name.clear();
		bday.clear();
		read++;
	}
	return read - error;
}

//Reads file full of person data and inputs them into two BSTs
//Pre: All iostream objects exist, PersonHashtable exists, and there are alternating pairs of 
//name and birthday lines in data file, name first
//Post: Appropriate Person objects are generated from data and added to the hashtable
void readFile(ifstream& reader, ofstream& errorLog, PersonHashTable& table, string& name, string& bday){
	int nameLine = 0;
	int bdayLine = 0;

	while (true)
	{
		if (reader.eof()) break;
		nameLine = bdayLine;
		while (!(reader.eof()) && name.empty()) {
			nameLine++;
			getline(reader, name);
		}
		bdayLine = nameLine;
		while (!(reader.eof()) && bday.empty()) {
			bdayLine++;
			getline(reader, bday);
		}

		try {
			Person* newPerson = new Person(name, bday, NAME_PKEY);
			table.add(newPerson);
		}
		catch (string e) {
			cout << e << endl;
			cout << "Skipped pair of name and birthday on lines " << nameLine << " and " << bdayLine << endl << endl;
			errorLog << e << endl;
			errorLog << "Skipped pair of name and birthday on lines " << nameLine << " and " << bdayLine << endl << endl;
		}
		name.clear();
		bday.clear();
	}
}

//Checks if the string is in the valid bday format
//Pre: used in find function to make sure user enters a valid bday
//Post: True if string is a valid bday and false if not
bool isValidBday(std::string b)
{
	bool valid = true;
	if (b.length() == 10)
	{
		for (int i = 0; i < 10; i++) {
			if (i == 4 || i == 7) i++;
			if (!isdigit(b[i])) {
				valid = false;
				break;
			}
		}
		if (b[4] != '-' || b[7] != '-') valid = false;
	}
	else valid = false;
	return valid;
}

//Prompts user for a birthday and returns the name corresponding to the birthday if it is found
//Pre: PersonHashtable exists
//Post: Value is found or not found
void find(PersonHashTable& table) {
	string bday;
	do{
		cout << "Proper birthday format:  YYYY-MM-DD" << endl;
		cout << "Enter person's birthday: ";
		getline(cin, bday);
	} while (isValidBday(bday) == false);
	if (table.find(bday) == nullptr) cout << "Invalid Data" << endl;
	else cout << "Name of person matching that birthdate: " << table.find(bday)->getName() << endl;
}


//Displays menu of commands to console
//Pre: None
//Post: Menu is displayed on console
void displayMenu() {
	cout << "\nMenu: " << endl;
	cout << "Type the number OR the name of the command in caps verbatim. " << endl;
	cout << "(1) PRINT - print hashtable data " << endl;
	cout << "(2) FIND - search for a value in hashtable " << endl;
	cout << "(3) HELP - display menu once again " << endl;
	cout << "(4) EXIT - exit the program " << endl;
	cout << "\nEnter command: ";
}