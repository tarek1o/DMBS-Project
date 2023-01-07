#pragma once
#include <iostream>
#include<cctype>
#include <string>
#include<vector>
using namespace std;

string lowerCase(string name);
string upperCase(string name);
bool checkString(string target);
string trim(string str);
vector<string> split(string target);
int getIndex(vector<string> v, string K);