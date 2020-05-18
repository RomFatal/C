#pragma once

#include <iostream>
#include <string>
#include "course.h"
#include "RCPtr.h"
using namespace std;

#ifndef _DEPARTMENT_HPP
#define _DEPARTMENT 


class Department
{
	private:
	string departmentName;
	nodeType<Course>* coursesList;
	nodeType<Student>* studentsList;

	public:
	string getDepartmentName();
	bool addCourse(RCPtr<Course>& newCourse);
	RCPtr<Student>& addStudent(const string fName, const string lName, const int ID, const int rYear, const string studAd, const string dep, const int sumOfCred = 0);
	Department(string departmentName);
	~Department();
	void signUpCourse(const int Id, const int courseId);
	bool isExist(const int Id);
	void deleteStudent(const int Id);
};

#endif