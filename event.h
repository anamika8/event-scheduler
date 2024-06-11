#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

//*******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents an Abstract Data Type for an event, and all its derived types
// that helps in planning for that event.
// This class interface is a representation of an event in OOP. 
// The base class event which will hold basic event information like – event organizer name, 
// location, event duration and date & time.
// There are three derived classes of event – pool, library and trip. All derives classes have 
// "is a" relationship with event that means all of them are event plus more.
//*******************************************************************************

//Global Constants
const int NAME = 51;
const int LOCATION = 151;
const int MAX = 251;


//There is a base class event which keeps track of individual event's name, location, duration
//and date-time.
class event
{
	public:
		event(); //constructor
		~event(); //destructor
		event(const event & source); //copy constructor
		int create_event(); //creates a new event
		int read_correct_date_time();//reads from user and validates the entered date time
		void edit_event_date_time(); //edits the event date time
		void display() const; //display event information
		int cancel_event(); // cancel a event
		int compare(char * org_name_tomatch);//compare the organization
		char * get_org_name();//retrieve oraganisation name
	protected:
		char * org_name;
		char * location;
		char * date_time;
		int duration;
};

//The pool class is derived from event. So pool is an event and more. It will
//manage the event to book a pool.
class pool: public event			
{
	public:
		pool(); //constructor
		int book_pool(); //books a pool event
		void display() const; //displays the pool booking information
		int cancel_pool_booking(); //cancels a pool booking
		void edit_pool_booking(); //edits a pool booking
	protected:
		string family_booking;
		float monthly_rate;
};

//The library class is derived from event. So library is an event and more. It will
//manage the event to book a time to use the library and its resources
class library: public event
{
	public:
		library(); //constructor
		library(const library & source);
		int book_library(); //books a library slot
		void display() const; //displays the booked library slot information
		int cancel_library_booking(); //cancels booked library slot
		void edit_library_booking(); //edits a library booking
	protected:
		int max_book_limit;
		int checked_books;
		string use_computer;
};

//The trip class is derived from event. So trip is an event and more. It will
//manage the event to book a trip, edit or cancel a booked trip
class trip: public event
{
	public:
		trip(); //constructor
		~trip(); //destructor
		trip(const trip & source); //copy constructor
		int book_trip(); //books a trip
		void display() const; //displays the booked trip information 
		int cancel_trip_booking(); //cancels booked trip
		void edit_trip_booking(); //edits a trip booking
	protected:
		float fees;
		char * food_details;
		int num_child;
};

