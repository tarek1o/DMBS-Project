#pragma once
#include <string>
#include<vector>
using namespace std;

void gotoxy(int x, int y);
void textattr(int i);
void login();
void PrintMenu(vector<string>menu, int position);
void moving(vector<string>menu, int& position, char ch);
int menus(vector<string>menu);
void askQuery(vector<string>result, int choice);
void show(vector<string>menu, vector<string>CreateDatabaseMenu);