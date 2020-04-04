#include <iostream>
#include <vector>
#include <map>
#include <time.h>
#include <Windows.h>
#include "vertex.h"
#include "truck.h"
#include <conio.h>
using namespace std;

#define const_TruckCAPACITY 50;
#define const_RetailCAPACITY 460;

typedef unsigned int u_int;

/*
int BinarySearchID(vector<double> array , double target)
{
	int l = 0, r = array.size();
	int middle = (l + r) / 2;
	
	while (1)
	{
		if (middle == array.size() - 1 || middle == 0)
			return middle;
		if (array[middle + 1] >= target && array[middle ] <= target)
			return middle + 1;
		else if (target > array[middle])
		{
			l = middle;
		}
		else
			r = middle;
		middle = (l + r) / 2;
	}
}
*/

int LinearSearchID(vector<double> array, double target)
{
	int i = 0;
	
	for (i; i < array.size(); ++i)
	{
		if (target <= array[i])
			return i;
	}
	//return i;
}
u_int GetNextVertexID(VERTEX* current, vector<VERTEX*>& vertexes)
{
	vector<double> probabilities;
	double sum = 0;
	double weight;
	for (auto i : vertexes)
	{
		if (current == i)
			continue;
		weight = current->GetPheromone(i) + 1/current->GetDistance(i);
		sum += weight;
		probabilities.push_back(sum);
	}
	// have to test is probabilities changing
	for (int i = 0 ; i < probabilities.size() ; ++i /* : probabilities*/)
		probabilities[i] /= sum;
	double rand0to1 = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	int result = LinearSearchID(probabilities, rand0to1);
	return result >= current->GetID() ? result + 1 : result;
}

void VisitVertex(TRUCK* truck, VERTEX* vertex)
{
	if (vertex->GetType() == retailer)
		vertex->FillCapacity(truck);
	else
		truck->Load();
}

void UpdatePheromones(vector <VERTEX*>& vertexes , double vaporizeSpeed , vector<TRUCK*>& trucks , double PheromoneAdded) // PheromoneAdded - usually 1/distance ( 0 if u want to add const (1/distance))
{
	for (auto i : vertexes) // decreasing all the pheromones 
	{
		for (int j = i->GetID() + 1; j < vertexes.size(); ++j)
		{
			i->ChangePheromone(vertexes[j], (1 - vaporizeSpeed) * i->GetPheromone(vertexes[j]));
		}
	}

	for (auto currentTruck : trucks) // Doint all the trucks movement and increasing pheromones
	{
		u_int destID = GetNextVertexID(vertexes[currentTruck->GetCurrentVertexID()], vertexes);
		VisitVertex(currentTruck, vertexes[destID]);
		VERTEX * currentVertex = vertexes[currentTruck->GetCurrentVertexID()];
		VERTEX* destVertex = vertexes[destID]; 
		if(PheromoneAdded == 0)
			currentVertex->AddPheromone(destVertex , static_cast<double> (1) / currentVertex->GetDistance(destVertex) ); 
		else
			currentVertex->AddPheromone(destVertex, PheromoneAdded);
		currentTruck->Ride(destVertex);
	}
	
}

void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

int main()
{
	srand(time(NULL));

	u_int trucksAmount;
	u_int truckCapacity;
	vector<TRUCK* > trucks;

	u_int vertexAmount;
	u_int vertexCapacity;
	double x, y;
	vector<VERTEX*> vertexes;

	cout << "Enter the amount of trucks" << endl;
	cin >> trucksAmount;
	system("cls");
	cout << "Enter the capacity of trucks" << endl;
	cin >> truckCapacity;
	system("cls");
	cout << "Enter the amount of vertexes" << endl;
	cin >> vertexAmount;
	system("cls");

	cout << "Enter the x coordinate of warehouse" << endl;
	cin >> x;
	system("cls");
	cout << "Enter the y coordinate of warehouse" << endl;
	cin >> y;
	system("cls");

	VERTEX* warehouse = new VERTEX(0, vertexTYPE::warehouse, x, y);
	vertexes.push_back(warehouse);

	for (int i = 1; i < vertexAmount; ++i)
	{
		cout << "Enter the x coordinate of #" << i << " retailer" << endl;
		cin >> x;
		system("cls");
		cout << "Enter the y coordinate of #" << i << " retailer" << endl;
		cin >> y;
		system("cls");
		VERTEX* retailer = new VERTEX(i, vertexTYPE::retailer, 200 , x, y);
		vertexes.push_back(retailer);
	}

	for (int i = 0; i < trucksAmount; ++i)
	{
		TRUCK* truck = new TRUCK(i, truckCapacity, 0, vertexes[0]);
		trucks.push_back(truck);
	}

	char action;

	for (auto i : vertexes)
	{
		i->SetDistances(vertexes);
		i->SetPheromones(vertexes, 1);
	}

	while ( /*(action = _getch()) != 13*/1 )
	{
		setcur(0, 0);

		for (auto i : vertexes)
		{
			for (auto j : *i->GetPheromones())
			{
				cout << i->GetID() << " -> " << j.first->GetID() << " = " << j.second << endl;
			}
		}

		action = _getch();

		UpdatePheromones(vertexes, 0.1, trucks, 0);

		/*if (action == 32)
		{
			cout << "Press any key to continue" << endl;
			while (action = _getch());
		}*/
	}



}