#ifndef CAFEMEMBERS_H
#define CAFEMEMBERS_H

#include<iostream>
#include<fstream> // input and output file stream
#include<string.h>
#include<iomanip>
// #include<conio.h> // used for getch(), getche()
#include <cstdlib>
#include<time.h> // for time and date functions
// #include<windows.h> // for using Win32 API functions
#include<stdio.h> // getting input from keyboard and output result to monitor

using namespace std;

//void memberEntryMenu(); // modify name later *********
int year, month, day, id, redays, i;

class memberEntry
{
protected:
	char name[20]; // Member Name
	int memberID; // Member ID
	char address[50]; // Member Address
	char email[30]; // Member Email Account
	char phoneNumber[15]; // Member Phone Number
	char username[15]; // Member Account Username
	char password[15]; // Member Account Password
public:
	void storeMember(); // Storing Member Info
	void getMemberInfo(); // Getting Member Info
	void showMemberInfo() const; // Display Info
	void showMemberInfo2() const; // Display other Info
	void readRecord(); // Reading Info to File
	void updateRecord(int); // Updating Info from File
	void searchRecord(); // Search Info from File
	void searchRecordName(); // Search Info by Name
	void deleteRecord(); // Erase Info from File
	//void renew(); // Renewal
	//void renewCheck(); // modify name later**********8
	//void showRenew(); // Display those who renewed
	//void checkRenew_finished(); // change name later *********
	void memberEntryMenu(); // same as the global ******8
};

void memberEntry::getMemberInfo()
{
	char tempName[20];
	fflush(stdin); // Flushing output buffer of the stream
getName:
	cout << "Enter Member's Name: ";
	cin.getline(name, 20);
	strcpy_s(tempName, name); // Copies by source to destination
	for (int i = 0; i < strlen(name); i++) // strlen() calculates length of string
	{
		if (isalpha(name[i]) || name[i] == ' ') // isalpha() checks if character is an alphabet letter or not
			continue;
		if (!isalpha(name[i]))
		{
			cout << "\nInvalid input (Name can only consist of Alphabets). Kindly try again\n";
			goto getName;
		}
	}
getID:
	while (1) // while true
	{
		cout << "Enter Member's ID: ";
		cin >> memberID;
		if (cin.good()) // cin.good() returns 0 if encountered problems 
			break;
		cin.clear();
		cout << "\nInvalid input. Kindly try again.\n";
		cin.ignore(20, '\n');
	}
	int i = memberID;
	ifstream checkMember; // file streaming
	checkMember.open("MemberEntry.txt", ios::in | ios::binary); // opens
	if (checkMember.fail()) // if at first member entry, then go to getAddress without file comparison 
	{
		goto getAddress;
	}
	checkMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!checkMember.eof()) // while not at end of file
	{
		if (i == memberID) // checks for same ID
		{
			cout << "\nID already exists for " << name << ". Kindly try again.\n";
			checkMember.close();
			goto getID;
		}
		checkMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	checkMember.close(); // closes
getAddress:
	memberID = i;
	strcpy_s(name, tempName);
	fflush(stdin);
	cout << "Enter Member's Address: ";
	cin.getline(address, 50);
	char tempAddress[50];
	strcpy_s(tempAddress, address);
getPhoneNo:
	cout << "\nEnter Member's Phone Number: ";
	cin.getline(phoneNumber, 15);
	for (int i = 0; i < strlen(phoneNumber); i++)
	{
		if (isdigit(phoneNumber[i])) // checks if character is a decimal digit character
			continue;
		if (!isdigit(phoneNumber[i]))
		{
			cout << "\nInvalid Phone Number (entered a non-digit character). Kindly try again.\n";
			goto getPhoneNo;
		}
	}
	if (strlen(phoneNumber) != 7)
	{
		cout << "\nInvalid Phone Number (must have 7 digits). Kindly try again.\n";
		goto getPhoneNo;
	}
	char tempPhoneNo[15];
	strcpy_s(tempPhoneNo, phoneNumber);
	cout << "\nEnter Member's Email: ";
	cin.getline(email, 30);
	char tempEmail[30];
	strcpy_s(tempEmail, email);
getUsername:
	cout << "\nEnter Member's Username: ";
	cin.getline(username, 15);
setPassword:
	cout << "Set Member's Password: ";
	{
		for (int i = 0;;) // ;; is used to indicate that it can leave from inside the block with a break statement
		{
			char temp = _getch(); // getch() reads a characte from the keyboard
			if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z') || (temp >= '0' && temp <= '9'))
			{
				password[i] = temp;
				i++;
				cout << "*";
			}
			if (temp == '\b' && i >= 1) // \b is backspace character
			{
				cout << "\b \b";
				i--;
			}
			if (temp == '\r')
			{
				password[i] = '\0';
				break;
			}
		}
		if (strlen(password) < 6)
		{
			cout << "\nInvalid Password (needs to be consist at least 7 digits). Kindly try again.\n";
			goto setPassword;
		}
	}
	char tempUsername[15], tempPassword[15];
	strcpy_s(tempUsername, username);
	strcpy_s(tempPassword, password);
	ifstream check;
	check.open("MemberEntry.txt", ios::in | ios::binary); // Opens
	if (check.fail())
	{
		goto revert;
	}
	check.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!check.eof())
	{
		if (!strcmp(tempUsername, username) && !strcmp(tempPassword, password)) // compares two string by every character
		{
			cout << "\nInvalid ( Two Members have identical Username and Password. Try again.\n";
			goto getUsername;
		}
		check.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
revert:
	memberID = i;
	strcpy_s(name, tempName);
	strcpy_s(address, tempAddress);
	strcpy_s(email, tempEmail);
	strcpy_s(phoneNumber, tempPhoneNo);
	strcpy_s(username, tempUsername);
	strcpy_s(password, tempPassword);
}

