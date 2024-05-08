#include "../packages/cpp-httplib/httplib.h"
#include "Lights.h"

#include <iostream>

using namespace std;

/*
1 optional arg: the server address with no spaces.
Default: 127.0.0.1:8080
*/
int main(int argc, char** argv) 
{
	Lights lights;
	string serverAddress = "127.0.0.1:8080";

	if (argc == 2)
	{
		serverAddress = argv[1];
	}

	httplib::Client cli(serverAddress);

	if (lights.getLights(&cli))
	{
		cout << lights.toJson().dump(1, '\t') << endl;

		while (!GetAsyncKeyState(VK_ESCAPE))
		{
			Lights newLights;
			if (newLights.getLights(&cli))
			{
				if (newLights != lights)
				{
					lights.findAndPrintChanges(newLights);
					
					lights.lights = newLights.lights;
				}
			}
			Sleep(1000);
		}
	}
	else
	{
		cout << "Error connecting to server." << endl;
		system("pause");
	}

	return 0;
}