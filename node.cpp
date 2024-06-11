#include "node.h"

//*******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents the implementation of all methods belonging to the header
// file - node.h for the classes pool_node, library_node and trip_event.
// It implements the functions outlined in the event.h file that
// helps create, edit, display and cancel the events for a particular event type.
//*******************************************************************************

//pool_node constructor
pool_node::pool_node(): next(nullptr)
{
}

//sets the next pool_node value
void pool_node::set_next(pool_node * next_pool)
{

	this -> next = next_pool;
}

//method to go to the next pool_node
pool_node *& pool_node::go_next()
{
	return this -> next;
}

//copy constructor of pool node
pool_node :: pool_node(const pool & to_copy): pool(to_copy)
{

}  
//library_node constructor
library_node::library_node(): next(nullptr)
{

}

//traverse to the next node
library_node *& library_node::go_next()
{
	return this -> next;
}


//sets the next library_node value
void library_node::set_next(library_node * next_library) //assigns the next node
{
	this -> next = next_library;
}

//copy constructor of library node
library_node :: library_node(const library & to_copy): library(to_copy)
{

}  