void memberEntry::showMemberInfo() const
{
	cout << "Member's Name: " << name << endl;
	cout << "Member's ID: " << memberID << endl;
	cout << "Member's Address: " << address << endl;
	cout << "Member's Email: " << email << endl;
	cout << "Member's Phone Number: " << phoneNumber << endl;
	cout << "Member's Username: " << username << endl;
	cout << "Member's Password: " << password << endl;
	cout << endl;
}

void memberEntry::showMemberInfo2() const
{
	cout << setw(22) << name << setw(7) << memberID << setw(20) << address << setw(15)
		<< phoneNumber << setw(30) << email << setw(15) << username << endl;
}

void memberEntry::storeMember()
{
	ofstream writeMember; // file output stream
	writeMember.open("MemberEntry.txt", ios::app | ios::binary);
	writeMember.write(reinterpret_cast<char*>(this), sizeof(*this));
	writeMember.close();
	cout << "\nSuccessfuly saved information to external file.\n";
}

void memberEntry::readRecord()
{
	i = 0;
	ifstream readMember; // file input stream
	readMember.open("MemberEntry.txt", ios::in | ios::binary);
	if (readMember.fail())
	{
		cout << "File not found OR Error while opening File.";
		return;
	}
	cout << "\n\nList Number       Member Name      ID           Address      Phone Number               Email                 Username\n;";
	cout << "_______________________________________________________________________________________________________________\n" << endl;
	readMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!readMember.eof())
	{
		i++;
		cout << setw(2) << i;
		showMemberInfo2();
		readMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	readMember.close(); // close
}

void memberEntry::searchRecord()
{
	int temp, count = 0;
	cout << "Enter Member's ID to search: ";
	cin >> temp;
	ifstream search;
	search.open("MemberEntry.txt", ios::in | ios::binary);
	if (search.fail())
	{
		cout << "File not found OR Error while opening File.";
		return;
	}
	search.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!search.eof())
	{
		if (temp == memberID)
		{
			cout << "_________________________________\n";
			cout << "\tSEARCHED MEMBER\n";
			cout << "_________________________________\n";
			showMemberInfo();
			count++;
			break;
		}
		search.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	if (!count)
	{
		cout << "\n ID " << temp << " not found." << endl;
	}
	search.close(); // close
}

