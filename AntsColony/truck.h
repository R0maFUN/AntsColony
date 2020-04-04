#pragma once
//#include "vertex.h"
#define const_TruckCAPACITY 50;
#define const_RetailCAPACITY 460;

typedef unsigned int u_int;

class VERTEX;

class TRUCK
{
private:
	u_int id;
	u_int capacity;
	u_int filledCapacity;
	u_int location; // id of current vertex
	VERTEX* currentVertex;
public:

	TRUCK()
	{
		this->capacity = const_TruckCAPACITY;
		this->filledCapacity = const_TruckCAPACITY;
		this->location = 0;
	}

	TRUCK(u_int _id, u_int _capacity, u_int _location, VERTEX* _currentVertex);
	

	void Load() // if arrived to the warehouse
	{
		this->filledCapacity = this->capacity;
	}

	void Unload(VERTEX* target); // if arrived to the retail
	
	u_int GetFilledCapacity() // returns current filled capacity
	{
		return this->filledCapacity;
	}

	void ChangeFilledCapacity(int amount) // filling or ridding capacity
	{
		this->filledCapacity += amount;
	}

	void Ride(VERTEX* destination);

	u_int GetCurrentVertexID()
	{
		return this->location;
	}

};