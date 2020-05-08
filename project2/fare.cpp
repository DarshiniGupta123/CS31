#include <iostream>
#include <string>
#include <iomanip> //the library for the identifier setprecision
using namespace std;
int main()
{
	cout << "Age of rider: ";
	int age;
	cin >> age; // inputs an age for the rider stored in the variable age
	cin.ignore(10000, '\n');

	cout << "Student? (y/n): ";
	string student; 
	getline(cin, student); // inputs if the rider is a student in the variable student 

	cout << "Destination: ";
	string destination; // stores the destination of the rider
	getline(cin, destination);

	cout << "Number of zone boundaries crossed: ";
	int zones; 
	cin >> zones; //the user inputs the number of zones they cross

	double fare;

	if (age < 18 && zones <= 1) //this if else ladder checks to see if there are any special discounts that apply to the rider and calculates the fare
		fare = 0.65;
	else if (student == "y" && zones <= 1)
		fare = 0.65;
	else if (age >= 65 && zones > 0)
		fare = 0.55 + (0.25 * zones);
	else if (age >= 65 && student == "y" && zones == 1)
		fare = 0.65;
	else if (age >= 65 && zones == 0)
		fare = 0.45;
	else
		fare = 1.35 + 0.55 * zones;

	if (age < 0)
		cout << "---\n" << "The age must not be negative" << endl; // this if else ladder attempts to check some incorrect data types the user inputs
	else if (student != "y" && student != "n")
		cout << "---\n" << "You must enter y or n" << endl;
	else if (destination == "")
		cout << "---\n" << "You must enter a destination" << endl;
	else if (zones < 0)
		cout << "---\n" << "The number of zone boundaries crossed must not be negative" << endl;
	else
		cout << "---\n" << "The fare to " << destination << " is $" << fixed << setprecision(2) << fare << endl; /* setprecision prevents fare from rounding off 
																													and keeps two places after the decimal point, and the fixed makes outputs such as $3.00 possible*/

} 
