#include "node.h"
using namespace std;

// ******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents an Abstract Data Type for a scheduler and its actions to
// help book various events like pool, library or a trip.
// Scheduler is handling all events like pool, library and trip
// It has nodes of the events which used to invoke all necessary functions to book events
// *******************************************************************************


// This person class represents an invdiidual who wants to manage event booking 
class person			
{
	public:
		person(); //constructor
		~person(); //destructor
		person(const person & source); //copy constructor
		void set_person(); //sets person info
		void display() const; //displays person info
	protected:
		char * name;
		char * address;
};

// This class scheduler is a person, who performs the necessary action to book events
// like pool booking, library booking or trip booking. This class has a pool event, 
// library event and a trip event
class scheduler: public person
{
	public:
		scheduler(); //constructor
		~scheduler(); //destructor
		scheduler(const scheduler & source); //copy constructor
		void insert_data(string event_name); //method to insert a new booking
		void remove_data(string event_name); //method to cancel a booked event
		void display(string event_name) const; //displays all the booked event information
		void removal_cll();//utility method to remove all nodes from CLL
		void insert_pool();//utility method to insert pool data
		void display_pool() const;//utility method to display pool data
		void remove_pool(char * org_name); //removes a pool event from the CLL
		void duplicate_cll(pool_node *& new_copy, pool_node * rear);//utility method to copy CLL
		void remove_all_trips();//remove all trips
		int finding_index(char *key) const; //finding index to input data in ARR
		void remove_all_library(); // remove all library details
		void insert_library();  //utility method to insert library data 
		void display_library() const; //utility method to display library data
		void remove_library(char * orgz_name);//utility method to remove library data
		void edit_trip_booking(); //function to edit a trip booking
		void copy_arr(const scheduler & new_list);//wrapper functio to copy deep copy ARR
	protected:
		pool_node * rear;
		library_node ** head;
		int table_size;
		vector<trip> trips;
		//utility recursive function to remove all pool_nodes
		void removal_cll(pool_node * & rear);
		//utility recursive function to insert pool nodes
		void insert_pool(pool_node * & rear);
		//utility recursive function to display pool nodes
		void display_pool(pool_node * rear) const;
		//utility recursive method to copy cll
		void duplicate_cll(pool_node * & new_object, pool_node * original, pool_node * & new_copy_tail);
		//utility recursive function to remove all pool_nodes matching org_name
		void remove_pool(pool_node * & rear, pool_node * prev, char * org_name);
		//insert trips to the vector
		void insert_trip();
		//display all trips
		void display_trips() const;
		//remove matching trips
		void remove_trip(char * org_name);
		//display all library bookings recursively
		void display_library(library_node * head) const;
		//remove all library booking recursively
		void remove_all_library(library_node * head);
		// delete from the Linear Linked List the matching library event recursively
		void remove_library(library_node * head, library_node * prev, library_node * new_head, char * orgz_name);
		//utility recursive method to deep copy all library nodes 
		void copy_arr(library_node * & head_dest, library_node * head_source);
};


bool again();
