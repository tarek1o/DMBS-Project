#include<iostream>
#include<cctype>
#include<string>
using namespace std;

string lowerCase(string name) {
	string temp = name;
	for (int i = 0; i < temp.size(); i++) {
		temp[i] = tolower(temp[i]);
	}
	return temp;
}

string upperCase(string name) {
	string temp = name;
	for (int i = 0; i < temp.size(); i++) {
		temp[i] = toupper(temp[i]);
	}
	return temp;
}

bool checkString(string target) {
	if (target.length() != 0) {
		for (int i = 0; i < target.size(); i++) {
			if (target[i] == '\'' || target[i] == '/' || target[i] == ':' || target[i] == '*' || target[i] == '?' || target[i] == '|' || target[i] == '<' || target[i] == '>') {
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

string trim(string str) {
	int start = 0;
	int end = str.length() - 1;

	for (int i = 0; i < str.length(); i++) {
		if (str[i] != ' ') {
			start = i;
			break;
		}
	}

	for (int i = str.length() - 1; i >= start; i--) {
		if (str[i] != ' ') {
			end = i;
			break;
		}
	}
	
	return str.substr(start, (end - start + 1));
}