 #pragma once

#ifndef _APPOINMENT_HPP
#define _APPOINMENT_HPP 1

#include <iostream>
#include <string>
#include <ctime>

#include "organization.h"
#include "user.h"

class User;

using namespace std;

typedef enum {Pending, Approved, Canceled} Status;

class User;

class Appointment
{
public:
	//Methods
	int getStatus()const;
	string getTherapistId()const;
	string getPatientId()const;
	void printPatients();
	void printAppointment();
	int printAppointment(int& index);//print with index

	//Frindes
	friend bool Organization::addAppointment(Appointment*&);
	friend bool Organization::deleteAppointment(User*&);
	friend void User::reviewAppointment();
	friend void User::deleteUserAppointment();
	friend bool User::deleteAppointment(Appointment* appointment);
	friend void User::closeApp();
	friend void User::saveData(ofstream& file);

	//C'tors & D'tors
	Appointment(User* therapists, User* patients, tm* time, string notes, Status status);
	~Appointment();
private:
	//Methods
	void addAppointmentToPatient();//add appoinment to one user without add to Participants
	void addAppointmentToTherapist();//add appoinment to one user without add to Participants
	void deleteAppointmentFromParticipants();
	void deleteAppointment();
	void saveData(ofstream& file);
	void closeApp();//free memory
	//Data member
	User& therapist;
	User& patient;
	//date& time
	tm* time;
	string notes;
	Status status;
};

#endif
