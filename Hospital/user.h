#pragma once

#ifndef _USER_HPP
#define _USER_HPP 1

#include <iostream>
#include <string>
#include "organization.h"
using namespace std;

typedef enum { Therapists, Patients, Receptionist} userType;

class Appointment;

class User
{
public:
	//Methods
	string getId()const;
	const int getNumAppointment()const;
	bool setAge(const int value);
	void setFirst(const string value);
	void setLast(const string value);
	void setId(const string value);
	void setPass(const string value);
	void setNotes(const string value);
	void setMode();
	const userType wichType()const;//return type of user

	Appointment* requestAppointment(User*& user);//request to make an appointment
	void reviewAppointment();//receptionist review appointment
	bool deleteAppointment(Appointment* appointment);
	void deleteUserAppointment();
	bool createAppointment(Appointment* appointment);//add to my appoinment
	int checkIfMatch(string& pass)const;//check if pass match to id
	void printUser();
	void printMyPatients();
	void printMyAppointments();
	void saveData(ofstream& file);
	void closeApp();//free memory

	//Friend Methods
	friend void Organization::deleteUser(string& id);
	friend bool Organization::deleteAppointment(User*&);
	friend int Organization::checkIfMatch(string& id, string& pass)const;
	friend void Organization::deleteFromReceptionist(Appointment* appointment);


	//C'tors & D'tors
	User(userType type, int age, string first, string last, string id, string pass, string notes);
	const User& operator=(const User& other);
	User(const User& other);

	User();
	~User();
private:
	//Methods
	Appointment* getMyAppointment();
	

	//Data member
	userType type;
	int age;
	string first;
	string last;
	string id;
	string pass;
	string notes;
	Appointment** appointments;
	int sizeAppointment;
	int numAppointment;
};


#endif
