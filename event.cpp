#include "event.h"

//*******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents the implementation of all methods belonging to the header
// file - event.h for the classes event, pool, library and trip.
// It implements the functions outlined in the event.h file and
// helps create, edit, display and cancel the events to an existing event instance.
//*******************************************************************************


//default contructor of event class
event::event(): org_name(nullptr), location(nullptr), date_time(nullptr),duration(0)
{
}

//copy constructor of event class
event::event(const event & source): org_name(nullptr), location(nullptr), date_time(nullptr),duration(0)
{
	if(!source.org_name || !source.location || !source.date_time || !source.duration)
		return;
	org_name = new char [strlen(source.org_name) + 1];
	strcpy(org_name, source.org_name);

	location = new char [strlen(source.location) + 1];
	strcpy(location, source.location);

	date_time = new char [strlen(source.date_time) + 1];
	strcpy(date_time, source.date_time);

	duration = source.duration;
}

//destructor of event class
event::~event()
{
	if(org_name)
		delete [] org_name;
	org_name = nullptr;

	if(location)
		delete [] location;
	location = nullptr;

	if(date_time)
		delete [] date_time;
	date_time = nullptr;

	duration = 0;
}

//method to book an event in the event base class
int event::create_event()
{
	char org_name_toadd[NAME];
	char location_toadd[LOCATION];
	if(org_name) 
		delete [] org_name;
	cout << "Please enter the organization name: ";
	cin.get(org_name_toadd, NAME, '\n');
	cin.ignore(100, '\n');
	org_name = new char[strlen(org_name_toadd) + 1];
	strcpy(org_name, org_name_toadd);

	if(location) 
		delete [] location;
	cout << "Please enter the location name: ";
	cin.get(location_toadd, LOCATION, '\n');
	cin.ignore(100, '\n');
	location = new char[strlen(location_toadd) + 1];
	strcpy(location, location_toadd);

	read_correct_date_time();

	cout << "Please enter the duration in hours to book the event: ";
	cin >> duration;
	cin.ignore(100, '\n');
	return 1;
}

//utility method to read the date time from user input in the correct format 
int event::read_correct_date_time()
{
	bool format_correct = true;
	int month, date, year, hour, minutes;
	char dash_dummy, space_dummy, colon_dummy;
	string temp_datetime = "";

	if(date_time) 
		delete [] date_time;
	do
	{
		format_correct = true;
		cout << "Please enter a date and time for the event as MM/DD/YYYY hh:mm: ";
		cin >> month >> dash_dummy >> date >> dash_dummy >> year >> space_dummy >> hour >> colon_dummy >> minutes;
		if (cin.fail())
		{
			cout << "ERROR -- You are not enetering the date in MM/DD/YYYY format \n";
			cin.clear(); 
			cin.ignore(1000, '\n');
		}
		else
			cin.ignore(100 , '\n');

		//check for invalid date & time
		if(year < 2021 || year > 2025)
		{
			cout << "Please enter dates between years 2021 and 2025" << endl;
			format_correct = false;
		}
		if(month <= 0 || month >= 12)
		{
			cout << "Please enter a valid month between 1 to 12" << endl;
			format_correct = false;
		}
		if(date <= 0 || date >= 31)
		{
			cout << "Please enter a valid date" << endl;
			format_correct = false;
		}
		if(hour < 0 || hour > 23)
		{
			cout << "Please enter a valid hour between 0 and 23" << endl;
			format_correct = false;
		}
		if(minutes < 0 || minutes >= 60)
		{
			cout << "Please enter a valid minute between 0 and 59" << endl;
			format_correct = false;
		}

	}while(!format_correct);

	temp_datetime = to_string(month) + "-" + to_string(date) + "-" + to_string(year) + " "
		+ to_string(hour) + ":" + to_string(minutes);

	date_time = new char[temp_datetime.length() + 1];
	strcpy(date_time, temp_datetime.c_str());
	return 1;
}

//method to edit the event's date_time field
void event::edit_event_date_time()
{
	read_correct_date_time();
}

//method to display the booked event information
void event::display() const
{
	if (!org_name || !location || !date_time || !duration)
		return;
	cout <<"Organization Name: "<< org_name <<endl;
	cout <<"Location: "<< location <<endl;
	cout <<"Date and Time: "<< date_time <<endl;
	cout <<"Duration: "<< duration <<endl;
}

//method to cancel a event by deallocating member variables
int event :: cancel_event()
{
	if(org_name)
		delete [] org_name;
	org_name = nullptr;

	if(location)
		delete [] location;
	location = nullptr;

	if(date_time)
		delete [] date_time;
	date_time = nullptr;

	duration = 0;
	return 1;
}

//Compares two keyword_search item by term names
int event :: compare(char * org_name_tomatch)
{
	if(!org_name_tomatch)
		return 0;
	if(strcasecmp(org_name, org_name_tomatch) == 0)
		return 1;
	else
		return 0;

}

//constructor for derived class pool
pool::pool(): family_booking(""), monthly_rate(0.0)
{

}

//method to display pool booking information
void pool::display() const
{
	event::display();
	if(family_booking == "" || !monthly_rate)
		return;
	cout << "Family booking requested: " << family_booking << endl;
	cout << "Pool monthly rate: " << "$" << monthly_rate << endl;
}

