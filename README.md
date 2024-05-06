# Josh.ai | C++ Coding Challenge Response
This is a Windows application and must be executed and compiled in Windows.
A precompiled standalone exe is in the 

## How to compile
Extract contents and open the .sln in Microsoft Visual Studio 2022.  Build using Visual Studio.

## Incoming parameters
Only one parameter is accepted, a server address without spaces.
If there is more or less than one parameter it will go with the default value.
Default: 127.0.0.1:8080
Ex: JoshChallenge.exe 192.168.1.20:8080

## Ending the program
Hitting the esc key will end the program.

# Design choices
## Error handling
If the program cannot initially connect to the server or has errors parsing the JSON, it will end.
After that, any errors in connection will be ignored.
I decided to not print errors, except the initial connecting/parsing, as it was not a requirement 
to print them.  Ideally, errors would be logged.

## Efficiency
Efficiency is a vague thing to handle because it can be measured in many conflicting ways.
You have space, memory, and processor efficiency.  Optimizing one may lead to comprimising another.
An efficiency choice I made was creating a seperate function for detecting if there is a change in the lights
and finding/printing the specific changes.  Finding/printing a specific change could be used as the function that
detects changes, however it is slower and should be triggered much less often than detecting any change.

I polled the server every second because lights shouldn't change in a home very often.  The more you 
poll, the more CPU cycles are needlessly wasted.  You also need to poll often enough for a snappy user experience.