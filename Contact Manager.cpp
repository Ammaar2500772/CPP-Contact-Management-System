#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <thread>
#include <chrono>
#include <iomanip>

struct Contact {
	std::string name;
	std::string phone;
};
const int max = 100;


//Uppercase to lowercase 


std::string upper2lower(std::string str)
{
	bool check = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' '))
			check = true;
	}
	if (check)
		return std::string();

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
	}
	return str;
}


//loadContacts() is used to Load any prevous cotacts from a file into the programme.


void loadContacts(Contact* list, int* count)
{
	std::ifstream data;
	std::string line;
	data.open("My Contacts.txt");
	if (!data)
	{
		std::cout << "Error in loading File, as no previous file is present.\n";
		return;
	}
	*count = 0;
	while (*count < max && getline(data, line))
	{
		size_t pos = line.find_last_of(' ');
		list[*count].name = line.substr(0, pos);
		list[*count].phone = line.substr(pos + 1);
		*count = *count + 1;
	}
	data.close();
}


//showContacts() is used to display all the contacts including those that were loaded from a file. 


void showContacts(Contact* list, int count)
{
	std::cout << "\nShowing all Contacts: \n\n";
	std::cout << std::left << std::setw(30) << "Names" << "Contact Numbers: \n";
	std::cout << "----------------------------------------\n";
	for (int i = 0; i < count; i++)
	{
		std::cout << std::left << std::setw(30) << list[i].name << list[i].phone << "\n";
	}

}


//void addContact() is used to add a new contact to the Array.


void addContact(Contact* list, int* count)
{

	if (*count >= max)
	{
		std::cout << "A new contact cannot be added. Max number of contacts has reached.\n";
		return;
	}

	std::string name = " ", ph = " ", phone_num = " ";

	std::cout << "\n-------------- Add a Contact --------------\n\n";


	//cin.ignore(1000,'\n');
	std::cout << "Enter the name of the contact: ";
	std::getline(std::cin, name);


	//Input Validation for phone number.
	while (true)
	{
		std::cout << "Enter the phone number (03XXXXXXXXX): ";
		std::cin >> ph;

		//Checking if all are digits

		bool alldigit = true;
		for (int i = 0; i < ph.size(); i++)
		{
			if (!isdigit(ph[i]))
			{
				alldigit = false;
				break;
			}
		}
		if (alldigit)
		{
			if (ph.size() == 11)
				break;

			else
			{
				std::cout << "\nInvalid phone number! The phone number must be exactly 11 digits. Please Try Again.\n\n";
				continue;
			}
		}
		else
			std::cout << "\nInvalid phone number! The phone number must be all digits. Please Try Again.\n\n";
	}

	phone_num = ph.substr(0, 4) + "-" + ph.substr(4);

	list[*count].name = name;
	list[*count].phone = phone_num;
	*count = *count + 1;
	std::cout << "\nContact Added Successfully.\n";
}


//searchContact() is used to search for a contact in the array.


void searchContact(Contact* list, int count)
{
	std::string targetname = " ";
	int choice = 0;
	std::cin.ignore(1000, '\n');

	std::string name2 = " ";

	while (true)
	{
		int found = 0;

		std::cout << "\n-------------- Search for a Contact --------------\n\n";

		std::cout << "Enter the name of the person you want to search: ";
		std::getline(std::cin, targetname);

		targetname = upper2lower(targetname);

		bool matchfound = false;
		for (int i = 0; i < count; i++)
		{
			name2 = upper2lower(list[i].name);


			if (name2 == targetname || name2.find(targetname) != std::string::npos)
			{
				matchfound = true;
				found = i;
				break;
			}
		}
		if (matchfound)
		{
			std::cout << "\nFound the contact successfully! \n";
			std::cout << "------------------------------\n";
			std::cout << "Name: \t\t" << list[found].name << "\nContact no: \t" << list[found].phone;
			std::cout << "\n------------------------------\n";
		}
		else
			std::cout << "\nContact not found! This Person is not in your Contact list! \n";


		while (true)
		{
			std::cout << "\n1. Search for another Contact.\n";
			std::cout << "2. Exit.\n";
			std::cout << "Enter your choice (1 or 2): ";
			std::cin >> choice;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				std::cout << "Invalid input.\n";
				continue;
			}
			std::cin.ignore(1000, '\n');

			if (choice == 1 || choice == 2)
				break;

			std::cout << std::endl;
			std::cout << "Invalid Choice. Enter 1 or 2.\n";
		}

		if (choice == 2)
		{
			std::cout << "Search Menu Exited successfully";
			break;
		}

	}

}


//void saveContacts() is used to save all Contacts in a file.


void saveContact(Contact* list, int count)
{
	std::cout << "Saving the current contacts..." << std::flush;
	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::ofstream data2;
	data2.open("My Contacts.txt");

	for (int i = 0; i < count; i++)
	{
		data2 << list[i].name << " " << list[i].phone << std::endl;
	}
	data2.close();
	std::cout << "\rSaved! " << std::flush;

}


int main()
{
	Contact myContacts[max];
	int totalContacts = 0;
	int* count = nullptr;
	count = &totalContacts;

	std::string str;
	int choice = 0;

	while (true)
	{
		std::cout << "Enter \"Start\" to open the Menu or \"Exit\" to close the program: ";
		std::cin >> str;
		str = upper2lower(str);

		if (str == "exit")
		{
			std::cout << "\n\nProgram terminated successfully.\n";
			return 0;
		}
		else if (str == "start")
			break;
		else
			std::cout << "\nInvald Command! Try Again.\n\n";
	}

	loadContacts(myContacts, count);

	std::cout << "\n\n\t---------------------- Welcome to Contacts Manager ----------------------\n";

	while (true)
	{
		std::cout << "\nChoose one of the following Options: \n";
		std::cout << "1. Add a new Contact.\n2. Show all Contacts.\n3. Search for a Contact.\n4. Save all Contacts.\n5. Exit the program.\n\n";
		std::cout << "Your choice (1-5): ";
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "\nInvalid Input! Choice must be an integer between 1 and 5. Try Again.\n";
			continue;
		}

		if (choice == 1)
		{
			std::cin.ignore(1000, '\n');
			addContact(myContacts, count);

		}
		else if (choice == 2)
		{
			showContacts(myContacts, totalContacts);
		}
		else if (choice == 3)
		{
			searchContact(myContacts, totalContacts);
		}
		else if (choice == 4)
		{
			saveContact(myContacts, totalContacts);
		}
		else if (choice == 5)
		{
			std::cout << "Exiting the Program..." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::cout << "Program Exited Succcessfully! " << std::endl;
			break;
		}
		else
			std::cout << "Invalid Choice! Please Try Again.\n";
	}

	return 0;
}