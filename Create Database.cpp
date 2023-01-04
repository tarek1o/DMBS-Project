#include <iostream>
#include<fstream>
#include <conio.h>
#include <cstring>
#include <string>
#include<vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include"Database.h"
#include<direct.h>
#include"Custome Functions.h"
#include"Helper Functions.h"

using namespace std;

int main()
{	vector<string>menu = { "Create New Database", "Select Database", "Delete Database", "Exit(ESC)" };
	vector<string>CreateDatabaseMenu = { "New Table", "Main Menu(Home)", "Exit(ESC)" };

	//login();
	show(menu, CreateDatabaseMenu);
	
	return 0;
}

