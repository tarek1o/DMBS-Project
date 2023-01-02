#pragma once
#include<iostream>
#include <conio.h>
#include"Helper Functions.h"
#include"Custome Functions.h"
#include<fstream>
using namespace std;
class Column
{
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
		gotoxy(20, row);
		textattr(0x0d);
		cout << "Column Name: ";
		textattr(0x0a);
		cin >> ColumnName;
		ColumnName = trim(ColumnName);
		//Check if this column name is exit or no (case insensitive)
	}

	void ColumnDatatype(int row) {
		gotoxy(52, row);
		textattr(0x0d);
		cout << "Datatype: ";
		textattr(0x0a);
		cin >> ColumnType;

		ColumnType = lowerCase(trim(ColumnType));

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
			cout << "Invalid datatype" << endl;
			cout << "Try again.." << endl;
			_getch();
			return ColumnDatatype(row);
		}
	}

	void addColumn(string DBName, string TableName) {
		char ch;
		int row = 8;
		do {
			Columnname(row);
			ColumnDatatype(row);
			collection.open((DBName + "/" + TableName + ".txt").c_str(), ios::app);
			collection << ColumnName + "(" + ColumnType + ")" << "		"; // 2 tabs
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

