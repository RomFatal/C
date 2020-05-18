#include <fstream>
#include "user.h"
#include "appointment.h"

const int dsize = 10;//defult size of arr

//Methods

bool  User::setAge(const int value)
{
	if (age > 0 && age < 120)
	{
		age = value;
		return 1;
	}
	else 0;
}

void  User::setFirst(const string value)
{
	first = value;
}

void  User::setLast(const string value)
{
	last = value;
}

void  User::setId(const string value)
{
	id = value;
}

void  User::setPass(const string value)
{
	pass = value;
}

void  User::setNotes(const string value)
{
	notes = value;
}

void User::setMode()
{
	int choice,age;
	string newvalue;
	cout << "Which data you want to set? (number)" << endl << "1.First name" << " 2.Last name" << " 3.Id" << " 4.Password" << " 5.Age"<<" 6.Notes"<<endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		cout << "Enter New First name" << endl;
		cin >> newvalue;
		setFirst(newvalue);
		break;
	case 2:
		cout << "Enter New Last name" << endl;
		cin >> newvalue;
		setLast(newvalue);
		break;
	case 3:
		cout << "Enter New Id name" << endl;

		cin >> newvalue;
		setId(newvalue);
		break;
	case 4:
		cout << "Enter New Password" << endl;
		cin >> newvalue;
		setPass(newvalue);
		break;
	case 5:
		cout << "Enter New age" << endl;
		cin >> age;
		setAge(age);
		break;
	case 6:
		cout << "Enter New Notes" << endl;
		cin >> newvalue;
		setNotes(newvalue);
		break;
	default:
		cout << "not valid input ----" << endl;
	}

}

string User::getId()const
{
	return id;
}

const int User::getNumAppointment()const {
	return numAppointment;
}

Appointment* User::getMyAppointment()
{
	if (numAppointment == 0) return 0;
	return (*appointments);
}

const userType User::wichType()const
{
	return type;
}

int User::checkIfMatch(string& pass)const
{
	if (this->pass == pass)
		return type;
	return -1;
}

int checkDate(int month, int day, int year)
{
	time_t nowtime = time(NULL);
	tm now = *localtime(&nowtime);

	if (year < now.tm_year)
		return 1;
	else if (year == now.tm_year)
		if (month < now.tm_mon)
			return 1;
		else if (month < now.tm_mon)
			if (day < now.tm_mday)
				return 1;

	if ((month = 1) || (month = 3) || (month = 5) || (month = 7) ||
		(month = 8) || (month = 10) || (month = 12))
	{
		day <= 31;
	}
	else if ((month = 4) || (month = 6) || (month = 9) || (month = 11))
	{
		day <= 30;
	}
	else if ((month = 2) && (year % 4 == 0))
	{
		day <= 29;
	}
	else if ((month = 2) && (year % 4 != 0))
	{
		day <= 28;
	};
	int status = 0;
	cout << "Good date!" << endl;

	if ((year < 999) || (year > 10000))
	{
		status == 1;
		cout << "Bad year" << endl;

	}
	if ((month < 1) || (month > 12))
	{
		status == 2;
		cout << "Bad month" << endl;
	}
	else if ((day < 1) || (day > 31))
	{
		status == 3;
		cout << "Bad day. Not 1-31" << endl;

	}
	else if ((day < 1) || (day > 30))
	{
		status == 4;
		cout << "Bad day, not 1-30" << endl;
	}
	else if ((day < 1) || (day > 29))
	{
		status == 5;
		cout << "Bad day, not 1-29" << endl;
	}
	else if ((day < 1) || (day > 28))
	{
		status == 6;
		cout << "Bad day, not 1-28" << endl;
	}
	return status;
};
  
int checkTime(int hour,int min)
	{

	time_t nowtime = time(NULL);
	tm now = *localtime(&nowtime);

	if (hour < now.tm_hour)
		return 1;
	else if (hour == now.tm_hour)
		if (min < now.tm_mon)
			return 1;

	if ((hour >= 0) && (hour <= 24))
		if (min >= 0 && min <= 59)
			return 1;
		else
			cout << "Bad mintes, not 1-59" << endl;
	else
		cout << "Bad hour, not 0-24" << endl;

	return 0;
	}

bool getTime(tm* timeAppoinment)
{
	int valid=0;
	tm* t=new tm;
	time_t nowtime = time(NULL);
	tm now = *localtime(&nowtime);
	cout << "Enter day: ";
	cin >> t->tm_mday;
	cout << "Enter month: ";
	cin >> t->tm_mon;
	cout << "Enter year: ";
	cin >> t->tm_year;
	valid+=checkDate(t->tm_mon, t->tm_mday, t->tm_year);
	cout << "Enter hour: ";
	cin >> t->tm_hour;
	cout << "Enter minets: ";
	cin >> t->tm_min;
	valid += checkTime(t->tm_hour, t->tm_min);
	t->tm_isdst = 0;
	t->tm_wday = 0;
	t->tm_yday = 0;
	t->tm_sec = 0;
	timeAppoinment = t;
	if (valid == 0)
		return 1;
	return 0;
}

