#include "scheduler.h" 
//*******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents the implementation of all methods belonging to the header
// file - scheduler.h for the classes person and scheduler.
// Here scheduler is a person and helps schedule various events like pool booking,
// library slot booking or trip booking.
// The person class implementation functions help set the person information by
// reading from user information.
// It implements the functions outlined in the scheduler class that
// helps book, edit, display and cancel the events of a particular event type.
//*******************************************************************************

//constructor for person class
person::person(): name(nullptr), address(nullptr)
{
}

//copy constructor of person class
person::person(const person & source): name(nullptr), address(nullptr)
{
	if(!source.name || !source.address)
		return;
	name = new char [strlen(source.name) + 1];
	strcpy(name, source.name);

	address = new char [strlen(source.address) + 1];
	strcpy(address, source.address);
}

//destructor of person class
person::~person()
{
	if(name)
		delete [] name;
	name = nullptr;

	if(address)
		delete [] address;
	address = nullptr;
}

//reads from the user and sets the person information
void person::set_person()
{
	char new_name[NAME];
	char new_address[LOCATION];
	if(name) 
		delete [] name;
	cout << "Please enter the name of the person to book the event: ";
	cin.get(new_name, NAME, '\n');
	cin.ignore(100, '\n');
	name = new char[strlen(new_name) + 1];
	strcpy(name, new_name);

	if(address) 
		delete [] address;
	cout << "Please enter the person address: ";
	cin.get(new_address, LOCATION, '\n');
	cin.ignore(100, '\n');
	address = new char[strlen(new_address) + 1];
	strcpy(address, new_address);
}

//displays person info
void person::display() const
{
	if (!name || !address)
		return;
	cout <<"Person Name: "<< name <<endl;
	cout <<"Address: "<< address <<endl;
	cout << endl;
}

//scheduler class constructor
scheduler::scheduler(): rear(nullptr), head(nullptr), table_size(15)
{
	head = new library_node * [table_size];
	for (int i = 0; i < table_size; ++i)
		head[i] = NULL;
}


//public member function to call the wrapper functions
//of the various events like - pool booking, library booking or trip booking
scheduler::~scheduler()
{
	removal_cll();
	remove_all_trips();
	remove_all_library();
}

/***pool booking information ***/

//wrapper function to call recursive function to remove all nodes in a CLL
void scheduler::removal_cll()
{
	if(!rear)
		return;
	removal_cll(rear -> go_next());
}

//recursive function to remove all pool bookings
void scheduler::removal_cll(pool_node * & rear)
{
	if(!rear)
		return;
	if(rear == this -> rear)
	{
		delete this -> rear;
		this -> rear = NULL;
		return;
	}
	pool_node * temp = rear -> go_next();
	delete rear;
	rear = temp;
	removal_cll(rear);
}


//public member function to call the wrapper functions
//of the various events like - pool booking, library booking or trip booking
void scheduler::insert_data(string event_name)
{
	if(event_name == "pool")
	{
		insert_pool();
	}
	else if(event_name == "trip")
	{
		insert_trip();
	} 
	else
	{
		insert_library();
	}
}

//wrapper function to call recursive pool booking method
void scheduler::insert_pool()
{
	return insert_pool(rear);
}

//method to insert a new pool booking in the circular linked list
void scheduler::insert_pool(pool_node * & rear)
{
	if(!rear)
	{
		rear = new pool_node;
		rear -> book_pool();
		rear -> set_next(rear);
		return;
	}

	pool_node * hold = rear -> go_next();
	pool_node * temp =  new pool_node;
	temp -> book_pool();
	rear -> set_next(temp);
	rear = temp;
	rear -> set_next(hold);
	return;
}

//public member function to call the wrapper functions
//of the various events like - pool booking, library booking or trip booking
void scheduler::display(string event_name) const
{

	if(event_name == "pool")
	{
		display_pool();
	}
	else if(event_name == "trip")
	{
		display_trips();
	} 
	else
	{
		display_library();
	}
}

