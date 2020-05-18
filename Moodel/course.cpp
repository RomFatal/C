#include "course.h"



Course::Course(const int courseNumber)
	:courseNumber(courseNumber), studentList(0), pointNum(0){}


Course::~Course()
{
	nodeType<Student>* toDelete;
	while (studentList != 0) {
		toDelete = studentList;
		studentList = studentList->next;
		delete studentList;
	}
}

int Course::getCourseId() {
	return courseNumber;
}
void Course::endOfCourse() {
	nodeType<Student>*curNode, *nextNode;
	curNode = studentList;
	while (curNode) {
		curNode->Val->addCredits(pointNum);
		nextNode = curNode->next;
		delete curNode;
		curNode = nextNode;
	}
	studentList = 0;
}
void Course::addStudent(RCPtr<Student>& NStudent) {
	nodeType<Student>* newNode = new nodeType<Student>(NStudent, studentList);
	if (newNode != 0)//in case of successful allocation
		studentList = newNode;
	else
		throw exception_ptr();
}
void Course::updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName) {
	pointNum = numOfCred;
	this->courseName = courseName;
	department = depName;
}
string Course::getCourseDepartment() {
	return department;
}
void Course::graduateStudent(int Id, bool graduate) {
	if (studentList == 0)
		return;
	nodeType<Student>* prev, *cur;
	if (Id == studentList->Val->getStudentId()) {
		cur = studentList;
		studentList = studentList->next;
	}
	else {
		prev = studentList;
		cur = prev->next;
		while (cur != 0) {
			if (cur->Val->getStudentId() == Id) {
				break;
			}
			prev = cur;
			cur = cur->next;
		}
		if (cur == 0)
			return;
	}
	if (graduate == true) {
		cur->Val->addCredits(pointNum);
	}
	delete cur;

}
void Course::printCourseDetails(ostream& out) {
	out << "course name:" << courseName << endl
		<< "course department" << department << endl
		<< "course ID:" << courseNumber << endl
		<< "number of credits:" << pointNum << endl
		<< "students:" << endl;
	nodeType<Student>* cur = studentList;
	if (cur == 0) {
		out << "There are no students enrolled in this course" << endl;
	}
	else {
		while (cur != 0) {
			cur->Val->printStudentDetails(out);
			cur = cur->next;
		}
	}
}
