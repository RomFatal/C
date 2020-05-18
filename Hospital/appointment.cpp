#include "appointment.h"
#include "user.h"
#include <fstream>
#include <iomanip>
//Methods

int Appointment::getStatus()const
{
	return status;
}

string Appointment::getTherapistId()const
{
	return therapist.getId();
}

string Appointment::getPatientId()const
{

	return patient.getId();

}


void Appointment::addAppointmentToPatient()
{
	patient.createAppointment(this);
}

void Appointment::addAppointmentToTherapist()
{
	if (therapist.createAppointment(this))
		status = (Status)1;
}

void Appointment::deleteAppointmentFromParticipants()
{
	if (status == 0)
	{
		patient.deleteAppointment(this);
		status = (Status)2;//Canceled
	}
	else
	{
		patient.deleteAppointment(this);
		therapist.deleteAppointment(this);
	}
}


string statusToString(Status status)
{
	switch (status)
	{
	case 0:
		return "pending";
		break;
	case 1:
		return "approved";
		break;
	case 2:
		return "canceled";
		break;
	}
}

bool checkTodayDate(tm* t)
{
	time_t nowtime = time(NULL);
	tm now = *localtime(&nowtime);
	now.tm_year += 1900;
	now.tm_mon += 1;
	if (t->tm_year > now.tm_year)
		return 1;
	else if (t->tm_year == now.tm_year)
		if (t->tm_mon > now.tm_mon)
			return 1;
		else if (t->tm_mon == now.tm_mon)
			if (t->tm_mday > now.tm_mday)
				return 1;
			else if (t->tm_mday = now.tm_mday)
				if(t->tm_hour > now.tm_hour)
				return 1;
			else if (t->tm_hour = now.tm_hour)
				if (t->tm_min > now.tm_mon)
					return 1;
	return 0;
}

void Appointment::printAppointment()
{
	int valid = checkTodayDate(time);
	if (valid)
	cout << "Patient id: " << patient.getId() << "Therapists id: " << therapist.getId() << "Date: " << setfill('0') << setw(2) << time->tm_mday << "/" << setfill('0') << setw(2) << time->tm_mon << "/" << time->tm_year << "Time: " << setfill('0') << setw(2) << time->tm_hour << ":" << time->tm_min << setfill('0') << setw(2) << ", " << notes << " Notes: " << notes << " Status: " << statusToString(status) << "." << endl;
}

int Appointment::printAppointment(int& i)
{
	int valid = checkTodayDate(time);
	if (valid)
	{
		cout << i << ") ";
		cout << "Patient id: " << patient.getId() << " Therapists id: " << therapist.getId() << " Date: " << setfill('0') << setw(2) << time->tm_mday << "/" << setfill('0') << setw(2) << time->tm_mon << "/" << time->tm_year << " Time: " << setfill('0') << setw(2) << time->tm_hour << ":" << setfill('0') << setw(2) << time->tm_min << setfill('0') << setw(2) << ", " << notes << " Notes: " << notes << " Status: " << statusToString(status) << "." << endl;
		return 0;
	}
	else return 1;
}

void Appointment::printPatients()
{
	patient.printUser();
	cout << endl;
}

void Appointment::saveData(ofstream& file)
{

	file << "> " << therapist.getId() << ", " << patient.getId() << ", " << setfill('0') << setw(2) << time->tm_mday << "/" << setfill('0') << setw(2) << time->tm_mon << "/" << time->tm_year << ", " << setfill('0') << setw(2) << time->tm_hour << ":" << setfill('0') << setw(2) << time->tm_min << ", "<< notes << ", " << statusToString(status) << "." << endl; //time

}

void Appointment::deleteAppointment()
{
	delete[]time;
}

void Appointment::closeApp()//free memory
{
	delete[]time;
}
//C'tors & D'tors

Appointment::Appointment(User* therapist, User* patient, tm* time, string notes, Status status) : therapist(*therapist), patient(*patient),time(time), notes(notes), status(status)
{
	this->time = time;
}

Appointment::~Appointment()
{
}