Appointment* User::requestAppointment(User*& user)
{
	bool valid;
	string notes;
	tm* t;
	getTime(t);
	if (!valid)
	{
		cout << "Faild worng time" << endl;
		return 0;
	}
	Appointment *newAppointment = new Appointment[1]{ Appointment(user, this , t , notes, Status(0)) };//create
	return newAppointment;
}

bool User::createAppointment(Appointment* appointment) {

	if (sizeAppointment <= numAppointment)
	{

		Appointment** temp = appointments;//copy old list
		sizeAppointment *= 2;
		appointments = new Appointment*[sizeAppointment];//allocating new size of list
		for (int i = 0; i < numAppointment; i++)//copy the old list to new list
			appointments[i] = temp[i];
	}
	appointments[numAppointment] = appointment;
	numAppointment++;
	return 1;
}

void User::reviewAppointment()
{
	int choice = 1;
	if (numAppointment != 0)
	{
		cout << "Reviwing mode:" << endl;
		for (int i = 0; i < numAppointment && choice == 1; i++)
		{
			cout << i + 1 << ") ";
			appointments[i]->printAppointment();
			cout << "Do you want to:" << endl << "1) Approve" << endl << "2) Cancel" << endl;
			cin >> choice;
			if (choice == 1)
				appointments[i]->addAppointmentToTherapist();//if approve add to therapist

			deleteAppointment(appointments[i]);//delete from receptionist both case

			if (i != numAppointment)
			{
				cout << "Do you want to get next appoinment:" << endl << "1) Yes" << endl << "2) No" << endl;
				cin >> choice;
			}
			else
				cout << "No more Appinment to reviwe return to Main Menu." << endl;
		}
	}
	else
		cout << "No Appinment to reviwe return to Main Menu." << endl;
}

void User::deleteUserAppointment()
{
	for (int i = 0; i < numAppointment; i++)
	{
		appointments[i]->deleteAppointmentFromParticipants();
	}

}

bool User::deleteAppointment(Appointment* appointment)
{	
	for (int i = 0; i < numAppointment; i++)//search for appointment
		if (appointments[i] == appointment)
		{
			appointments[i]->deleteAppointment();
			numAppointment--;
			for (int j = i; j < numAppointment; j++)
				appointments[j] = appointments[j + 1];
			return 1;
		}
	return 0;
}

void User::printUser()
{
	
	cout << "Name: " << first << " " << last << " ID: " << id << endl;
}

void User::printMyPatients()
{
	cout << "Your Patients:" << endl;
	if (numAppointment != 0)
		for (int i = 0; i < numAppointment; i++)
			appointments[i]->printPatients();
	cout << endl;
	cout << "-----------------" << endl;

}

void User::printMyAppointments() {
	int currindex,lessnum = 0;//not print num
	cout << "Your Appointments:" << endl;
if (numAppointment != 0)
for (int i = 0; i < numAppointment; i++)
{
	currindex = i - lessnum + 1;
	lessnum +=appointments[i]->printAppointment(currindex);
}
else
cout << "No Appointments" << endl;
cout << "-----------------" << endl;

}

void User::saveData(ofstream& file)
{
	file << "[" << type + 1 << "] " << age << ", " << first << ", " << last << ", " << id << ", " << pass << ", " << notes << endl;
	if (numAppointment != 0)
		for (int i = 0; i < numAppointment; i++)
			appointments[i]->saveData(file);
}

void User::closeApp()//free memory
{
	for (int i = 0; i < numAppointment; i++)
		appointments[i]->closeApp();
	delete[]appointments;
}

//C'tors & D'tors

User::User(userType type, int age, string first, string last, string id, string pass, string notes) : type (type) ,age(age), first(first), last(last), id(id), pass(pass), notes(notes),appointments(0), sizeAppointment(dsize),numAppointment(0)
{
	appointments = new Appointment*[dsize];
}

User::User() : type((userType)0), age(0), first(0), last(0), id(0), pass(0), notes(0),appointments(0), sizeAppointment(0), numAppointment(0)
{
	appointments = new Appointment*[dsize];
}


User::User(const User& other) : type(other.type), age(other.age), first(other.first), last(other.last), id(other.id), pass(other.pass), notes(other.notes), sizeAppointment(other.sizeAppointment),numAppointment(other.numAppointment)
{
	appointments = new Appointment*[sizeAppointment];
	for (int i = 0; i < numAppointment; i++)
		appointments[i] = other.appointments[i];
}

const User& User::operator=(const User& other)
{
	if (this == &other)
		return (*this);//if empty return pointer
	this->~User();//if not desrtry
	new (this) User(other);//create empty
	return (*this);//return pointer

}

User::~User()
{
	delete[]appointments;
}

