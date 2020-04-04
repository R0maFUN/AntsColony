#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include "truck.h"
using namespace std;

#define const_TruckCAPACITY 50;
#define const_RetailCAPACITY 460;

typedef unsigned int u_int;

class TRUCK;

enum vertexTYPE {
	warehouse,
	retailer
};

class VERTEX
{
private:
	u_int id;
	
	double x, y;
	vertexTYPE type;
	u_int capacity;
	u_int filledCapacity;
	unordered_map<VERTEX*, double>* pheromones = new unordered_map<VERTEX*, double>; // pheromones on the way from this vertex to the next ones
	unordered_map<VERTEX*, double>* distances = new unordered_map<VERTEX*, double>; // distances on the way from this vertex to the next ones
public:
	VERTEX()
	{

	}

	VERTEX(u_int id, vertexTYPE type, double x, double y);

	VERTEX(u_int id, vertexTYPE type, u_int capacity, double x, double y);


	void FillCapacity(TRUCK* truck);


	void SetPheromones(vector<VERTEX*>& vertexes, double pheromoneAmount)
	{
		for (int i = this->id + 1; i < vertexes.size(); ++i)
			this->pheromones->insert(make_pair(vertexes[i], pheromoneAmount));
	}

	double CalculateDistance(VERTEX* to)
	{
		return sqrt(pow(this->x - to->x, 2) + pow(this->y - to->y, 2));
	}

	void SetDistances(vector<VERTEX*>& vertexes)
	{
		for (int i = this->id + 1; i < vertexes.size(); ++i)
			this->distances->insert(make_pair(vertexes[i], this->CalculateDistance(vertexes[i])));
	}

	u_int GetID()
	{
		return this->id;
	}

	vertexTYPE GetType()
	{
		return this->type;
	}

	double GetPheromone(VERTEX* destination)
	{
		if (this->id < destination->GetID())
			return (*this->pheromones)[destination];
		else
			return (*destination->pheromones)[this];
	}

	unordered_map<VERTEX*, double>* GetPheromones()
	{
		return pheromones;
	}

	double GetDistance(VERTEX* destination)
	{
		if (this->id < destination->GetID())
			return (*this->distances)[destination];
		else
			return (*destination->distances)[this];
	}

	void AddPheromone(VERTEX* destination, double amount)
	{
		if (this->id < destination->id)
			(*this->pheromones)[destination] += amount;
		else
			(*destination->pheromones)[this] += amount;
	}

	void ChangePheromone(VERTEX* destination, double newValue)
	{
		if (this->id < destination->id)
			(*this->pheromones)[destination] = newValue;
		else
			(*destination->pheromones)[this] = newValue;
	}

};





/*
class VERTEX
{
private:
	u_int id;
	double x, y;
	vertexTYPE type;
	u_int capacity;
	u_int filledCapacity;
	map<VERTEX*, double>* pheromones; // pheromones on the way from this vertex to the next ones
	map<VERTEX*, double>* distances; // distances on the way from this vertex to the next ones
public:
	VERTEX()
	{

	}

	VERTEX(u_int id, vertexTYPE type, double x, double y)
	{
		this->id = id;
		this->type = type;
		this->x = x;
		this->y = y;
		if (type != warehouse)
		{
			this->capacity = const_RetailCAPACITY;
			this->filledCapacity = 0;
		}
	}

	VERTEX(u_int id, vertexTYPE type, u_int capacity, double x, double y)
	{
		this->id = id;
		this->type = type;
		this->x = x;
		this->y = y;
		this->capacity = capacity;
		this->filledCapacity = 0;
	}

	void FillCapacity(TRUCK* truck)
	{
		if (this->filledCapacity == this->capacity)
			return;
		else if (this->filledCapacity + truck->GetFilledCapacity() > this->capacity)
		{
			truck->ChangeFilledCapacity(this->filledCapacity - this->capacity);
			this->filledCapacity = this->capacity;
		}
		else
		{
			this->filledCapacity += truck->GetFilledCapacity();
			truck->ChangeFilledCapacity(-1 * truck->GetFilledCapacity());
		}
	}

	void SetPheromones(vector<VERTEX*>& vertexes, double pheromoneAmount)
	{
		for (int i = this->id + 1; i < vertexes.size(); ++i)
			this->pheromones->insert(make_pair(vertexes[i], pheromoneAmount));
	}

	double CalculateDistance(VERTEX* to)
	{
		return sqrt(pow(this->x - to->x, 2) + pow(this->y - to->y, 2));
	}

	void SetDistances(vector<VERTEX*>& vertexes)
	{
		for (int i = this->id + 1; i < vertexes.size(); ++i)
			this->distances->insert(make_pair(vertexes[i], this->CalculateDistance(vertexes[i])));
	}

	u_int GetID()
	{
		return this->id;
	}

	vertexTYPE GetType()
	{
		return this->type;
	}

	double GetPheromone(VERTEX* destination)
	{
		if (this->id < destination->GetID())
			return (*this->pheromones)[destination];
		else
			return (*destination->pheromones)[this];
	}

	map<VERTEX*, double>* GetPheromones()
	{
		return pheromones;
	}

	double GetDistance(VERTEX* destination)
	{
		if (this->id < destination->GetID())
			return (*this->distances)[destination];
		else
			return (*destination->distances)[this];
	}

	void AddPheromone(VERTEX* destination, double amount)
	{
		if (this->id < destination->id)
			(*this->pheromones)[destination] += amount;
		else
			(*destination->pheromones)[this] += amount;
	}

	void ChangePheromone(VERTEX* destination, double newValue)
	{
		if (this->id < destination->id)
			(*this->pheromones)[destination] = newValue;
		else
			(*destination->pheromones)[this] = newValue;
	}

};
*/