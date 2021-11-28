#pragma once
#include <string>
#include <vector>

using namespace std;

class Place
{
public:
	Place(string parName);
	~Place();
	bool isNeighbour(string parPlace);
	void setNeighbour(string parPlace);
	vector<string> getNeighbours();
	string getName();
private:
	string name;
	vector<string> vNeighbours;
};

Place::Place(string parName)
{
	this->name = parName;
}

Place::~Place()
{
	this->vNeighbours.clear();
}

inline bool Place::isNeighbour(string parPlace)
{
	for (string place : vNeighbours)
	{
		return place == parPlace;
	}
}

inline void Place::setNeighbour(string parPlace)
{
	this->vNeighbours.push_back(parPlace);
}

inline vector<string> Place::getNeighbours()
{
	return vNeighbours;
}

inline string Place::getName()
{
	return this->name;
}
