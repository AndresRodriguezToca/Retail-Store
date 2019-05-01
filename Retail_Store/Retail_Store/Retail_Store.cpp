#include "pch.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
using namespace std;

//Main Class + Accessors and Mutators
class PersonData {
private:
	string lastName, firstName, address, city, state;
	short int zip;
	unsigned long long int phone;
public:
	void getInfo(string, string, string, string, string, int, unsigned long long int);
};
void PersonData::getInfo(string lastname, string firstname, string useraddress, string usercity, string userstate, int userzip, unsigned long long int userphone) {
	lastName = lastname;
	firstName = firstname;
	address = useraddress;
	city = usercity;
	state = userstate;
	zip = userzip;
	phone = userphone;
}

//CLass derived from PersonData + Accessors and Mutators
class customerData : public PersonData{
private:
	int customerNumber;
	bool mailingList;
public:
	int getcustomerNumber();
	void putmailingList(char);
};
//Assign customer number
int customerData::getcustomerNumber() {
	customerNumber = 1;
	
	ifstream file("Customers.txt");

	if (file.fail()) {
		ofstream DataFile;
		DataFile.open("Customers.txt", ios::app);
		DataFile << customerNumber << endl;
		DataFile.close();
		return customerNumber;
	}
	else {
		string line;
		int count = 0;

		while (getline(file, line)) {
			count++;
		}
		customerNumber = (count + customerNumber);
		file.close();

		ofstream DataFile;
		DataFile.open("Customers.txt", ios::app);
		DataFile << customerNumber << endl;
		DataFile.close();

		return customerNumber;
	}
	
}
void customerData::putmailingList(char List) {
	if (List == 'Y' || List == 'y') {
		mailingList = true;
	}
	else {
		mailingList = false;
	}
}

//Class derived from derived class of PersonData + Accessors and Mutators + PurchasesAmount File
class PreferredCustomer : public customerData{
private:
	double purchasesAmount = 0, discountLevel, fileNumber;
public:
	double getPurchasesAmount(double);
	double getdiscountAmount(double);
	double getTotalPurchasesAmount(double, int);

};
double PreferredCustomer::getTotalPurchasesAmount(double purchases, int customer) {

	ifstream file("Purchases.txt");
	string line;
	int count = 0;

	while (getline(file, line)) {
		count++;
		if (count == customer) {
			fileNumber = atoi(line.c_str());
		}
	}

	purchasesAmount = (fileNumber + purchases);
	file.close();

	count = 0;
	return purchasesAmount;
}
double PreferredCustomer::getPurchasesAmount(double purchases) {

		ifstream file("Purchases.txt");

		if (file.fail()) {
			ofstream DataFile;
			DataFile.open("Purchases.txt", ios::app);
			DataFile << purchases << endl;
			DataFile.close();
			purchasesAmount += purchases;
			return purchasesAmount;
		}
		else {

			ofstream DataFile;
			DataFile.open("Purchases.txt", ios::app);
			DataFile << purchases << endl;
			DataFile.close();
			purchasesAmount += purchases;
			return purchasesAmount;
		}

		
}
double PreferredCustomer::getdiscountAmount(double discount) {
	if (discount > 499 && discount < 1000) {
		discountLevel = 5.0;
		return discountLevel;
	}
	else if (discount > 999 && discount < 1500) {
		discountLevel = 6.0;
		return discountLevel;
	}
	else if(discount > 1499 && discount < 2000) {
		discountLevel = 7.0;
		return discountLevel;
	}
	else if(discount > 1999) {
		discountLevel = 10.0;
		return discountLevel;
	}
	else {
		cout << "\nSorry, the total amount you spend don't qualified to rewards." << endl;
		cout << "Have a nice day!";
		return 0;
	}
}

//Main Function
int main()
{
	string lastName, firstName, address, city, state;
	unsigned long long int phone;
	int customerNumber, zip, customer;
	double amount_purchase, more_purchases, discount, totalPurchases;
	char choice, response;
	PreferredCustomer DataUser;
	
	//Welcome
	cout << "\n\t\t**********************************\n\t\t**** Retail Store User Reward ****\n\t\t**********************************" << endl;
	cout << "\nWelcome to the Retail Store User Reward. You may have the opportunity to redeem up\nto $1500 discount on all futures purchases." << endl;
	// Ask for Customer Number if not continue
	cout << endl << "(If you don't have a customer number type '0')" << endl;
	cout << "Costumer Number: ";
	cin >> customer;
	
	if (customer == 0 ) {
		//Collect Info
		cout << "\nFirst Name: ";
		cin >> firstName;
		cout << "\nLast Name: ";
		cin >> lastName;
		cout << "\nMail Address: ";
		cin >> address;

		//Mailing List
		cout << "\nWould you like be on the Mailing List? (Y/N): ";
		cin >> choice;
		DataUser.putmailingList(choice);

		//Continue Collecting Info
		cout << "\nCity: ";
		cin >> city;
		cout << "\nState: ";
		cin >> state;
		cout << "\nZip: ";
		cin >> zip;
		cout << "\nPhone: ";
		cin >> phone;

		//Send info collected
		DataUser.getInfo(lastName, firstName, address, city, state, zip, phone);

		//Amount of Purchases
		cout << "\nPlease, enter the amount spend on purchase today: ";
		cin >> amount_purchase;

		//Validator
		while (amount_purchase < 0) {
			cout << "\nSorry that amount it's invalid please try again" << endl;
			cout << "Enter the total amount spend on purchase today: ";
			cin >> amount_purchase;
		}

		//Check if there it's another purchases.
		cout << "\nThere's any other amount missing? (N/Y): ";
		cin >> response;

		//Loop to gather all purchases remaining.
		while (response == 'Y' || response == 'y') {
			cout << "Enter the addicional amount spend: ";
			cin >> more_purchases;
			amount_purchase += more_purchases;

			cout << "There's any other purchases left? (N/Y): ";
			cin >> response;
		}
		//Finish program if amount entered it's less than $500.
		if (amount_purchase < 499) {
			cout << "\nSorry, the total amount you spend don't qualified to rewards." << endl;
			cout << "Have a nice day!";
			return 0;
		}
		else {
			totalPurchases = DataUser.getPurchasesAmount(amount_purchase);
			discount = DataUser.getdiscountAmount(totalPurchases);
			//Generate a random number for the costumer
			customerNumber = DataUser.getcustomerNumber();
			cout << "\nCongratulation you qualify for an amount of " << discount << "% of discount for all future purchases." << endl;
			cout << "Your Customer Number it's " << customerNumber << "\n\n" << endl;
		};
		return 0;
	}
	else {
		cout << "\nPlease, enter the amount spend on purchase today: ";
		cin >> amount_purchase;

		//Validator
		while (amount_purchase < 0) {
			cout << "\nSorry that amount it's invalid please try again" << endl;
			cout << "Enter the total amount spend on purchase today: ";
			cin >> amount_purchase;
		}

		//Check if there it's another purchases.
		cout << "\nThere's any other amount missing? (N/Y): ";
		cin >> response;

		//Loop to gather all purchases remaining.
		while (response == 'Y' || response == 'y') {
			cout << "Enter the addicional amount spend: ";
			cin >> more_purchases;
			amount_purchase += more_purchases;

			cout << "There's any other purchases left? (N/Y): ";
			cin >> response;
		}
		totalPurchases = DataUser.getTotalPurchasesAmount(amount_purchase, customer);
		discount = DataUser.getdiscountAmount(totalPurchases);
		cout << "\nCongratulation you qualify for an addicional discount of " << discount << "% of discount for all future purchases." << endl;
		return 0;
	}

	

}