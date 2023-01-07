#include<iostream>
#include<fstream>
#include<direct.h>
#include<conio.h>
#include<string>
#include<vector>
#include"Table.h"
#include"Custome Functions.h"
#include"Helper Functions.h"
using namespace std;

class Database
{
	string DBName;
	Table t;
	vector<string>names;
	fstream collection;

public:
	Database() {
		string temp;
		collection.open("Databases.txt");
		while (getline(collection, temp))
		{
			names.push_back(temp);
		}
		collection.close();
	}

	void setDatabase(string _DBName) {
		DBName = _DBName;
	}

	string CreateDatabase() {
		string temp;
		gotoxy(22, 4);
		cout << "Enter Database Name: ";
		cin >> DBName;
		DBName = lowerCase(trim(DBName));

		if (!checkString(DBName)) {
			gotoxy(22, 5);
			cout << "Invalid Name" << endl;
			gotoxy(22, 6);
			cout << "Press any key to try again";
			_getch();
			system("cls");
			return CreateDatabase();
		}

		if (DBName == "databases" || DBName == "temp") {
			gotoxy(22, 5);
			cout << "Reserved name" << endl;
		}

		for (int i = 0; i < names.size(); i++) {
			if (DBName == names[i]) {
				gotoxy(22, 5);
				cout << "This Database is already found" << endl;
				gotoxy(22, 6);
				cout << "Press any key to try again";
				_getch();
				system("cls");
				return CreateDatabase();
			}
		}

		_mkdir(DBName.c_str()); //Create Folder with the same name of new Database
		collection.open("Databases.txt", ios::app);//Open the files that contains all Databases names
		collection << DBName << endl; // Add the name of new Database in collection file
		collection.close();
		names.push_back(DBName); // Add the name of new Database in the Vector
		gotoxy(22, 5);
		cout << DBName << " Database is created Successfully" << endl;
		gotoxy(22, 6);
		system("pause");		
		return DBName;
	}

	void CreateTable() {
		t.setTable(DBName);
		t.CreateTable();
	}

	vector<string> ShowDatabases() {
		return names;
	}

	vector<string> ShowTables(string _DBName) {
		return t.ShowTables(_DBName);
	}

	void DeleteDatabase(string target) {
		// 1) delete the name of target database from Databases.txt
		collection.open("temp.txt", ios::app);
		for (int i = 0; i < names.size(); i++) {
			if (names[i] != target) {
				collection << names[i] << endl;
			}
		}
		collection.close();
		remove("Databases.txt");
		rename("temp.txt", "Databases.txt");

		// 2) delete the folder of target database
		int x = system(("rmdir /s /q " + target).c_str());
		if (x == 0) {
			gotoxy(22, 9 + names.size());
			textattr(0x0c);
			cout << target << " Database is deleted Successfully" << endl;
			gotoxy(22, 10 + names.size());
			cout << "Press any key to back to main menu" << endl;
			_getch();
		}
		else
		{
			cout << "Error: " << target << " cannot be deleted" << endl;
		}
	}

	void DeleteTable(string DBName, string target) {
		t.DeleteTable(DBName, target);
	}
};