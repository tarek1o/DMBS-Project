#include<iostream>
#include<cctype>
#include<string>
#include<vector>
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

vector<string> split(string target) {
	int start = 0, end;
	string temp = lowerCase(trim(target));
	vector<string>final;
	target = "";
	//To remove any extra spaces between words
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] != ' ' && temp[i] != '\t') {
			target += temp[i];
		}
		else
		{
			if (target[target.length() - 1] != ' ') {
				target += " ";
			}
		}
	}
	//To push each word in the vector
	for (int i = 0; i < target.length(); i++) {
		if (target[i] == ' ' || i == target.length() - 1) {
			end = i;
			final.push_back(trim(target.substr(start, end - start + 1)));
			start = i + 1;
		}
	}
	return final;
}

int getIndex(vector<string> targetVector, string target)
{
	auto it = find(targetVector.begin(), targetVector.end(), target);
	if (it != targetVector.end())
	{
		int index = it - targetVector.begin();
		return index;
	}
	else {
		return -1;
	}
}
