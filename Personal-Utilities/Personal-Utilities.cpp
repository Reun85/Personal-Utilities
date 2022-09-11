// Personal-Utilities.cpp : Defines the entry point for the application.
//

#include "Utils.h"
#include <iostream>
#include "JSON.cpp"
using namespace std;

int main()
{
	std::string hello = "C:\\Users\\i7\\source\\repos\\Reun85\\Personal-Utilities\\Personal-Utilities\\JSONtest.json";
	Reun::Utils::JSON js(hello);


	return 0;
}
