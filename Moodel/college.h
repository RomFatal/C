#pragma once
#include <iostream>
#include <string>
#include "student.h"
#include "course.h"
#include "department.h"
#include"studentsCycle.h"
#include "RCPtr.h";
#include <vector>

using namespace std;

class College
{
		string collegeName;
		nodeType<Course>* coursesList;
		nodeType<Course>* getCourseById(const int courseId);
		vector<Department> departmentsList;
		vector<StudentsCycle> cycles;
		string findCourseDepartment(const int& courseId);
public:
	void addDepartment(string depName);
	void addCourse(const int courseId);
	void signUpCourse(const int id, const int courseId);
	void completionCourse(const int courseId);
	void graduateStudent(const int Id, const int courseId);
	void addStudent(const string fName, const string lName, const int ID, const int rYear, const string studAd, const string dep, const int sumOfCred=0);
	void removeStudent(const int Id, const int courseId);
	void deleteStudent(const int Id, const int cycle);
	bool updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName);
	void printDepartmentCycleDetailses(ostream& out, const string& department, int cycle);
	void printCourseDetails(ostream& out, const int);
	void updateCollegeName(const string& name);
	College(const string name="");
	~College();
};

