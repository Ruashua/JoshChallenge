#include "Lights.h"

bool Lights::getLights(httplib::Client* cli)
{
	vector<Light> newLights;

	httplib::Result result;
	httplib::Result details;

	result = cli->Get("/lights");
	if (result.error() == httplib::Error::Success)
	{
		json data = json::parse(result.value().body, NULL, false);
		if (data.is_discarded() || !data.is_array())
		{
			return false;	//If bad JSON, return.
		}

		for (auto it : data)
		{
			if (it.is_object() && it[KEYID].is_string())
			{
				details = cli->Get("/lights/" + (string)it[KEYID]);
				if (details.error() == httplib::Error::Success)
				{
					json parsedDetails = json::parse(details.value().body, NULL, false);
					if (!parsedDetails.is_discarded() && parsedDetails[KEYNAME].is_string() && parsedDetails[KEYROOM].is_string() &&
						parsedDetails[KEYON].is_boolean() && parsedDetails[KEYBRIGHTNESS].is_number_integer())
					{
						newLights.push_back(Light(parsedDetails[KEYNAME], it[KEYID], parsedDetails[KEYROOM],
							parsedDetails[KEYON], parsedDetails[KEYBRIGHTNESS]));
					}
					else
					{
						return false;	//If bad JSON, return.
					}
				}
				else
				{
					return false;	//If error in server response, return.
				}
			}

		}
		lights = newLights;  //Only set the new lights if you get a successful server return and json parse.
	}
	else
	{
		return false;  //If error in server response, return.
	}
	return true;
}

json Lights::toJson()
{
	json jsonLights;
	jsonLights.array();

	for (auto light : lights)
	{
		jsonLights.push_back(light.toJson());
	}

	return jsonLights;
}

bool Lights::operator!=(Lights otherLights)
{
	bool lightChanged = true;
	//Detects if anything was added.
	if (lights.size() != otherLights.lights.size())
	{
		return true;
	}

	//Detects if a light has changed details compared to the incoming vector.
	//It will also detect if one is missing.
	for (auto light : lights)
	{
		lightChanged = true;
		for (auto otherLight : otherLights.lights)
		{
			if (light == otherLight)
			{
				lightChanged = false;
				break;
			}
		}
		if (lightChanged)
		{
			return true;
		}
	}
	return false;
}

void Lights::findAndPrintChanges(Lights otherLights)
{
	findAndPrintRemovedLight(otherLights);
	findAndPrintAddedLight(otherLights);
	findAndPrintUpdatedValue(otherLights);
}

void Lights::findAndPrintRemovedLight(Lights otherLights)
{
	bool lightRemoved = true;
	for (auto light : lights)
	{
		lightRemoved = true;
		for (auto otherLight : otherLights.lights)
		{
			if (light.id == otherLight.id)
			{
				lightRemoved = false;
				break;
			}
		}
		if (lightRemoved)
		{
			cout << light.name + " (" + light.id + ") has been removed" << endl;
		}
	}
}

void Lights::findAndPrintAddedLight(Lights otherLights)
{
	bool lightAdded = true;
	for (auto otherLight : otherLights.lights)
	{
		lightAdded = true;
		for (auto light : lights)
		{
			if (light.id == otherLight.id)
			{
				lightAdded = false;
				break;
			}
		}
		if (lightAdded)
		{
			cout << otherLight.toJson().dump(1, '\t') << endl;
		}
	}
}

void Lights::findAndPrintUpdatedValue(Lights otherLights)
{
	bool lightFound = false;
	for (auto light : lights)
	{
		lightFound = false;
		for (auto otherLight : otherLights.lights)
		{
			if (light.id == otherLight.id)
			{
				if (light != otherLight)
				{
					if (light.name != otherLight.name)
					{
						printSingleValue(KEYNAME, otherLight.id, otherLight.name);
					}
					if (light.room != otherLight.room)
					{
						printSingleValue(KEYROOM, otherLight.id, otherLight.room);
					}
					if (light.on != otherLight.on)
					{
						printSingleValue(KEYON, otherLight.id, otherLight.on);
					}
					if (light.brightness != otherLight.brightness)
					{
						printSingleValue(KEYBRIGHTNESS, otherLight.id, otherLight.brightness);
					}
				}
				break;
			}
		}
	}
}
