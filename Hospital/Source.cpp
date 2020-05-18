//Rom Fatal
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "framework.h"

fstream file("data.txt");
using namespace std;

int main()
{
	Framework Hospital(file);
	Hospital.loadMainMenu();


	ofstream file("data.txt", std::ios::out | std::ios::trunc);
	file << "hello";

	Hospital.saveDataToFile(file);
	file.close();
	return 0;
}