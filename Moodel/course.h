#pragma once

#include <iostream>
#include <string>
#include "RCObject.h"
#include "RCPtr.h"
#include "student.h"
using namespace std;

#ifndef _COURSE_HPP
#define _COURSE_HPP 1

class Student;
class Course: public RCObject
{
	
private:

	int courseNumber;
	int pointNum;
	string courseName;
	string department;
	nodeType<Student>* studentList;
	public:
	string getCourseDepartment();
	int getCourseId();
	void updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName);
	void addStudent(RCPtr<Student>& NStudent);//try&catch
	void endOfCourse();
	void graduateStudent(int Id, bool graduate);
	void printCourseDetails(ostream& out);
	Course(const int courseNumber=0);

	~Course();
};

#endif