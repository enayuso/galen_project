#pragma warning(disable:4996)

#ifndef CAFELOGIN_H
#define CAFELOGIN_H

#include<iostream>
// #include<conio.h>
#include <cstdlib>
#include<time.h>
#include<fstream>
#include<string.h>
#include"cafemember.h"
using namespace std;

class Time
{
public:
	int date, hours, minutes, seconds;
	int loggedMemberID;
	char loggedMemberName[20];
};

class memberLogin :public memberEntry
{
public:
	int loggedToMemberID();
	void logout();
	void showLoggedIn();
	void showLoggedOut();
	void nonUser();
};

int memberLogin::loggedToMemberID()
{
	fflush(stdin);
	int temp = 0, count = 0;
	char userName[15];
	char passWord[15];
	cout << "Enter Member's Username: ";
	cin.getline(userName, 15);
	cout << "Enter Member's Password: ";
	{
		for (int i = 0;;)
		{
			char t = _getch();
			if ((t >= 'a' && t <= 'z') || (t >= 'A' && t <= 'Z') || (t >= '0' && t <= '9'))
			{
				passWord[i] = t;
				i++;
				cout << "*";
			}
			if (t == '\b' && i >= 1)
			{
				cout << "\b \b ";
				i--;
			}
			if (t == '\r')
			{
				passWord[i] = '\0';
				break;
			}
		}
	}
	ifstream checkLogged;
	checkLogged.open("LoggedMembers.txt", ios::app | ios::binary);
	checkLogged.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	while (!checkLogged.eof())
	{
		if (!strcmp(userName, username) && !strcmp(passWord, password))
		{
			cout << "\nThis Member is already logged in.\n";
			return 0;
		}
		checkLogged.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	ifstream inFile;
	inFile.open("MemberEntry.txt", ios::in | ios::binary);
	if (inFile.fail())
	{
		cout << "\nFile not found OR Error while opening File.\n";
		return 0;
	}
	inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	while (!inFile.eof())
	{
		if (!strcmp(userName, username) && !strcmp(passWord, password))
		{
			cout << "\nMember Successfully Logged In.";
			ofstream outFile, onTime, loggedMember;
			loggedMember.open("LoggedMembers.txt", ios::app | ios::binary);
			loggedMember.write(reinterpret_cast<char*>(this), sizeof(memberEntry));
			onTime.open("LoggedTime.txt", ios::app | ios::binary);
			time_t z = time(NULL);
			tm tm = *localtime(&z);
			Time t;
			strcpy_s(t.loggedMemberName, name);
			t.loggedMemberID = memberID;
			t.date = tm.tm_mday;
			t.hours = tm.tm_hour;
			t.minutes = tm.tm_min;
			t.seconds = tm.tm_sec;
			onTime.write(reinterpret_cast<char*>(&t), sizeof(t));
			onTime.close();
			count++;
			return memberID;
			break;
		}
		inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	}
	inFile.close();
	if (!count)
	{
		char ch;
		cout << "\nIncorrect Username or Password. Want to try again?\n";
		cout << "Enter 'y' for yes, 'n' for no: ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			loggedToMemberID();
	}
	return 0;
	inFile.close();
}

void memberLogin::logout()
{
	int temp, count = 0;
	fflush(stdin);
	char tempUser[15], tempPass[15];
	cout << "Enter Member's Username to Logout: ";
	cin.getline(tempUser, 15);
	cout << "\nEnter Member's Password to Logout: ";
	for (int i = 0;;)
	{
		char ch = _getch();
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
		{
			tempPass[i] = ch;
			i++;
			cout << "*";
		}
		if (ch == '\b' && i >= 1)
		{
			cout << "\b \b ";
			i--;
		}
		if (ch == '\r')
		{
			tempPass[i] = '\0';
			break;
		}
	}
	ofstream logMember, outFile;
	ifstream inFile;
	inFile.open("LoggedMembers.txt", ios::in | ios::binary);
	if (inFile.fail())
	{
		cout << "\nFailed to find logged-in Members.\n";
		return;
	}
	logMember.open("TempLoggedMembers.txt", ios::out | ios::binary);
	outFile.open("LoggedOutMembers.txt", ios::out | ios::app | ios::binary);
	inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	while (!inFile.eof())
	{
		if (!strcmp(tempUser, username) && !strcmp(tempPass, password))
		{
			outFile.write(reinterpret_cast<char*>(this), sizeof(memberEntry));
			ofstream outTime;
			outTime.open("LoggedOutTime.txt", ios::app | ios::in | ios::binary);
			time_t z = time(NULL);
			tm tm = *localtime(&z);
			Time w;
			strcpy_s(w.loggedMemberName, name);
			w.loggedMemberID = memberID;
			w.date = tm.tm_mday;
			w.hours = tm.tm_hour;
			w.minutes = tm.tm_min;
			w.seconds = tm.tm_sec;
			outTime.write(reinterpret_cast<char*>(&w), sizeof(Time));
			outTime.close();
			count++;
		}
		if(strcmp(tempUser, username) || strcmp(tempPass, password))
			logMember.write(reinterpret_cast<char*>(this), sizeof(memberEntry));
		inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	}
	if (count)
		cout << "\t\t\tSuccessfuly logged out Member.\n";
	if (!count)
		cout << "\nUnable to log out Member - Member is currently logged in.\n";
	inFile.close();
	outFile.close();
	logMember.close();
	remove("LoggedMembers.txt");
	rename("TempLoggedMembers.txt", "LoggedMembers.txt");
	while (_getche() != '\r');
}

void memberLogin::showLoggedIn()
{
	cout << "---------------------------Logged-In Members---------------------------\n";
	ifstream inFile;
	inFile.open("LoggedMembers.txt", ios::in | ios::binary);
	if (!inFile)
	{
		cout << "Failed to find logged-in Members.";
		return;
	}
	inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	while (!inFile.eof())
	{
		showMemberInfo();
		cout << "_______________________________\n";
		inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	}
	inFile.close();
}

void memberLogin::showLoggedOut()
{
	cout << "---------------------------Logged-Out Members---------------------------\n";
	ifstream inFile;
	inFile.open("LoggedMembers.txt", ios::in | ios::binary);
	if (!inFile)
	{
		cout << "Failed to find logged-out Members.";
		return;
	}
	inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	while (!inFile.eof())
	{
		showMemberInfo();
		cout << "_______________________________\n";
		inFile.read(reinterpret_cast<char*>(this), sizeof(memberEntry));
	}
	inFile.close();
}

void memberLogin::nonUser()
{
	getMemberInfo();
	storeMember();
	system("cls");
	cout << "\n\nEnter Username and Password to Login.\n";
	loggedToMemberID();
}

#endif //CAFELOGIN_H