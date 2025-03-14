#pragma warning(disable:4996)

#ifndef CAFECHARGE_H
#define CAFECHARGE_H

#pragma warning(suppress : 4996)
#include<iostream>
#include<fstream>
// #include<conio.h>
#include <cstdlib>
#include<time.h>
#include<string.h>
#include"cafeLogin.h"

using namespace std;

int memberCharge;

class Charge :public Time
{
public:
	void calculateCharge();
	void showCharges();
	void chargeMenu();
};

void Charge::calculateCharge()
{
	int temp, count = 0, count2 = 0;
	int minInTime, minOutTime, usedTime, chargeRate;
	string name;
	while (1)
	{
		cout << "\nEnter Member's ID to calculate charge: ";
		cin >> temp;
		if (cin.good())
			break;
		cin.clear();
		cout << "\t\t\tInvalid input. Kindly try again." << endl;
		cin.ignore(10, '\n');
	}
	ifstream calCharge;
	fflush(stdin);
	calCharge.open("LoggedTime.txt", ios::out | ios::binary);
	if (calCharge.fail())
	{
		cout << "Failed to find logged-in Member.";
		return;
	}
	calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!calCharge.eof())
	{
		if (temp == loggedMemberID)
		{
			cout << "\nLogin Time = " << hours << ":" << minutes << ":" << seconds;
			minInTime = (date * 24 * 60) + (hours * 60) + minutes;
			name = loggedMemberName;
			count2++;
			break;
		}
		calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	calCharge.close();
	ifstream outTime; // Opening Logout Time File
	outTime.open("LoggedOutTime.txt", ios::out | ios::binary);
	if (outTime.fail())
		goto output;
	outTime.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!outTime.eof())
	{
		if (temp == loggedMemberID)
		{
			cout << "\nLogout Time = " << hours << ":" << minutes << ":" << seconds;
			minOutTime = (date * 24 * 60) + (hours * 60) + minutes;
			count++;
			break;
		}
		outTime.read(reinterpret_cast<char*>(this), sizeof(Time));
	}
	outTime.close();
output:
	if (count == 0 && count2 == 1)
	{
		cout << "\nMember is currently logged-in, but charges are still added until now.\n";
		time_t z = time(NULL);
		tm tm = *localtime(&z);
		usedTime = ((tm.tm_mday * 24 * 60) + (tm.tm_hour * 60) + tm.tm_min) - minInTime;
		cout << endl;
		cout << name << " have used the System for a total of " << usedTime << " minutes until now.\n";
		while (1)
		{
			cout << "\nKindly enter Charge Rate per Minute: ";
			cin >> chargeRate;
			if (cin.good())
				break;
			cin.clear();
			cout << "\t\t\tInvalid Charge Rate. Kindly try again.\n";
			cin.ignore(10, '\n');
		}
		cout << "Charge = " << chargeRate * usedTime;
	}
	if (count == 1 && count2 == 1)
	{
		ofstream out;
		out.open("TempLogin.txt", ios::app | ios::binary);
		calCharge.open("LoggedTime.txt", ios::app | ios::binary);
		calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (!calCharge.eof())
		{
			if (temp != loggedMemberID)
			{
				out.write(reinterpret_cast<char*>(this), sizeof(*this));
			}
			calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
		}
		calCharge.close();
		out.close();
		remove("LoggedTime.txt");
		rename("TempLogin.txt", "LoggedTime.txt");
		out.open("TempLogout.txt", ios::app | ios::binary);
		calCharge.open("LoggedOutTime.txt", ios::out | ios::binary);
		calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (!calCharge.eof())
		{
			if (temp != loggedMemberID)
			{
				out.write(reinterpret_cast<char*>(this), sizeof(*this));
			}
			calCharge.read(reinterpret_cast<char*>(this), sizeof(*this));
		}
		calCharge.close();
		out.close();
		remove("LoggedOutTime.txt");
		rename("TempLogout.txt", "LoggedOutTime.txt");
		usedTime = minOutTime = minInTime;
		cout << endl;
		cout << name << " used the System for a total of " << usedTime << " minutes.\n";
		while (1)
		{
			cout << "Kindly enter the Charge Rate per Minute: ";
			cin >> chargeRate;
			if (cin.good())
				break;
			cin.clear();
			cout << "\t\t\tInvalid Charge. Kindly try again.\n";
			cin.ignore(10, '\n');
		}
		memberCharge = chargeRate * usedTime;
		cout << "Total Charge = " << memberCharge;
		ofstream cc;
		cc.open("allCharges.txt", ios::out | ios::app | ios::binary);
		cc << loggedMemberID << " " << memberCharge << " ";
		cc.close();
	}
	if (count == 0 && count2 == 0)
	{
		cout << "\nThe Member is currently logged out.]n";
	}
}

void Charge::showCharges()
{
	ifstream in;
	in.open("allCharges.txt", ios::in | ios::binary);
	if (in.fail())
	{
		cout << "\nFile not found OR Error while opening File.\n";
		return;
	}
	in >> loggedMemberID >> memberCharge;
	while (!in.eof())
	{
		cout << "Member's ID: " << loggedMemberID << endl;
		cout << "Member's Charge: " << memberCharge << endl;
		cout << "_______________________________" << endl;
		in >> loggedMemberID >> memberCharge;
	}
}

void Charge::chargeMenu()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t       ";
	cout << "\n\n";
	cout << "\t\t\t\t   CHARGE MENU               \n";
	cout <<    "\t\t   _______________________________________________\n";
	cout << "\n \t\t  |                                               |";
	cout << "\n \t\t  |      1. Calculate Charges for certain Member  |";
	cout << "\n \t\t  |      2. Show all Charges                      |";
	cout << "\n \t\t  |      3. Return                                |";
	cout << "\n \t\t   _______________________________________________";
	cout << "\n\n\n";
	int temp;
	while (1)
	{
		cout << "\t\t\t\t Enter your Choice: ";
		cin >> temp;
		if (cin.good())
			break;
		cin.clear();
		cout << "\t\t\tInvalid choice. Kindly try again.\n";
		cin.ignore(10, '\n');
	}
	switch (temp)
	{
	case 1:
		system("cls");
		calculateCharge();
		while (_getche() != '\r');
		return chargeMenu();
		break;
	case 2:
		system("cls");
		showCharges();
		while (_getche() != '\r');
		return chargeMenu();
		break;
	case 3:
		return;
	default:
		cout << "Invalid choice. Kindly try again.\n";
		return chargeMenu();
		break;
	}
}

#endif // CAFECHARGE_H