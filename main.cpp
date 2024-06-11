#include "scheduler.h"
using namespace std;

//*******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file helps test the implementation of event and its derived classes
// pool, library and trip.
// The functions that can be tested for each of these classes are -
// - booking a pool, or library or trip event
// - editing a pool, or library or trip event
// - canceling a pool, or library or trip event
// - display a pool, or library or trip event
//*******************************************************************************

//Function declarations to be used to create menu
void show_options();
void pool_booking(scheduler & my_scheduler);
void library_booking(scheduler & my_scheduler);
void trip_booking(scheduler & my_scheduler);

int main()
{
	char response = ' ';
	scheduler my_scheduler;
	cout << "Please enter the information about the person making the bookings" << endl;
	my_scheduler.set_person();
	do
	{
		cout << "Choose your options : " << endl;
		show_options();
		cin >> response;
		cin.ignore(100,'\n');
		switch (response)
		{
			case '1': pool_booking(my_scheduler); 
				  break;
			case '2': library_booking(my_scheduler);
				  break;
			case '3': trip_booking(my_scheduler);
				  break;
			case 'q': break;
			default: cout << "Wrong input. Try again or press 'q' to quit" << endl;
				 break;
		}
		cout << endl;
	} while (tolower(response) != 'q');

	return 0;
}

//method to test the trip class methods
void trip_booking(scheduler & my_scheduler)
{
	char response = 'N';
	do
	{
		my_scheduler.insert_data("trip");
		my_scheduler.display("trip");      
	} while(again());
	cout << "\n Do you wish to make changes to any of your trip booking? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.edit_trip_booking();		

	my_scheduler.display("trip");      

	cout << "\n Do you wish to clear all your trip bookings? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.remove_all_trips();

	my_scheduler.display("trip");      
}

//method to test the pool class methods using scheduler class
void pool_booking(scheduler & my_scheduler)
{
	char response = 'N';
	do
	{
		my_scheduler.insert_data("pool");
		my_scheduler.display("pool");      
	} while(again());
	cout << "\n Do you wish to cancel any of your pool bookings? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.remove_data("pool");		
	my_scheduler.display("pool");      

	cout << "\n Do you wish to clear all your pool bookings? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.removal_cll();

	my_scheduler.display("pool");      
}

//method to test the library class methods
void library_booking(scheduler & my_scheduler)
{
	char response = 'N';
	do
	{
		my_scheduler.insert_data("library");
		my_scheduler.display("library");      
	} while(again());
	cout << "\n Do you wish to cancel any of your library slots? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.remove_data("library");		

	my_scheduler.display("library");      

	cout << "\n Do you wish to clear all your library slots? Y/N:";	
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		my_scheduler.remove_all_library();

	my_scheduler.display("library");      
}

//method to display menu
void show_options()
{
	cout << "1 - Perform a pool booking, edit and cancel" << endl;
	cout << "2 - Perform a library booking, edit and cancel" << endl;
	cout << "3 - Perform a trip booking, edit and cancel" << endl;
	cout << "Press q to quit the program" << endl;
}

//Utility function to ask user if they want to repeat the same procedure
bool again()
{
	char response = 'N';
	cout <<"Do you want to repeat? Y/N - ";
	cin >> response;
	cin.ignore(100,'\n');
	if (toupper(response) == 'Y')
		return true;
	else
		return false;
}
