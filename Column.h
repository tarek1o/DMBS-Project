#pragma once
#include<iostream>
#include <conio.h>
#include<vector>
#include"Helper Functions.h"
#include"Custome Functions.h"
#include<fstream>
using namespace std;
class Column
{
	string TableName;
	string DBName;
	string ColumnName;
	string ColumnType;
	string* String;
	char* ch;
	int* Int;
	long *Long;
	double* Double;
	fstream collection;

public:
	Column() {
		ch = NULL;
		String = NULL;
		Int = NULL;
		Long = NULL;
		Double = NULL;
	}

	void Columnname(int row) {
		string temp;
		vector<string>names;
		
		//To get all metadata of the table before add any new column to check if it is exit or not
		collection.open((DBName + "/" + TableName + ".txt").c_str());
		getline(collection, temp);
		collection.close();
		names = split(temp);

		//Start take the name of the column
		gotoxy(20, row);
		textattr(0x0d);
		cout << "Column Name: ";
		textattr(0x0a);
		cin >> ColumnName;
		ColumnName = lowerCase(trim(ColumnName));

		//To check if the name that is entered is exit or not
		for (int i = 0; i < names.size(); i++) {
			if (ColumnName == names[i]) {
				gotoxy(20, row + 1);
				textattr(0x0c);
				cout << "This name is used" << endl;
				gotoxy(20, row + 2);
				textattr(0x0c);
				cout << "Press any key to try again" << endl;
				_getch();
				gotoxy(20, row);
				cout << "                                                                 " << endl;
				gotoxy(20, row + 1);
				cout << "                                                                 " << endl;
				gotoxy(20, row + 2);
				cout << "                                                                 " << endl;
				return Columnname(row);
			}
		}
	}

	void ColumnDatatype(int row) {
		gotoxy(52, row);
		textattr(0x0d);
		cout << "Datatype: ";
		textattr(0x0a);
		cin >> ColumnType;
		ColumnType = lowerCase(trim(ColumnType));

		//To check if the datatype that is entered is exit or not
		if (ColumnType == "int" || ColumnType == "bit" || ColumnType == "smallint" || ColumnType == "tinyint" || ColumnType == "bigint") {
			Int = new int(1);
		}
		else if (ColumnType == "float" || ColumnType == "real" || ColumnType == "decimal" || ColumnType == "smallmoney" || ColumnType == "money") {
			Double = new double(1);
		}
		else if (ColumnType == "char" || ColumnType == "varchar" || ColumnType == "text" || ColumnType == "nchar" || ColumnType == "nvarchar" || ColumnType == "ntext") {
			String = new string();
		}
		else
		{
			textattr(0x0c);
			gotoxy(32, row + 1);
			cout << "Invalid datatype" << endl;
			gotoxy(32, row + 2);
			cout << "Try again.." << endl;
			_getch();
			gotoxy(52, row);
			cout << "                                                                 " << endl;
			gotoxy(32, row + 1);
			cout << "                                                                 " << endl;
			gotoxy(32, row + 2);
			cout << "                                                                 " << endl;
			return ColumnDatatype(row);
		}
	}

	void addColumn(string _DBName, string _TableName) {
		DBName = _DBName;
		TableName = _TableName;
		char ch;
		string temp;
		int row = 8;
		do {
			Columnname(row);
			ColumnDatatype(row);
			collection.open((DBName + "/" + TableName + ".txt").c_str(), ios::app);
			//collection << ColumnName + "(" + ColumnType + ")" << "		"; // 2 tabs
			collection << ColumnName << "       "; // 7 spaces
			collection.close();
			row++;
			gotoxy(20, row);
			textattr(0x0e);
			cout << "Do you want to add new column?(y/n)";
			ch = _getch();
			ch = tolower(ch);
			cout << endl;
			row ++;
		} while (ch != 'n');
	}
};

