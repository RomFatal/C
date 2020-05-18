#pragma once

#ifndef _ORGANIZATION_HPP
#define _ORGANIZATION_HPP 1
#include "framework.h"


using namespace std;

class Appointment;

class User;

class Organization
{
public:
	//Methods
	bool checkIfExist(string& id)const;//check if user existing in the system
	int checkIfMatch(string& id, string& pass)const;//check if pass match to id

	void addUser(User*& value);//add to organization
	bool addAppointment(Appointment*& newAppointment);//add to organization
	void addToReceptionist(Appointment*& appointment);//add to Receptionist

	bool deleteAppointment(User*& user);//delete from organization
	void deleteUser(string& id);//delete from organization
	void deleteFromReceptionist(Appointment* appointment);

	void printTherapists()const;
	void printPatients()const;
	void saveData(ofstream& file)const;
	void closeApp();//free memory

	//C'tors & D'tors
	Organization();
	~Organization();
	//friend class Framework;
	friend void Framework::getData(fstream&);
	friend void Framework::loadMainMenu();
private:
	//Methods

	User* chooseTherapists();
	User* searchUser(string &id)const;
	User* searchTherapists(string &id)const;
	User* searchPatients(string &id)const;
	User* searchReceptionists(string &id)const;
	User* getUserByIndex(int index)const;
	//Data member
	User** therapists;
	User** patients;
	User** receptionists;
	Appointment** appointment;
	int sizeTherapists;
	int sizePatients;
	int sizeReceptionist;
	int sizeAppointment;
	int numTherapists;
	int numPatients;
	int numReceptionists;
	int numAppointments;
};

#endif