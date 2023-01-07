#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include <conio.h>
#include<windows.h>
#include<vector>
#include"Database.h"
#include"Table.h"
#include"Custome Functions.h"
#include"Helper Functions.h"

void creation(vector<string>query) {
	fstream collection;
	if (query.size() >= 2) {
		if (query[1] == "database") { // database
			if (query.size() == 3) {
				string temp;
				Database d;
				if (!checkString(query[2])) {
					gotoxy(22, 7);
					cout << "Invalid Name" << endl;
					gotoxy(22, 8);
					cout << "Press any key to try again";
					_getch();
					system("cls");
					return;
				}
				
				if (getIndex(d.ShowDatabases(), query[2]) == -1) {
					_mkdir(query[2].c_str()); //Create Folder with the same name of new Database
					collection.open("Databases.txt", ios::app);//Open the files that contains all Databases names
					collection << query[2] << endl; // Add the name of new Database in collection file
					collection.close();
					gotoxy(22, 5);
					cout << query[2] << " Database is created Successfully" << endl;
					gotoxy(22, 6);
					system("pause");
					return;
				}
				else {
					gotoxy(22, 7);
					cout << "This database is already found" << endl;
					return;
				}
			}
			else {
				gotoxy(22, 7);
				cout << "Incorrect syntax" << endl;
			}
		}
		else if (query[1] == "table") { //table
			
		}
		else {
			gotoxy(22, 7);
			cout << "Invalid query" << endl;
		}
	}
	else {
		gotoxy(22, 7);
		cout << "Invalid query" << endl;
	}
}

void drop(string DBName, vector<string> splitedQuery) {
	Database d;
	d.setDatabase(DBName);
	if (splitedQuery[1] == "table") {
		if (splitedQuery.size() == 3) {
			d.DeleteTable(DBName, splitedQuery[2]);
		}
		else {
			cout << "Incorrect syntax" << endl;
		}
	}
	else {
		cout << "Incorrect syntax" << endl;
	}
}

void truncate(string DBName, vector<string>splitedQuery) {
	vector<string> rows;
	fstream collection;
	string metaData, temp;
	if (splitedQuery[1] == "table") {
		if (splitedQuery.size() == 3) {
			collection.open(DBName + "/" + splitedQuery[2] + ".txt");
			getline(collection, metaData);
			while (getline(collection, temp)) {
				rows.push_back(temp);
			}
			collection.close();
			collection.open(DBName + "/" + "temp.txt", ios::app);
			collection << metaData << endl;
			collection.close();
			cout << rows.size() - 1 << " rows effected" << endl;
			remove((DBName + "/" + splitedQuery[2] + ".txt").c_str());
			rename((DBName + "/temp.txt").c_str(), (DBName + "/" + splitedQuery[2] + ".txt").c_str());
		}
	}
}

void SelectQuery(vector<string>the_query) {
	fstream myfile;
	string db_name;
	//string file_name;
	int file_num_id;
	int the_size = the_query.size();
	//select * from emp1(table)
	if (the_query[1] == "*" && the_size == 4) {
		cout << "please enter Database name";
		getline(cin, db_name);
		myfile.open(db_name + "/" + the_query[3] + ".txt", ios::app);
		if (myfile.is_open()) {
			string data;
			while (getline(myfile, data)) {
				cout << data << "\n";
			}
			myfile.close();
		}
		else { cout << "no such table check help in main menu"; }
	}
	// select emp where id = 1 from emp1=> index 5
	else if (the_query[1] != "*" && the_query[2] == "where" && the_size == 6) {
		cout << "please enter Database name";
		getline(cin, db_name);
		file_num_id = stoi(the_query[5]);
		if (file_num_id <= 0) {
			cout << " id must be > 0 " << endl;
		}
		myfile.open(db_name + "/" + the_query[7] + ".txt", ios::app);
		if (myfile.fail()) {
			cout << "cant open file" << endl;
		}
		int current_id = 0;
		string output;
		while (!myfile.eof()) {
			current_id++;
			getline(myfile, output);
			if (current_id == file_num_id) break;
			if (current_id < file_num_id) {
				cout << "this record not found";
			}
			else
				cout << output << endl;
			myfile.close();
		}
	}
}

void the_insert(vector<string>the_query, string db_name) {
	std::ofstream outfile;
	if (the_query[0] == "insert" && the_query[1] == " into") {
		//cout << the_query[1];
		string the_addcolumn;
		outfile.open(db_name + "/" + the_query[2] + ".txt", std::ios_base::app);
		cout << "please enter column values :    attribute: val    attribute : val ";
		getline(cin, the_addcolumn);
		outfile << "\n" << the_addcolumn;
		outfile.close();
		cout << "one row affected";
	}
}

void QueryResult(string query, vector<string>result, int choice) {
	vector<string>splitedQuery = split(query);

	if (splitedQuery[0] == "select") {
		SelectQuery(splitedQuery);
	}
	else if (splitedQuery[0] == "insert") {
		the_insert(splitedQuery, result[choice]);
	}
	else if (splitedQuery[0] == "delete") {

	}
	else if (splitedQuery[0] == "update") {
		cout << "Update Query" << endl;
	}
	else if (splitedQuery[0] == "drop") {
		drop(result[choice], splitedQuery);
	}
	else if (splitedQuery[0] == "truncate") {
		truncate(result[choice], splitedQuery);
	}
	else if (splitedQuery[0] == "create") {
		creation(splitedQuery);
	}
	else 
	{
		gotoxy(22, 8);
		cout << "Invalid Query" << endl;
	}
}