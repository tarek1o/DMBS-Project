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

	void CreateDatabase() {
		string temp;
		gotoxy(22, 4);
		cout << "Enter Database Name: ";
		cin.ignore();
		getline(cin, DBName);

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
		cout << "Press any key to continue....";
		_getch();
	}

	void CreateTable() {
		t.setTable(DBName);
		t.CreateTable();
	}

	void ShowDatabases() {
		string temp;
		if (names.size() == 0) {
			cout << "No Databases to show" << endl;
		}
		else
		{
			for (int i = 0; i < names.size(); i++) {
				cout << names[i] << endl;
			}
		}
	}

	void DeleteDatabase(string target) {
		int x = system(("rmdir /s /q " + target).c_str());
		if (x == 0) {
			cout << target << " Database is deleted Successfully" << endl;
		}
		else
		{
			cout << "Error: " << target << " cannot be deleted" << endl;
		}
	}
};