//wrapper function to display pool details
void scheduler::display_pool() const
{
	if (!rear)
	{	
		cout << "Sorry, there are no pool bookings available for: \n";
		person::display();
		return;
	}

	cout << "\n Listing down all pool bookings made by : \n";	
	person::display();
	return display_pool(rear -> go_next());
}

//recursive function to display pool details from the Circular Linked List
void scheduler::display_pool(pool_node * rear) const
{
	if(rear == this -> rear)
	{
		rear -> display();
		return;
	}
	rear -> display();//output the data
	return display_pool(rear -> go_next()); //display the next.
}


//scheduler class copy constructor
scheduler::scheduler(const scheduler & source): person(source), rear(nullptr), head(nullptr)
{
	duplicate_cll(rear, source.rear);  
	copy_arr(source);
}

//method to deep copy pool_node event
void scheduler::duplicate_cll(pool_node * & new_copy, pool_node * rear)
{
	if(!rear)
	{
		new_copy = NULL;
		return;
	}

	new_copy = new pool_node(*rear);
	new_copy -> go_next() = new_copy;
	pool_node * hold = rear;

	return duplicate_cll(new_copy -> go_next(), rear -> go_next(), hold);
}

//recursive function of pool_node deep copy
void scheduler::duplicate_cll(pool_node * & new_copy, pool_node * original, pool_node * & new_copy_tail)
{
	if(original == new_copy_tail)
		return;

	pool_node * temp = new_copy;
	new_copy = new pool_node(*rear);
	new_copy -> go_next() = temp;

	return duplicate_cll(new_copy -> go_next(), original -> go_next(), new_copy_tail);
} 

//method to deep copy library data(ARR)
void scheduler::copy_arr(const scheduler & new_list)
{

	head = new library_node * [new_list.table_size];
	table_size = new_list.table_size;

	for(int i = 0; i < table_size; i++)
	{

		copy_arr(head[i],new_list.head[i]);
	}
	return;
}

//recursive dunction of library node deep copy 
void scheduler::copy_arr(library_node * & head_dest, library_node * head_source)
{
	if(!head_source)
	{
		head_dest = NULL;
		return;
	}

	// copy data
	head_dest = new library_node(*head_source);
	head_dest -> go_next() = NULL;

	return copy_arr(head_dest -> go_next(), head_source -> go_next());
}

//method to cancel a booked event
void scheduler::remove_data(string event_name)
{
	char orgz_name[NAME];
	cout << "\n Please enter the organization name whose booking you wish to cancel: ";
	cin.get(orgz_name, NAME, '\n');
	cin.ignore(100, '\n');
	if(event_name == "pool")
	{
		remove_pool(orgz_name);
	} 
	else if(event_name == "library")
	{
		remove_library(orgz_name);
	}
}

//removes pool event by the organization name
void scheduler::remove_pool(char * orgz_name)
{
	if(!rear)
		return;
	return remove_pool(rear -> go_next(), rear, orgz_name);
}

//recursive function call to remove pool event
void scheduler::remove_pool(pool_node * & rear, pool_node * prev, char * orgz_name)
{
	if(rear -> go_next() == rear) // when this is the only node
	{
		if(rear -> compare(orgz_name) == 1)
		{
			delete rear;
			this -> rear = NULL;
			return;
		}
		return;
	}
	if(rear == this -> rear)
	{
		if(rear -> compare(orgz_name) == 1)
		{
			pool_node * hold = rear -> go_next();
			delete rear;
			prev -> set_next(hold);
			this -> rear = prev;
			return;
		}
		return;
	}

	if(rear -> compare(orgz_name) == 1)
	{
		pool_node * hold = rear -> go_next();
		delete rear;
		prev -> set_next(hold);
		rear = hold;
		if(!rear)
			return remove_pool(rear, prev, orgz_name);
	}

	return remove_pool(rear -> go_next(), prev -> go_next(), orgz_name);
}

