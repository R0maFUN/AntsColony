#include "truck.h"
#include "vertex.h"


TRUCK::TRUCK(u_int _id, u_int _capacity, u_int _location, VERTEX* _currentVertex)
{
	this->capacity = _capacity;
	this->location = _location;
	this->id = _id;
	this->currentVertex = _currentVertex;
	this->filledCapacity = _capacity;
}

void TRUCK::Unload(VERTEX* target) // if arrived to the retail
{
	target->FillCapacity(this);
}

void TRUCK::Ride(VERTEX* destination) // changing the current location
{
	this->location = destination->GetID();
}