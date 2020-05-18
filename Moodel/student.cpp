#include "student.h"

Student::Student(const string fName, const string lName, const int iD, const int rYear, const string studentAdd,
	const string dep, const int pointsAdd) :
	firstName(fName), lastName(lName), id(iD), address(studentAdd),
	regYear(rYear), department(dep),
	points((pointsAdd < 0 ? 0 : pointsAdd)), graduate(false) {}

Student::~Student()
{
}
void Student::addCredits(const int amount) {
	points += amount;
}
int Student::getStudentId() { return id; }
string Student::getStudentDepartment() { return department; }
int Student::getCredits() {
	return points;
}
bool Student::getGraduate() {
	return graduate;
}
void Student::setGraduate() {
	graduate = true;
}
void Student::printStudentDetails(ostream& out) {
	out << "first name:" << firstName << endl
		<< "last name:" << lastName << endl
		<< "ID:" << id << endl
		<< "Year of registration:" << regYear << endl
		<< "address:" << address << endl
		<< "department:" << department << endl
		<< "credits:" << points << endl;
}