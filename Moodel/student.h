#pragma once

#include <iostream>
#include <string>
#include "RCObject.h"
#include "RCPtr.h"

using namespace std;

#ifndef _STUDENT_HPP
#define _STUDENT_HPP 1
class Student: public RCObject
{
private:
	string firstName;
	string lastName;
	int id;
	string address;
	int regYear;
	string department;
	int points;
	bool graduate;
public:
	Student(const string fName, const string lName, const int iD, const int rYear, const string studentAdd, const string depdepartment, const int pointsAdd=0);
	~Student();
	void addCredits(const int amount);
	int getStudentId();
	string getStudentDepartment();
	int getCredits();
	bool getGraduate();
	void setGraduate();
	void printStudentDetails(ostream& out);
};


#endif