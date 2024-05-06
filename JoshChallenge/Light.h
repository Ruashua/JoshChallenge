#pragma once
#include <iostream>
#include "../packages/json/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

//JSON keys for the object
const string KEYNAME = "name";
const string KEYID = "id";
const string KEYROOM = "room";
const string KEYON = "on";
const string KEYBRIGHTNESS = "brightness";

class Light
{
public:
	string name;
	string id;
	string room;
	bool on;
	int brightness;	//Represented as a percentage 0-100.

	/*Sets all of the lights values.  Converts the 0-255 brightness scale to 0-100.*/
	Light(string _name, string _id, string _room, bool _on, int _brightness);

	bool operator==(Light otherLight);
	bool operator!=(Light otherLight);

	/*Converts the light object into a JSON object for easy comparison and printing.*/
	json toJson();
};