#include<iostream>
#include<cctype>
#include<string>
#include <conio.h>
#include<windows.h>
#include<vector>
#include"Database.h"
using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textattr(int i) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

void login() {
    string username, password;
    char ch;
    system("cls");

    textattr(0x0b);
    gotoxy(15, 5);
    cout << "              Welcome to Our Databaase Managment System                  " << endl << endl << endl << endl;
    gotoxy(15, 7);

    textattr(0x0d);
    cout << "Enter your username: ";
    textattr(0x0e);
    cin >> username;

    textattr(0x0d);
    gotoxy(15, 9);
    cout << "Enter your password: ";
    textattr(0x0e);
    do {
        ch = _getch();
        switch (ch) {
        case 0:
            _getch();
            break;
        case 13:
            cout << endl;
            break;
        case 8:
            if (password.length() > 0) {
                password.erase(password.end() - 1);
                cout << ch << ' ' << ch;
            }
            break;
        default:
            password += ch;
            cout << '*';
            break;
        }
    } while (ch != 13);

    if (username != "admin" || password != "admin") {
        gotoxy(22, 11);
        textattr(0x0c);
        cout << "Access denied" << endl;
        gotoxy(22, 13);
        cout << "Enter any key to repeat again";
        _getch();
        login();
    }

    textattr(0x0a);
    gotoxy(30, 11);
    cout << "Access allowed!" << endl;
    gotoxy(30, 13);
    cout << "Press any key to containue....";
    ch = _getch();
    system("cls");
}

void PrintMenu(vector<string>menu, int position) {
    for (int i = 0; i < menu.size(); i++) {
        gotoxy(25, 5 + i);
        if (position == i) {
            textattr(0xb0);
        }
        cout << menu[i];
        textattr(0x0a);
    }
}

void moving(vector<string>menu, int& position, char ch) {
    switch (ch) {
    case 71: //home
        system("cls");
        break;

    case 79: // end
        system("cls");
        break;

    case 72: // up
        position--;
        if (position < 0) {
            position = menu.size() - 1;
        }
        break;

    case 80: // down
        position++;
        if (position > menu.size() - 1) {
            position = 0;
        }
        break;
    }
}

int menus(vector<string>menu) {
    int flag = 0, position = 0;
    char ch;
    do {
        //Print Menu on the screen
        PrintMenu(menu, position);

        //Take an order from the user
        ch = _getch();

        //Check the order
        switch (ch) {
        case -32: //Extend Character
            ch = _getch();
            moving(menu, position, ch);
            break;

        case 13: // Enter Character
            system("cls"); // To remove the previous message that print when the user pressed enter
            switch (position) {
            case 0: //Create New Database
                return 0;
                break;

            case 1: // Select Database
                return 1;
                break;

            case 2: // Delete Database
                return 2;
                break;

            case 3: // exit
                return 3;
                break;
            }
            break;

        case 27: //Exit character
            system("cls");
            return 3;
            break;
        }
    } while (flag == 0);
}

void show(vector<string>menu, vector<string>CreateDatabaseMenu) {
    Database d;

    int position = 0, choice;
    choice = menus(menu);
    system("cls");

    switch (choice) {
    case 0: // create Database
        d.CreateDatabase();

        system("cls");

        choice = menus(CreateDatabaseMenu);

        system("cls");

        switch (choice)
        {
        case 0: // new table
            d.CreateTable();
            break;

        case 1: //relationship

            break;

        case 2: //main menu
            show(menu, CreateDatabaseMenu);
            break;

        case 3: //exit
            cout << "Exit" << endl;
            break;
        }

        break;

    case 1: // select database
        d.ShowDatabases();
        break;

    case 2: //Delete Database
        d.DeleteDatabase("iti");
        break;

    case 3: //Exit
        cout << "Exit" << endl;
        break;
    }
}