void memberEntry::searchRecordName()
{
	ifstream sMember;
	ofstream wMember;
	wMember.open("TempFile.txt", ios::app | ios::binary);
	sMember.open("MemberEntry.txt", ios::in | ios::binary);
	sMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!sMember.eof())
	{
		wMember.write(reinterpret_cast<char*>(this), sizeof(*this));
		sMember.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	sMember.close();
	wMember.close();
	char cName[20];
	ifstream search;
	ofstream found;
	cout << "Enter Member's Name to search: ";
	for (int i = 0; i < 20; i++)
	{
		int count = 0;
		search.open("TempFile.txt", ios::in | ios::binary);
		cName[i] = _getche(); // gets character from keyboard and echoes to output screen
		system("cls");
		cout << "Enter Member's Name to search: ";
		for (int j = 0; j <= i; j++)
		{
			cout << cName[j];
		}
		cout << "\n\n       Member Name      ID           Address      Phone Number               Email                 Username\n";
		cout << "_______________________________________________________________________________________________________\n";
		search.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (!search.eof())
		{
			if (toupper(cName[i]) == name[i] || tolower(cName[i]) == name[i])
			{
				count++;
				cout << setw(18) << name << setw(7) << memberID << setw(20) << address << setw(15)
					 << phoneNumber << setw(30) << email << setw(15) << username << endl;
				found.open("File.txt", ios::app | ios::binary);
				found.write(reinterpret_cast<char*>(this), sizeof(*this));
				found.close();
			}
			search.read(reinterpret_cast<char*>(this), sizeof(*this));
		}
		search.close();
		remove("TempFile.txt"); // removing file from system
		rename("File.txt", "TempFile.txt"); // "replacing" the file
		if (!count)
		{
			remove("TempFile.txt");
			cout << "\nSearched record does not exist in System.\n";
			return;
		}
	}
	remove("TempFile.txt");
}

void memberEntry::deleteRecord()
{
	int temp;
	while (1)
	{
		cout << "Enter Member's ID to delete: ";
		cin >> temp;
		if (cin.good())
			break;
		cin.clear();
		cout << "\t\t\tInvalid input. Kindly try again." << endl;
		cin.ignore(10, '\n');
	}
	int count = 0;
	ifstream login;
	login.open("LoggedMembers.txt", ios::in | ios::binary);
	if (login.fail())
	{
		goto deleteMember;
	}
	login.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!login.eof())
	{
		if (temp == memberID)
		{
			cout << "\nMember is currently loggin in. Cannot delete until Member logs out.\n";
			return;
		}
		login.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
deleteMember:
	login.close();
	ofstream outFile;
	ifstream inFile;
	inFile.open("MemberEntry.txt", ios::in | ios::binary);
	if (inFile.fail())
	{
		cout << "\nFile not found OR Error while opening File.";
		return;
	}
	outFile.open("TempFile.txt", ios::out | ios::binary);
	inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!inFile.eof())
	{
		if (temp == memberID)
		{
			cout << "_________________________________\n";
			cout << " \tCURRENTLY DELETING MEMBER INFO\n";
			cout << "_________________________________\n";
			showMemberInfo();
			cout << "\n\nAre you sure you want to delete Member's Information? (Type 'y' or 'n')\n";
			if (_getche() == 'n' || _getche() == 'N')
			{
				outFile.close();
				remove("TempFile.txt");
				return;
			}
			count++;
		}
		if(temp != memberID) // double check here
			outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
		inFile.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	inFile.close();
	outFile.close();
	remove("MemberEntry.txt");
	rename("TempFile.txt", "MemberEntry.txt");
	if (!count)
		cout << "Member ID " << temp << " not found in System." << endl;
	if (count)
		cout << "Record successfully deleted from System.";
}

