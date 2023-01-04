#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <conio.h>
#include<vector>
#include"Custome Functions.h"
#include "Helper Functions.h"
#include"Column.h"
using namespace std;

class Table
{
	string TableName;
	string DBName;
	Column c;
	vector<string>tables;
	fstream collection;

public:
	void setTable(string _DBName) { //Create file called tables contains all names of tables
		string temp;
		DBName = _DBName;
		collection.open(DBName + "/Tables.txt");
		collection.close();
	}

	void CreateTable() {
		gotoxy(22, 4);
		cout << "Enter Table Name: ";
		getline(cin, TableName);
		TableName = lowerCase(trim(TableName));

		if (!checkString(TableName) || TableName == "tables") {
			gotoxy(22, 5);
			cout << "Invalid Name" << endl;
			gotoxy(22, 6);
			cout << "Press any key to try again";
			_getch();
			system("cls");
			return CreateTable();
		}

		for (int i = 0; i < tables.size(); i++) {
			if (TableName == tables[i]) {
				gotoxy(22, 5);
				cout << "This Table is already found" << endl;
				gotoxy(22, 6);
				cout << "Press any key to try again";
				_getch();
				system("cls");
				return CreateTable();
			}
		}

		collection.open(DBName + "/" + "Tables.txt", ios::app);//Open the files that contains all tables names
		collection << TableName << endl; //add the name in the tables file
		collection.close();
		collection.open((DBName + "/" + TableName + ".txt").c_str(), ios::app); //Create table file
		collection.close();
		tables.push_back(TableName);
		gotoxy(22, 5);
		cout << TableName << " Table is created Sucessfuly" << endl;

		// create columns for the table
		c.addColumn(DBName, TableName);
	}

	void ShowTables() {
		if (tables.size() == 0) {
			cout << "No Tables to show" << endl;
		}
		else
		{
			for (int i = 0; i < tables.size(); i++) {
				cout << tables[i] << endl;
			}
		}
	}
};