//books a pool event
int pool::book_pool()
{
	event::create_event();
	cout << "Do you want to book pool for your family? yes/no - ";
	getline(cin,family_booking);
	cout <<"Please provide monthly rate to book pool: " <<"$";
	cin >> monthly_rate;
	cin.ignore(100, '\n');

	return 1;
}

//cancels a pool booking
int pool:: cancel_pool_booking()
{
	event::cancel_event();
	family_booking = "";
	monthly_rate = 0.0;
	return 1;
} 

//method to edit pool booking information
void pool::edit_pool_booking()
{
	event::edit_event_date_time();
	char response = ' ';
	cout << "Do you want to change your family booking preference? Y/N" << endl;
	cin >> response;
	cin.ignore(100, '\n');

	if(tolower(response) == 'y')
	{
		cout << "Do you want to book for your family? yes/no - ";
		getline(cin, family_booking);
	}

	cout << "Pool booking has been successfully edited. Current booking info:" << endl;
	pool::display();
}
//constructor for derived class library
library::library(): max_book_limit(0), checked_books(0), use_computer("")
{

}

library::library(const library & source): event(source)
{

}

//books a library slot
int library::book_library()
{
	event::create_event();

	cout << "Please provide maximum book limit that can be borrowed from library : " ;
	cin >> max_book_limit;
	cin.ignore(100, '\n');

	cout << "Please provide number of books you have checked from library : " ;
	cin >> checked_books;
	cin.ignore(100, '\n');

	cout << "Do you want to book computer? yes/no - ";
	getline(cin, use_computer);
	return 1;
}

//method to edit library booking
void library::edit_library_booking()
{
	event::edit_event_date_time();
	char response = ' ';
	cout << "Do you want to change your library booking preference? Y/N" << endl;
	cin >> response;
	cin.ignore(100, '\n');

	if(tolower(response) == 'y')
	{
		cout << "Please provide number of books you have checked from library : " ;
		cin >> checked_books;
		cin.ignore(100, '\n');

		cout << "Do you want to book computer? yes/no - ";
		getline(cin, use_computer);
	}

	cout << "Library booking has been successfully edited. Current booking info:" << endl;
	library::display();
}

//displays the booked library slot information
void library::display() const 
{
	event::display();
	if(!max_book_limit || !checked_books || use_computer == "")
		return;
	cout << "Maximum book limit: " << max_book_limit << endl;
	cout << "Number of books requested: " << checked_books << endl;
	cout << "Computer booking requested: " << use_computer << endl;
}

//cancels booked library slot
int library::cancel_library_booking()
{
	event::cancel_event();
	max_book_limit = 0;
	checked_books = 0;
	use_computer = "";

	return 1;
}


//constructor for derived class trip
trip::trip(): fees(0.0), food_details(nullptr), num_child(0) 
{

}

//copy constructor for derived class trip
trip::trip(const trip & source) : event(source), fees(0.0), food_details(nullptr),
	num_child(0)
{
	if(!source.food_details || !source.fees || !source.num_child)
		return;
	food_details = new char [strlen(source.food_details) + 1];
	strcpy(food_details, source.food_details);

	fees = source.fees;
	num_child = source.num_child;
}

//destructor method for trip class
trip :: ~trip()
{
	if(food_details)
		delete [] food_details;
	food_details = nullptr;

	fees = 0.0;
	num_child = 0;
}

//method to book a trip event
int trip:: book_trip() 
{
	char food_details_toadd[MAX];
	event::create_event();

	if(food_details) 
		delete [] food_details;
	cout << "Please enter the food information for the trip: ";
	cin.get(food_details_toadd, MAX, '\n');
	cin.ignore(100, '\n');
	food_details = new char[strlen(food_details_toadd) + 1];
	strcpy(food_details, food_details_toadd);

	cout << "Please enter the fees to book the trip: " << "$";
	cin >> fees;
	cin.ignore(100, '\n');

	cout << "Please enter the number of children coming to the trip: ";
	cin >> num_child;
	cin.ignore(100, '\n');
	return 1;
}

//edits a trip booking
void trip::edit_trip_booking()
{
	event::edit_event_date_time();
	char response = ' ';
	cout << "Do you want to change your trip booking preference? Y/N" << endl;
	cin >> response;
	cin.ignore(100, '\n');

	if(tolower(response) == 'y')
	{
		cout << "Please edit the fees to book the trip: " << "$";
		cin >> fees;
		cin.ignore(100, '\n');

		cout << "Please edit the number of children coming to the trip: ";
		cin >> num_child;
		cin.ignore(100, '\n');
	}
	cout << "Trip booking has been successfully edited. Current booking info:" << endl;
	trip::display();
}


//displays the booked trip information
void trip:: display() const 
{
	event::display();
	if(!food_details || !fees || !num_child)
		return;
	cout << "Food information: " << food_details << endl;
	cout << "Fees for trip: " <<"$" << fees << endl;
	cout << "Number of children comming: " << num_child <<endl;
}

//cancels booked trip event
int trip:: cancel_trip_booking()
{
	event::cancel_event();

	if(food_details)
		delete [] food_details;
	food_details = nullptr;
	fees = 0.0;
	num_child = 0;
	return 1;
}

//retrieve the organization name
char * event::get_org_name()
{
	if(!org_name)
		return nullptr;
	return org_name;
}
