#include<iostream>
#include<fstream>
#include<cctype>
#include<string>
#include <conio.h>
#include<stdio.h.>
#include<windows.h>
#include<vector>
#include"Database.h"
#include"Table.h"
#include"Custome Functions.h"
#include"Helper Functions.h"

using namespace std;

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
	if (splitedQuery[1] == "table") {
		if (splitedQuery.size() == 3) {
			d.DeleteTable(DBName, splitedQuery[2]);
			gotoxy(22, 7);
			cout << "One table is deleted" << endl;
		}
		else {
			gotoxy(22, 7);
			cout << "Incorrect syntax" << endl;
		}
	}
	else {
		gotoxy(22, 7);
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
			cout << rows.size() << " rows effected" << endl;
			remove((DBName + "/" + splitedQuery[2] + ".txt").c_str());
			rename((DBName + "/temp.txt").c_str(), (DBName + "/" + splitedQuery[2] + ".txt").c_str());
		}
	}
}

void SelectQuery(vector<string>the_query, string db_name) {
	int where_indx = getIndex(the_query, "where");
	int from_index = getIndex(the_query, "from");
	int equal_index = getIndex(the_query, "=");
	fstream myfile;
	int file_num_id;
	int the_size = the_query.size();
	cout << the_size;

	if (the_size > 0) {
		//select * from emp1(table)
		if (the_query[1] == "*" && the_size == 4) {
			myfile.open(db_name + "/" + the_query[from_index + 1] + ".txt", ios::app);
			if (myfile.is_open()) {
				string data;
				while (getline(myfile, data)) {
					cout << data << "\n";
				}
				myfile.close();
			}
			else { cout << "no such table check help in main menu"; }
		}
		// select record from emp2 where id = 1
		else if (the_query[1] != "*") {
			file_num_id = stoi(the_query[equal_index + 1]);
			if (file_num_id <= 0) {
				cout << " id must be > 0 " << endl;
			}
			myfile.open(db_name + "/" + the_query[from_index + 1] + ".txt", ios::app);
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
	else cout << "the query must be length greater than 0";

}

void the_insert(vector<string>the_query, string db_name) {
	fstream outfile;
	int j = 0;
	int open_index = getIndex(the_query, "(");
	int close_index = getIndex(the_query, ")");
	int into_index = getIndex(the_query, "into");
	int values_index = getIndex(the_query, "values");

	if (the_query[1] == "into") {
		string the_adderecord;
		outfile.open((db_name + "/" + the_query[2] + ".txt").c_str(), ios::app);
		outfile << endl;
		for (int i = values_index + 1; i < the_query.size(); i++) {
			outfile << the_query[i] << "       ";
		}
		outfile.close();
		cout << "one row affected";

	}
	else {
		cout << "Invalid Query" << endl;
	}
}

void QueryResult(string query, vector<string>result, int choice) {
	vector<string>splitedQuery = split(query);
	cout << "first one is " << splitedQuery[0] << endl;
	if (splitedQuery[0] == "select") {
		SelectQuery(splitedQuery, result[choice]);
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
		cout << "Invalid Query sdawd" << endl;
	}
}