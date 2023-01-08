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

		string temp;
		collection.open(DBName + "/" + "Tables.txt");
		while (getline(collection, temp)) {
			tables.push_back(temp);
		}
		collection.close();

		if (!checkString(TableName)) {
			gotoxy(22, 5);
			cout << "Invalid Name" << endl;
			gotoxy(22, 6);
			cout << "Press any key to try again";
			_getch();
			system("cls");
			return CreateTable();
		}
		else if (TableName == "tables" || TableName == "temp") {
			gotoxy(22, 5);
			cout << "Reserved name" << endl;
			gotoxy(22, 6);
			cout << "Press any key to try again";
			_getch();
			system("cls");
			return CreateTable();
		}
		else {

			if (getIndex(tables, TableName) != -1) {
				gotoxy(22, 5);
				cout << "This Table is already found" << endl;
				gotoxy(22, 6);
				cout << "Press any key to try again";
				_getch();
				system("cls");
				return CreateTable();
			}
			else {
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
		}
	}

	vector<string> ShowTables(string _DBName) {
		DBName = _DBName;
		string temp;
		collection.open(DBName + "/" + "Tables.txt");
		while (getline(collection, temp)) {
			tables.push_back(temp);
		}
		collection.close();
		return tables;
	}

	void DeleteTable(string _DBName, string target) {
		DBName = _DBName;
		string temp;
		collection.open(DBName + "/Tables.txt");
		while (getline(collection, temp))
		{
			tables.push_back(temp);
		}

		collection.close();

		if (getIndex(tables, target) == -1 || tables.size() == 0) {
			gotoxy(22, 7);
			cout << "This table is not found" << endl;
			gotoxy(22, 8);
			system("pause");
		}
		else {
			// 1) delete the name of target table from Tables.txt
			collection.open(DBName + "/temp.txt", ios::app);
			for (int i = 0; i < tables.size(); i++) {
				if (tables[i] != target) {
					collection << tables[i] << endl;
				}
			}
			collection.close();
			remove((DBName + "/Tables.txt").c_str());
			rename((DBName + "/temp.txt").c_str(), (DBName + "/Tables.txt").c_str());

			// 2) delete the folder of target database
			remove((DBName + "/" + target + ".txt").c_str());
		}
	}
};

