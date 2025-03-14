#include<iostream>
#include<fstream>
#include<process.h>
#include<string>

#include"cafeCharge.h"
#include"cafeComputer.h"
#include"cafeLogin.h"
#include"cafemember.h"

void validCheck();
int x, choice, temp;
void mainMenu();
void entryMenu();
//void memberEntryMenu();
//void computerMenu();
void cafeManage();
void cafeBook();

using namespace std;

int main()
{
	system("COLOR 70");
	cout << "\n\t\t\t\tCyber Cafe Database Management System.\n\n";
	system("pause");
	system("cls");
	system("COLOR 70");
	string uName = "Enrique"; // Initial Username for "Personnel Only"
	string uPass = "Pp222"; // Initial Password
	fflush(stdin);
	string _user;
	char _pass[15];
	for (int i = 0; i < 3; i++)
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t    -----------------LOG IN TO SYSTEM-------------------";
		cout << "\n\n\n\n\n";
		cout << "\n\t\t\t\t Enter Username: ";
		getline(cin, _user);
		cout << "\n\t\t\t\t Enter Password: ";
		{
			char ch;
			for (int i = 0;;)
			{
				ch = _getch();
				if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
				{
					_pass[i] = ch;
					i++;
					cout << "*";
				}
				if (ch == '\b' && i >= 1)
				{
					cout << "\b \b";
					i--;
				}
				if (ch == '\r')
				{
					_pass[i] = '\0';
					break;
				}
			}
		}
		if (_user == uName && _pass == uPass)
		{
			cout << "\n\n\t\t\t\tSuccessfully Logged-In. Press Enter to continue...\n";
			while (_getche() != '\r');
			mainMenu();
		}
		cout << "\n\n\t\t\t\tInvalid Username or Password. Kindly try again...\n";
		while (_getche() != '\r');
	}
	return 0;
}

void mainMenu()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
	cout << "\n\n";
	cout << "\t\t\t\t           MAIN MENU         \n";
	cout << "\t\t\t\t     ________________________\n";
	cout << "\t\t\t\t      |                        |";
	cout << "\n\t\t\t\t    |     1. Master Entry    |";
	cout << "\n\t\t\t\t    |     2. Cafe Managment  |";
	cout << "\n\t\t\t\t    |     3. Exit            |\n";
	cout << "\t\t\t\t  |________________________|\n";
	cout << "\n\n";
	validCheck();
	switch (choice)
	{
	case 1:
		entryMenu();
		break;
	case 2:
		cafeManage();
		break;
	case 3:
		exit(0);
		break;
	default:
		cout << "Invalid choice. Kindly try again...\n ";
		return mainMenu();
		break;
	}
}

void entryMenu()
{
	cafeComputer c;
	memberEntry m;
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
	cout << "\n\n";
	cout << "\t\t\t\t         ENTRY MENU          \n";
	cout << "\t\t\t\t    ________________________\n";
	cout << "\t\t\t\t    |                        |";
	cout << "\n\t \t\t \t|     1. Member Entry    |";
	cout << "\n \t\t\t \t|     2. Computer Entry  |";
	cout << "\n \t\t\t \t|     3. Exit            |\n";
	cout << "\t\t\t    \t|________________________|\n";
	cout << "\n\n";
	validCheck();
	switch (choice)
	{
	case 1:
		m.memberEntryMenu();
		entryMenu();
		break;
	case 2:
		c.computerMenu();
		entryMenu();
		break;
	case 3:
		return mainMenu();
		break;
	default:
		cout << "Invalid choice. Kindly try again...\n ";
		return entryMenu();
		break;
	}
}

