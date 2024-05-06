#include "Light.h"


Light::Light(string _name, string _id, string _room, bool _on, int _brightness)
{
	name = _name;
	id = _id;
	room = _room;
	on = _on;
	brightness = 100 * _brightness / 255;
	if (brightness < 0)
	{
		brightness = 0;
	}
	if (brightness > 100)
	{
		brightness = 100;
	}
}

json Light::toJson()
{
	json jsonLight;
	jsonLight.object();
	jsonLight[KEYNAME] = name;
	jsonLight[KEYID] = id;
	jsonLight[KEYROOM] = room;
	jsonLight[KEYON] = on;
	jsonLight[KEYBRIGHTNESS] = brightness;

	return jsonLight;
}

bool Light::operator==(Light otherLight)
{
	if (toJson() == otherLight.toJson())
	{
		return true;
	}
	return false;
}

bool Light::operator!=(Light otherLight)
{
	if (toJson() != otherLight.toJson())
	{
		return true;
	}
	return false;
}