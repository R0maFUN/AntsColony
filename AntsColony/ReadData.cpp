
//#include "vertex.h"
#include "ReadData.h"
#include <iostream>
#include <Windows.h>

vector<string> ParseString(string str) // filling the vector with words and numbers from the file
{
	vector<string> parsed;
	size_t i = 0;
	string tmp;
	while (str[i] != '\0')
	{
		if (!tmp.empty() && str[i] == ' ')
		{
			parsed.push_back(tmp);
			tmp.clear();
		}
		else if (str[i] != ' ' && str[i] != '\n')
			tmp.push_back(str[i]);
		++i;
	}
	if (!tmp.empty())
		parsed.push_back(tmp);
	return parsed;
}

int StringToInt(string str) // conversation string to integer
{
	int i = str.length() - 1;
	int result = 0;
	int exp = 0;
	while (i >= 0)
	{
		result += (str[i] - '0')* pow(10, exp);
		exp++;
		--i;
	}
	return result;
}

void ReadData(string filename, vector<VERTEX*>& vertexes, unsigned int& truckcapacity, unsigned int& trucksamount) // reading the data from file
{
	string line;
	fstream in(filename);     // Open the input file
	while (getline(in, line))  // read line from the file
	{
		vector<string> parsed = ParseString(line);    // parsed line 
		if (!parsed.empty() && parsed[0] == "NUMBER")  // getting information about the trucks
		{
			getline(in, line);
			parsed = ParseString(line);
			trucksamount = StringToInt(parsed[0]);
			truckcapacity = StringToInt(parsed[1]);
			continue;
		}
		if (!parsed.empty() && parsed[0][0] >= '0' && parsed[0][0] <= '9') // getting information about the customers
		{
			int CustNo = StringToInt(parsed[0]);
			double x = StringToInt(parsed[1]);
			double y = StringToInt(parsed[2]);

			if (CustNo == 0) // if customer is a warehouse
			{
				VERTEX* warehouse = new VERTEX(0, vertexTYPE::warehouse, x, y);
				vertexes.push_back(warehouse);
			}
			else   // if customer is a retailer
			{
				VERTEX* retailer = new VERTEX(CustNo, vertexTYPE::retailer, StringToInt(parsed[3]), x, y);
				vertexes.push_back(retailer);
			}
		}
	}
}

void setcur(int x, int y)//установка курсора на позицию  x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void ReadDataFromConsole(vector<VERTEX*>& vertexes, unsigned int& truckCapacity, unsigned int& trucksAmount , unsigned int& vertexAmount)
{

	double x, y;

	cout << "Enter the amount of trucks" << endl;
	cin >> trucksAmount;
	setcur(0, 0);
	cout << "Enter the capacity of trucks" << endl;
	cin >> truckCapacity;
	setcur(0, 0);
	cout << "Enter the amount of vertexes" << endl;
	cin >> vertexAmount;
	setcur(0, 0);

	cout << "Enter the x coordinate of warehouse" << endl;
	cin >> x;
	setcur(0, 0);
	cout << "Enter the y coordinate of warehouse" << endl;
	cin >> y;
	setcur(0, 0);

	VERTEX* warehouse = new VERTEX(0, vertexTYPE::warehouse, x, y);
	vertexes.push_back(warehouse);

	for (int i = 1; i < vertexAmount; ++i)
	{
		cout << "Enter the x coordinate of #" << i << " retailer" << endl;
		cin >> x;
		setcur(0, 0);
		cout << "Enter the y coordinate of #" << i << " retailer" << endl;
		cin >> y;
		setcur(0, 0);
		unsigned int cap;
		cout << "Enter the capacity of #" << i << " retailer" << endl;
		cin >> cap;
		setcur(0, 0);
		VERTEX* retailer = new VERTEX(i, vertexTYPE::retailer, cap, x, y);
		vertexes.push_back(retailer);
	}
}