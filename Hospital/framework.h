#pragma once
#ifndef _FRAMEWORK_HPP
#define _FRAMEWORK_HPP 1

#include <iostream>


using namespace std;

class Organization;
class User;

class Framework
{
public:
	//Methods

	void loadMainMenu();
	void saveDataToFile(ofstream& file);//save all data program to output file
	void closeApp();//free memory
	bool checkIfExist(string& id) const;//check if user existing in the system
	int checkIfMatch(string& id,string& pass) const;//check if pass match to id
	void getData(fstream& file);//get all data from file
	void signup();//new user

	//C'tors & D'tors
	Framework(fstream& file);
	~Framework();
private:

	//Data member
	Organization* organization;
};

#endif