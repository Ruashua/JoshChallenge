#pragma once
#include <iostream>
#include "../packages/cpp-httplib/httplib.h"
#include "Light.h"

using namespace std;
using json = nlohmann::json;

class Lights
{
public:
	vector<Light> lights;

	Lights(){;}

	/* Gets and stores all light details from the server.*/
	bool getLights(httplib::Client* cli);
	

	bool operator!=(Lights otherLights);

	/*Converts the light object into a JSON object for easy comparison and printing.*/
	json toJson();

	/*Calls each subfunction to print all changes between this object and an incoming object.*/
	void findAndPrintChanges(Lights otherLights);
	
	/*Finds and prints all removed lights between this object and an incoming object.*/
	void findAndPrintRemovedLight(Lights otherLights);

	/*Finds and prints all added lights between this object and an incoming object.*/
	void findAndPrintAddedLight(Lights otherLights);

	/*Finds and prints all changes for every light between this object and an incoming object.
	Each change is printed seperately.*/
	void findAndPrintUpdatedValue(Lights otherLights);


	/*Template function for printing the ID and 1 passed in value.*/
	template <typename T>
	void printSingleValue(string key, string id, T value)
	{
		json object;
		object.object();
		object[KEYID] = id;
		object[key] = value;
		cout << object.dump(1, '\t') << endl;
	}


};

