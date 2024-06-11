#include "event.h"
#include <vector>
using namespace std;

// ******************************************************************************
// Anamika Nayak , CS202 , Summer 2021
// This file represents the classes for managing and maintaining a booked event
// and they are implemented using different data structures and data types like
// circular linked list, linear linked list and vector.
// *******************************************************************************

// A pool_node is a pool plus the pointer to manage the next node of the 
// circular linked list
class pool_node: public pool
{
	public:
		pool_node(); //construtor
		pool_node *& go_next(); //traverse to the next node
		void set_next(pool_node * next_pool); //create a new node
		void delete_all();//method to delete all pool_node information
		pool_node(const pool & to_copy);//copy constructor
	protected:
		pool_node * next;
		void delete_all(pool_node * & rear); 
};

// A library_node is a library plus the pointer to manage the next node of the array of
// linear linked list
class library_node: public library
{
	public:
		library_node(); //constructor
		library_node *& go_next(); //traverse to the next node
		void set_next(library_node * next_pool); //assigns the next node
		library_node(const library & to_copy);//copy constructor
	protected:
		library_node * next;
};
