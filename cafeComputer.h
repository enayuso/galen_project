#ifndef CAFECOMPUTERS_H
#define CAFECOMPUTERS_H

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string.h>
// #include<conio.h>
#include <cstdlib>

using namespace std;

//void computerMenu();

class cafeComputer
{
protected:
	char compName[20];
	char ipAddress[12];
	char compCode[20];
public:
	void getComputerInfo();
	void showComputerInfo() const;
	void storeComputer();
	void deleteComputerInfo();
	void updateComputerInfo();
	void readComputerInfo();
	bool searchComputerInfo();
	void searchComputerInfoEntry();
	void computerMenu();
};

void cafeComputer::getComputerInfo()
{
	int count = 0;
	char tempName[20];
	fflush(stdin);
	cout << "Enter Computer's Name: ";
	cin.getline(compName, 20);
	strcpy_s(tempName, compName);
getIP: // IP Address Check beings here
	cout << "Enter Computer's IP Address: ";
	cin.getline(ipAddress, 12);
	for (int i = 0; i < strlen(ipAddress); i++)
	{
		if (isdigit(ipAddress[i]) || ipAddress[i] == '.')
			continue;
		else
		{
			cout << "\nInvalid IP Address. Must only contain digits and fullstops.\n";
			goto getIP;
		}
	}
	if (strlen(ipAddress) < 4 || strlen(ipAddress) > 12)
	{
		cout << "\nInvalid IP Address. Must contain 4-12 characters. Kindly try again.\n";
		goto getIP;
	}
	for (int i = 0; i < strlen(ipAddress); i++)
	{
		if (ipAddress[i] == '.')
			count++;
	}
	if (count < 2)
	{
		cout << "\nInvalid IP Address. Must have at least two (2) fullstops.\n";
		goto getIP;
	}
	// IP Checking ends here
	char tempIP[12]; // was 50
	strcpy_s(tempIP, ipAddress);
	fflush(stdin); // might have to be removed
setCode:
	cout << "\nEnter Computer's Code: ";
	cin.getline(compCode, 20);
	char tempCode[20];
	strcpy_s(tempCode, compCode);
	ifstream check;
	check.open("ComputerEntry.txt", ios::in | ios::binary);
	if (check.fail())
		goto output;
	check.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!check.eof())
	{
		if (!strcmp(tempCode, compCode))
		{
			cout << "\nComputer Code alraedy exists in System.\n";
			goto setCode;
		}
		check.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
output:
	strcpy_s(compName, tempName);
	strcpy_s(ipAddress, tempIP);
	strcpy_s(compCode, tempCode);
}

void cafeComputer::showComputerInfo() const
{
	cout << "Computer Name         : " << compName << endl;
	cout << "Computer IP Address   : " << ipAddress << endl;
	cout << "Computer Code         : " << compCode << endl;
	cout << "__________________________________________________" << endl;

}

void cafeComputer::storeComputer()
{
	ofstream comp;
	comp.open("ComputerEntry.txt", ios::app | ios::binary);
	comp.write(reinterpret_cast<char*>(this), sizeof(*this));
	comp.close();
	cout << "Computer Information has been successfully saved to external file.";
}

void cafeComputer::readComputerInfo()
{
	ifstream temp;
	temp.open("ComputerEntry.txt", ios::in | ios::binary);
	if (temp.fail())
	{
		cout << "\nFile not found OR Error while opening file.\n";
		return;
	}
	cout << "----------------Computer Information from File--------------------" << endl;
	temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!temp.eof())
	{
		showComputerInfo();
		temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	temp.close();
}

void cafeComputer::searchComputerInfoEntry()
{
	fflush(stdin);
	int count = 0;
	char cc[20];
	cout << "\nEnter Computer Code to search: ";
	cin.getline(cc, 20);
	ifstream search;
	search.open("ComputerEntry.txt", ios::in | ios::binary);
	if (search.fail())
	{
		cout << "\nFile not found OR Error while opening file.\n";
		return;
	}
	search.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!search.eof())
	{
		if (!strcmp(cc, compCode))
		{
			showComputerInfo();
			count++;
			return;
		}
		search.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	if (!count)
	{
		cout << "\nThere's no Computer in the System with this Code.\n";
		return;
	}
	search.close();
}

bool cafeComputer::searchComputerInfo()
{
	fflush(stdin);
	char cc[20];
	int count = 0;
	cout << "\nEnter Computer Code to search: ";
	cin.getline(cc, 20);
	ifstream temp;
	temp.open("UsingComputer.txt", ios::binary);
	if (temp.fail())
	{
		goto seeOutput;
	}
	temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!temp.eof())
	{
		if (!strcmp(cc, compCode))
		{
			cout << "\t\t\tComputer is already in use.\n";
			return false;
		}
		temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
seeOutput:
	temp.close();
	ifstream search;
	search.open("ComputerEntry.txt", ios::in | ios::binary);
	if (search.fail())
	{
		cout << "\nFile not found OR Error while opening File.\n";
		return false;
	}
	search.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!search.eof())
	{
		if (!strcmp(cc, compCode))
		{
			showComputerInfo();
			count++;
			return true;
		}
		search.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	if (!count)
	{
		cout << "\nThere's no Computer with this Code.\n";
		return false;
	}
	search.close();
}