void memberEntry::updateRecord(int temp)
{
	fflush(stdin);
	int count = 0;
	ifstream login;
	login.open("LoggedMembers.txt", ios::in | ios::binary);
	if (login.fail())
		goto updateMember;
	login.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!login.eof())
	{
		if (temp == memberID)
		{
			cout << "\nMember is currently logged in. Cannot update information until Member logs out.\n";
			return;
		}
		login.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	login.close();
updateMember:
	fstream file;
	file.open("MemberEntry.txt", ios::in | ios::out | ios::ate | ios::binary);
	file.seekg(0); // to set position of next character to be extracted from input stream
	file.read(reinterpret_cast<char*>(this), sizeof(*this));
	while (!file.eof())
	{
		if (temp == memberID)
		{
			cout << "_________________________________\n";
			cout << " \tCURRENTLY UPDATING MEMBER'S INFORMATION\n";
			cout << "_________________________________\n";
			showMemberInfo();
			cout << "\n\nAre you sure you want to delete Member's Information? (Type 'y' or 'n')\n";
			if (_getche() == 'n' || _getche() == 'N')
				return;
			system("cls");
			cout << "\t\t\t\t Kindly enter new information.\n";
			getMemberInfo();
			int pos = file.tellp();
			file.seekp(pos - sizeof(*this));
			file.write(reinterpret_cast<char*>(this), sizeof(*this));
			count++;
		}
		file.read(reinterpret_cast<char*>(this), sizeof(*this));
	}
	file.close();
	if (!count)
		cout << "Information does not exist in System.";
	if (count)
		cout << "Successfully updated Member's Information.";
}

void memberEntry::memberEntryMenu()
{
	int choice;
	while (true)
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t        ";
		cout << "\n\n";
		cout << "\t\t\t\t MEMBER MENU         ";
		cout << "\n\t\t\t\t____________________________________";
		cout << "\n\t\t\t\t|                                   |";
		cout << "\n\t\t\t\t|      1. Add Member                |";
		cout << "\n\t\t\t\t|      2. Show Members              |";
		cout << "\n\t\t\t\t|      3. Search Member by ID       |";
		cout << "\n\t\t\t\t|      4. Search Member by Name     |";
		cout << "\n\t\t\t\t|      5. Delete Member             |";
		cout << "\n\t\t\t\t|      6. Update Member             |";
		cout << "\n\t\t\t\t|      2. Return                    |";
		cout << "\n\t\t\t\t_____________________________________\n";
		cout << "\n\n";
		while (1)
		{
			cout << "\t\t\t\t Kindly enter your choice: ";
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
			char ans;
			do
			{
				system("cls");
				cout << "\t\t\t---------ENTER NEW MEMBER INFORMATION---------\n";
				getMemberInfo();
				storeMember();
				cout << "\nDo you wish to continue adding a new member?\n";
				cout << "Enter 'y' for yes, 'n' for no: ";
				cin >> ans;
			} while (ans == 'y' || ans == 'Y');
			break;
		case 2:
			system("cls");
			readRecord();
			while (_getche() != '\r');
			break;
		case 3:
			system("cls");
			searchRecord();
			while (_getche() != '\r');
			break;
		case 4:
			system("cls");
			searchRecordName();
			while (_getche() != '\r');
			break;
		case 5:
			system("cls");
			deleteRecord();
			while (_getche() != '\r');
			break;
		case 6:
			system("cls");
			int t;
			cout << "Enter Member's ID to update: ";
			cin >> t;
			updateRecord(t);
			while (_getche() != '\r');
			break;
		case 7:
			return;
			break;
		default:
			cout << "Invalid choice. Kindly try again.";
			return memberEntryMenu();
			break;
		}

	}
}

#endif // CAFEMEMBERS_H