// Colby Cabrera
// FinalProject_ColbyCabrera.cpp
// A car rental system
// Visual Studio 2019

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Car {

public:
	string type;
	string name;
	int price;

	Car() {
	
		type = "none set";
		name = "none set";
		price = 0;
	}

	Car(string t, string n, int p) {

		type = t;
		name = n;
		price = p;
	}
};

void menu(Car* array[5], int size[], int whichMenu, int& carType);

void rent(Car* array[5], int size[], int carType);

void buy(Car* array[5], int size[], int carType);

void carSelect(Car* array[5], int size[], int& carType, int& carChoice, bool isRental);

void fillArray(ifstream& input, Car* array[5], int size[]);
// Requires the CarList.txt file to be in the E:// drive

void fileOutput(string name, string carChoice, int days, bool isRental);
// Creates and appends rental and purchase data to the RentalAndPurchaseLog.txt file in the E:// drive

int main() {

	int carType;

	ifstream carListFile;
	carListFile.open("E:\\CarList.txt");

	typedef Car* CarPtr;

	CarPtr cars[5];
	int size[5] = { 6, 5, 3, 4, 2 };

	cars[0] = new Car[6];
	cars[1] = new Car[5];
	cars[2] = new Car[3];
	cars[3] = new Car[4];
	cars[4] = new Car[2];

	fillArray(carListFile, cars, size);

	cout << "Welcome to Rent a Car Rentals!";

	menu(cars, size, 0, carType);

	return 0;
}

void menu(Car* array[5], int size[], int whichMenu, int& carType) {

	int choice;

	if (whichMenu == 0) {
	
		cout << "\n\nMenu\n";
		cout << "1: Rent\n";
		cout << "2: Buy\n";
		cout << "3: Exit\n";

		cin >> choice;

		while (choice > 3 || choice < 1) {

			cout << "Number must be 1, 2, or 3, try again: ";

			cin >> choice;
		}

		if (choice == 1) {

			rent(array, size, carType);
		}

		else if (choice == 2) {

			buy(array, size, carType);
		}

		else {

			exit(0);
		}

		choice = 0;
	}

	else {

		cout << "\nWe offer sedans, pickup trucks, minivans, SUVs, and sports cars!";
		cout << "\nSelect a car type:\n";
		cout << "1: Sedans\n";
		cout << "2: Pickup Trucks\n";
		cout << "3: Minivans\n";
		cout << "4: SUVs\n";
		cout << "5: Sports Cars\n";

		cin >> carType;

		while (carType > 5 || carType < 1) {

			cout << "Number must be 1, 2, 3, or 5, try again: ";

			cin >> carType;
		}

		carType--;
	}
}

void rent(Car* array[5], int size[], int carType) {

	int carChoice, days;
	const double TAX = 0.06;
	double cost, totalCost;
	string name, lineEnd;

	menu(array, size, 1, carType);

	carSelect(array, size, carType, carChoice, true);

	cout << "How many days are you renting the car? ";
	cin >> days;

	while (days < 1) {

		cout << "You can only rent a car for one more more days, try again:  ";
		cin >> days;
	}

	cost = days * (array[carType][carChoice - 1].price / 1200.0);

	totalCost = cost + (cost * TAX);

	cout << "\nCost before 6% tax: $" << cost << endl;
	cout << "Total cost:         $" << totalCost << endl;

	cout << "Enter a name for your rental: ";
	getline(cin, lineEnd);
	getline(cin, name);

	cout << "Thank you for shopping at Rent a Car Rentals!";

	fileOutput(name, array[carType][carChoice - 1].name, days, true);

	menu(array, size, 0, carType);
}

void buy(Car* array[5], int size[], int carType) {

	const double TAX = 0.06;
	double cost, totalCost;
	string name, lineEnd;
	int carChoice;

	menu(array, size, 1, carType);

	carSelect(array, size, carType, carChoice, false);

	cost = array[carType][carChoice - 1].price;

	totalCost = cost + (cost * TAX);

	cout << "\nCost before 6% tax: $" << cost << endl;
	cout << "Total cost:         $" << totalCost << endl;

	cout << "Enter a name for your purchase: ";
	getline(cin, lineEnd);
	getline(cin, name);

	cout << "Thank you for shopping at Rent a Car Rentals!";

	fileOutput(name, array[carType][carChoice - 1].name, 0, false);

	menu(array, size, 0, carType);
}

void fileOutput(string name, string carChoice , int days, bool isRental) {

	ofstream log;
	log.open("E:\\RentalAndPurchaseLog.txt", ios::app);

	log << name << endl;
	log << carChoice << endl;
	
	if (isRental) {

		log << "Rental" << endl;
		log << days << " days" << endl;
	}

	else {

		log << "Purchase" << endl;
	}
	
	log << endl;

	log.close();
}

void fillArray(ifstream& input, Car* array[5], int size[]) {
	
	string type, name, strPrice, space;
	int price, k = 0;

	for (int i = 0; i < 5; i++) {

		for (int j = 0; j < size[k]; j++)
		{

			getline(input, type);
			getline(input, name);
			getline(input, strPrice);
			getline(input, space);

			price = stoi(strPrice);

			array[i][j] = Car(type, name, price);
		}

		k++;
	}
}

void carSelect(Car* array[5], int size[], int& carType, int& carChoice, bool isRental) {

	cout.setf(ios::fixed);
	cout.setf((ios::showpoint));
	cout.precision(2);

	cout << "\nSelect a car:\n";

	if (isRental) {

		for (int j = 0; j < size[carType]; j++) {

			cout << j + 1 << ": " << array[carType][j].name;
			cout << " $" << array[carType][j].price / 1200.0 << " per day.\n";
		}
	}

	else {

		for (int j = 0; j < size[carType]; j++) {

			cout << j + 1 << ": " << array[carType][j].name;
			cout << " $" << array[carType][j].price << endl;
		}
	}

	cout << "0: Back to Menu.\n";
	cin >> carChoice;
	
	if (carChoice != 0) {

		while (carChoice > size[carType] || carChoice < 1) {

			cout << "Number must be a valid selection, try again: ";

			cin >> carChoice;
		}
	}

	else {

		menu(array, size, 0, carType);
	}
}