/***trip booking information ****/

//insert trips to the vector
void scheduler::insert_trip()
{
	trip new_trip;
	cout << "\n Starting a new trip booking" << endl;
	new_trip.book_trip();
	trips.push_back(new_trip);
}

//display trips using vector functions
void scheduler::display_trips() const
{
	if(trips.empty())
	{	
		cout << "No trip booking has been done yet by: " << endl;
		person::display();
		return;
	}

	cout << "\n Listing down all trip bookings made by : \n";	
	person::display();
	for (auto it = trips.begin(); it != trips.end(); ++it) 
	{
		(*it).display();
	}
}

//remove all trips using vector method
void scheduler::remove_all_trips()
{
	if(trips.empty())
		cout << "No trip booking has been done yet" << endl;

	trips.clear();
}
//edit a trip using vector
void scheduler::edit_trip_booking()
{
	char org_name[NAME];
	cout << "\n Please enter the organization name whose booking you wish to edit: ";
	cin.get(org_name, NAME, '\n');
	cin.ignore(100, '\n');
	if(trips.empty())
		cout << "No trip booking has been done yet" << endl;


	for (vector<trip>::iterator it = trips.begin(); it != trips.end(); ++it) 
	{
		if((*it).compare(org_name) == 1)
		{
			(*it).edit_trip_booking();
		}
	}
}


/***library booking information***/

//Helper function to create and return the hash key
int scheduler::finding_index(char *key) const
{

	int index_value = 0;
	int value = 0;

	int length = strlen(key);
	for (int i = 0 ; i< length-1 ; ++i)
	{

		value += tolower(key[i])* tolower(key[i+1])*1011;
	}

	index_value = value % table_size; 
	return index_value;
}

//remove all library bookings
void scheduler::remove_all_library()
{
	if(!head)
		return;

	for(int i = 0; i < table_size; ++i)
	{ // For every bucket
		if(this -> head[i])
		{
			library_node * current = head[i];
			if(current)
				remove_all_library(current);
		}
	}
	if(head)
	{
		delete [] head;
		head = NULL;
	}
}

// delete all library event recursively
void scheduler::remove_all_library(library_node * head)
{
	if(!head)
		return;
	remove_all_library(head -> go_next());
	delete head;
	head = NULL;
	return;
}

//makes a library booking
void scheduler::insert_library()
{
	library_node * temp = new library_node;
	temp -> book_library();
	char * key_value = temp -> get_org_name();
	int index = finding_index(key_value);
	temp -> go_next() = head[index];
	head[index] = temp;
}

//display all library bookings
void scheduler::display_library() const
{
	if(!head)
	{	
		cout << "No library booking has been done yet by: " << endl;
		person::display();
		return;
	}
	cout << "\n Listing down all library bookings made by : \n";	
	person::display();
	for(int index = 0; index < table_size; ++index)
	{ 
		library_node * current = head[index];
		if(current)
		{
			cout <<"List #" << index <<":  "<< endl;
			display_library(current);
		}
	}
	return;
}

//recursive call to display library bookings
void scheduler::display_library(library_node * new_head) const
{
	if(!new_head)
		return;
	new_head -> display();
	display_library(new_head -> go_next());
}


//method to cancel matching library booking
void scheduler::remove_library(char * orgz_name)
{
	int index  = finding_index(orgz_name);
	library_node * current = head[index]; 
	library_node * previous = NULL;
	while (current && current -> compare(orgz_name)!= 1)
	{
		previous = current;
		current = current -> go_next();
	}
	if(current != NULL)
	{
		if(current == head[index])
			head[index] = current -> go_next();
		else   
			previous -> go_next() = current -> go_next();

		delete current;
		current = NULL;
		return;
	}
	else
		return;
}

