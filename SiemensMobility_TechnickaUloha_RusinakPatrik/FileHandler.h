#pragma once
#include <fstream>
#include "Place.h"

using namespace std;

class FileHandler
{
public:
	FileHandler(string parFilePath);
	~FileHandler();
	void parser();
	void output();

private:
	ifstream loader;
	string filePath;
	string fileName;
	vector<Place*> vPlaces;
	vector<string> vOutput;
	void creator(string parPlace, string parNeighbour);
	vector<string> stringParser(string sToParse, string parDelimiter);
};

FileHandler::FileHandler(string parFilePath)
{
	this->filePath = parFilePath;
}

FileHandler::~FileHandler()
{
	this->vPlaces.clear();
	this->vOutput.clear();
}

inline void FileHandler::parser() 
{
	loader.open(filePath);

	if (!loader.is_open())
	{
		cout << filePath + " not found." << endl;
		exit(0);
	}

	cout << "\nLoading..." << endl;

	string placeA;
	string placeB;
	string firstLine;
	bool firstLaneReaded = false;

	while (!loader.eof())
	{
		if (!firstLaneReaded)
		{
			getline(loader, firstLine, '\n');

			vector<string> routes = this->stringParser(firstLine, ",");

			for (string route : routes)
			{
				vector<string> places = this->stringParser(route, "-");

				bool first = true;
				string place1;
				string place2;

				for (string place : places)
				{
					if (first)
					{
						place1 = place;
						first = false;
					}
					else
					{
						place2 = place;
					}
				}

				this->creator(place1, place2);
				this->creator(place2, place1);
			}

			firstLaneReaded = true;
		}

		getline(loader, placeA, ',');
		getline(loader, placeB, '\n');

		bool found = false;

		for (Place* temp1 : this->vPlaces) //prehladavanie do druhej urovne (musia mat spolocneho suseda), ktore podla dodanych vstupnych parametrov staci, pri hlbsom prehladavani by to bolo potrebne spravit rekurzivne
		{
			if (temp1->getName() == placeA)
			{
				for (string temp2 : temp1->getNeighbours())
				{
					if (temp2 == placeB)
					{
						this->vOutput.push_back("Yes");
						found = true;
						break;
					}
					else 
					{
						for (Place* temp3 : this->vPlaces)
						{
							if (temp3->getName() == placeB)
							{
								for (string temp4 : temp3->getNeighbours())
								{
									if (temp4 == temp2)
									{
										this->vOutput.push_back("Yes");
										found = true;
										break;
									}
								}
							}
						}
					}
				}
			}
		}

		if (!found)
		{
			this->vOutput.push_back("No");
		}
	}
	cout << "File opened succesfully" << endl;
}

inline void FileHandler::output()
{
	cout << "Creating output file..." << endl;
	string filePathParsed = filePath.substr(0, filePath.find("."));

	ofstream outputFile;
	outputFile.open(filePathParsed + ".out");
	for (string answer : this->vOutput)
	{
		outputFile << answer << endl;
	}

	outputFile.close();

	cout << "\nDone. Output file can be found here: " << endl;
}

inline void FileHandler::creator(string parPlace, string parNeighbour)
{
	int counter = 0;

	for (Place* temp : this->vPlaces)
	{
		if (temp->getName() == parPlace)
		{
			bool found = false;

			for (string tempString : temp->getNeighbours())
			{
				if (tempString == parNeighbour)
				{
					found == true;
				}
			}

			if (!found)
			{
				temp->setNeighbour(parNeighbour);
			}

			counter++;
			break;
		}
	}

	if (counter == 0)
	{
		Place* temp = new Place(parPlace);
		temp->setNeighbour(parNeighbour);
		this->vPlaces.push_back(temp);
	}
}

inline vector<string> FileHandler::stringParser(string sToParse, string parDelimiter)
{
	size_t pos = 0;
	string token;
	vector<string> parsed;

	while ((pos = sToParse.find(parDelimiter)) != string::npos)
	{
		token = sToParse.substr(0, pos);

			parsed.push_back(token);
			sToParse.erase(0, pos + parDelimiter.length());
	}

	parsed.push_back(sToParse);
	
	return parsed;
}