void cafeManage()
{
	memberEntry me;
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
	cout << "\n\n";
	cout << "\t\t\t\t		CAFE MANAGMENT         \n";
	cout << "\t\t\t\t     ________________________\n";
	cout << "\t\t\t\t    |                        |";
	cout << "\n\t \t\t \t|     1. Booking         |";
	cout << "\n \t\t\t \t|     2. Charges         |";
	cout << "\n \t\t\t \t|     3. Return          |\n";
	cout << "\t\t\t    \t|________________________|\n";
	cout << "\n\n";
	validCheck();
	Charge ch;
	switch (choice)
	{
	case 1:
		cafeBook();
		break;
	case 2:
		system("cls");
		ch.chargeMenu();
		return cafeManage();
		break;
	case 3:
		return mainMenu();
		break;
	default:
		cout << "Invalid choice ! Renter ";
		return cafeManage();
		break;
	}
}

void cafeBook()
{
	system("cls");
	cout << "\n\n\n\n\t\t\t        ";
	cout << "\n\n";
	cout << "\t\t\t       MEMBER MANAGEMENT        \n";
	cout << "\t\t\t     _______________________________________\n";
	cout << "\t\t\t    |                                       |";
	cout << "\n\t \t \t|     1. Member log in                  |";
	cout << "\n \t\t \t|     2. Member log out                 |";
	cout << "\n \t\t \t|     3. Non Member User Log in         |";
	cout << "\n \t\t \t|     4. Logged in members              |";
	cout << "\n \t\t \t|     5. Which members used systems ??  |";
	cout << "\n \t\t \t|     6. Return                         |\n";
	cout << "\t\t    \t|_______________________________________|\n";
	cout << "\n\n";
	memberLogin m;
	cafeComputer c;
	validCheck();
	switch (choice)
	{
	case 1:
	case1:
		system("cls");
		if (c.searchComputerInfo())
		{
			cout << "\t\t\tComputer found.\n\t\t\t Enter Username and Password. \n";
			x = m.loggedToMemberID();
			int i = x;
			if (x)
			{
				ifstream in;
				in.open("UsingComputer.txt", ios::binary);
				if (in.fail())
					goto newComp;
				in.read(reinterpret_cast<char*>(&c), sizeof(c));
				in >> x;
				while (!in.eof())
				{
					if (i == x)
					{
						cout << "Computer's in use. ";
						return;
					}
					in.read(reinterpret_cast<char*>(&c), sizeof(c));
					in >> x;
				}
				in.close();
			newComp:
				ofstream out;
				out.open("UsingComputer.txt", ios::app | ios::binary);
				out.write(reinterpret_cast<char*>(&c), sizeof(c));
				out << x;
				out.close();
			}
		}
		else
		{
			cout << "\nDo you wish to retry?\n ";
			cout << "Enter 'y' for yes, 'n' for no.\n";
			char ch;
			cin >> ch;
			if (ch == 'y' || ch == 'y')
				goto case1;
			else
				return cafeBook();
		}
		while (_getche() != '\r');
		return cafeBook();
		break;
	case 2:
		system("cls");
		m.logout();
		return cafeBook();
		break;
	case 3:
		system("cls");
		cout << "You're loggin as a Non-Member, hence:\n";
		cout << "1- Provide required information to become a Member.\n";
		cout << "2- Set your Username and Password.\n";
		cout << "3- Enter Username and Password to Login\n\n";
		m.nonUser();
		while (_getche() != '\r');
		return cafeBook();
		break;
	case 4:
		system("cls");
		m.showLoggedIn();
		while (_getche() != '\r');
		return cafeBook();
		break;
	case 5:
		system("cls");
		m.showLoggedOut();
		while (_getche() != '\r');
		return cafeBook();
		break;
	case 6:
		return cafeManage();
		break;
	default:
		cout << "Invalid choice. Kindly try again...\n";
		return cafeBook();
		break;
	}
}

void validCheck()
{
	while (1)
	{
		cout << "\t\t\t\t Enter your choice:  ";
		cin >> choice;
		if (cin.good())
			break;
		cin.clear();
		cout << "\t\t\tInvalid choice. Kindly try again..." << endl;
		cin.ignore(10, '\n');
	}
}