void cafeComputer::deleteComputerInfo()
{
	fflush(stdin);
	char cc[20];
	int count = 0;
	cout << "\nEnter the Computer's Code to delete: ";
	cin.getline(cc, 20);
	ofstream out;
	ifstream in;
	in.open("ComputerEntry.txt", ios::in | ios::binary);
	if (in.fail())
	{
		cout << "\nFile not found OR Error while opening file.\n";
		return;
	}
	out.open("TempComputer.txt", ios::out | ios::binary);
	in.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!in.eof())
	{
		if (!strcmp(cc, compCode))
		{
			cout << "\t\t\tComputer found. Do you want to delete?\n";
			cout << "Enter 'y' for yes, 'n' for no: \n";
			if (_getche() == 'n' || _getche() == 'N')
			{
				out.close();
				remove("TempComputer.txt");
				return;
			}
			count++;
		}
	deleteComp:
		if(strcmp(cc, compCode)) // double check
			out.write(reinterpret_cast<char*>(this), sizeof(*this));
		in.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	in.close();
	out.close();
	if (!count)
		cout << "\nComputer does not exist in System.";
	if (count) // double check
		cout << "\nComputer Information successfully deleted.";
	remove("ComputerEntry.txt");
	rename("TempComputer.txt", "ComputerEntry.txt");
}

void cafeComputer::updateComputerInfo()
{
	fflush(stdin);
	char cc[20];
	int count = 0;
	cout << "Enter Computer's Code to update: ";
	cin.getline(cc, 20);
	fstream temp;
	temp.open("ComputerEntry.txt", ios::in | ios::out | ios::ate || ios::binary);
	if (temp.fail())
	{
		cout << "\nFile not found OR Error while opening file.\n";
		return;
	}
	temp.seekg(0);
	temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!temp.eof())
	{
		if (!strcmp(cc, compCode))
		{
			cout << "\t\t\tComputer found. Do you want to update?\n";
			cout << "Enter 'y' for yes, 'n' for no.\n";
			if (_getche() == 'n' || _getche() == 'N') // double check
				return;
			system("cls");
			cout << "\t\t\t\t Enter new Computer Information.\n";
			getComputerInfo();
			int pos = temp.tellp();
			temp.seekp(pos - sizeof(*this)); // why an error?
			temp.write(reinterpret_cast<char*>(this), sizeof(*this));
			count++;
		}
		temp.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	temp.close();
	if (!count)
		cout << "\nThe Computer Information does not exist.\n";
	if (count)
		cout << "\nComputer Information successfully updated.\n";
}

void cafeComputer::computerMenu()
{
	cafeComputer c;
	int choice;
	while (true)
	{
		cout << "\n\n\n\n\t\t\t        ";
		cout << "\n\n";
		cout << "\t\t\t      COMPUTER MENU          ";
		cout << "\n\t\t\t\t   __________________________";
		cout << "\n\t\t\t\t  |                          |";
		cout << "\n\t\t \t \t|     1. Add Computer      |";
		cout << "\n \t\t\t \t|     2. Show Computers    |";
		cout << "\n \t\t\t \t|     3. Search Computer   |";
		cout << "\n \t\t\t \t|     4. Delete Computer   |";
		cout << "\n \t\t\t \t|     5. Update Computer   |";
		cout << "\n \t\t\t \t|     6. Return            |\n";
		cout << "\t\t    \t\t|__________________________|\n";
		cout << "\n\n";
		while (1)
		{
			cout << "\t\t\t\t Enter choice: ";
			cin >> choice;
			if (cin.good())
				break;
			cin.clear();
			cout << "\t\t\tInvalid choice. Kindly try again." << endl;
			cin.ignore(10, '\n');
		}
		switch (choice)
		{
		case 1:
			system("cls");
			char temp;
			do
			{
				getComputerInfo();
				storeComputer();
				cout << "\nDo you wish to add another Computer to the system?\n";
				cout << "Enter 'y' for yes, 'n' for no.\n";
				cin >> temp;
			} while (temp == 'y' || temp == 'Y');
			break;
		case 2:
			system("cls");
			readComputerInfo();
			while (_getche() != '\r');
			break;
		case 3:
			system("cls");
			searchComputerInfoEntry();
			while (_getche() != '\r');
			break;
		case 4:
			system("cls");
			deleteComputerInfo();
			while (_getche() != '\r');
			break;
		case 5:
			system("cls");
			updateComputerInfo();
			while (_getche() != '\r');
			break;
		case 6:
			return;
			break;
		default:
			cout << "Invalid choice. Kindly try again.\n";
			return computerMenu();
			break;
		}
	}
}

#endif // CAFECOMPUTERS_H