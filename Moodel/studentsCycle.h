#pragma once
#include"RCPtr.h"
#include"student.h"
class StudentsCycle {
private:
	int startYear;
	int numOfStarted;
	int numOfStudents;
	int numOfFinished;
	nodeType<Student>* studentsList;
	nodeType<Student>* finishedStudents;
	void checkGraduates();
public:
	StudentsCycle(int start);
	string getStudentDepartment(const int Id);
	~StudentsCycle();
	int getStartYear();
	void addStudent(RCPtr<Student>& nStudent);
	bool isExist(const int Id);
	void deleteStudent(const int Id);
	void printCycleDetailes(ostream& out, const string& department);
};