#include<iostream>
#include<cctype>
#include<string>
#include <conio.h>
#include<windows.h>
#include<vector>
#include"Database.h"
#include"Custome Functions.h"
#include"Helper Functions.h"

void QueryResult(string query, vector<string>result, int choice) {
	vector<string>splitedQuery = split(query);

	if (splitedQuery[0] == "select") {
		cout << "Selected Query" << endl;
	}
	else if (splitedQuery[0] == "insert") {
		cout << "Insert Query" << endl;
	}
	else if (splitedQuery[0] == "update") {
		cout << "Update Query" << endl;
	}
	else if (splitedQuery[0] == "delete") {
		cout << "Delete Query" << endl;
	}
	else if (splitedQuery[0] == "truncate") {
		cout << "Truncate Query" << endl;
	}
	else 
	{
		cout << "Invalid Query" << endl;
	}
}
