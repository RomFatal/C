#include "organization.h"
#include <fstream>
#include <iostream>
#include "user.h"
#include "appointment.h"

const int dsize = 8;//defult size of arr
//Methods

User* Organization::searchTherapists(string &id)const
{
	if (numTherapists == 0) return 0;
	for (int i = 0; i < numTherapists; i++)//search
		if (therapists[i]->getId() == id)
			return therapists[i];
	return 0;//not found
}

User* Organization::searchPatients(string &id)const
{
	if (numPatients == 0) return 0;
	for (int i = 0; i < numPatients; i++)//search
		if (patients[i]->getId() == id)
			return patients[i];
	return 0;//not found
}

User* Organization::searchReceptionists(string &id)const
{
	if (numReceptionists == 0) return 0;
	for (int i = 0; i < numReceptionists; i++)//search
		if (receptionists[i]->getId() == id)
			return receptionists[i];
	return 0;//not found
}

User* Organization::searchUser(string &id)const
{
	User* user;
	user = searchTherapists(id);
	if (user != 0)
		return user;
	user = searchPatients(id);
	if (user != 0)
		return user;
	user = searchReceptionists(id);
	if (user != 0)
		return user;
	return 0;
}

User* Organization::getUserByIndex(int index)const
{
	return therapists[index];
}

User* Organization::chooseTherapists()
{

		int choice;
		string id;
		cout << "Choose Therapists do you want to get appoinment with Options:" << endl << "1) Print all Therapists" << endl << "2) Search by id" << endl;
		cin >> choice;
		if (choice == 1)
		{
			cout << "List of Therapists:" << endl;
			printTherapists();
			cout << "Choose therapists number: " << endl;
			cin >> choice;
			return getUserByIndex(choice - 1);

		}
		else
		{
			cout << "Enter id: ";
			cin >> id;
			return searchTherapists(id);
		}

}

bool Organization::checkIfExist(string& id)const
{

	if (searchTherapists(id) != 0)
		return 1;
	if (searchPatients(id) != 0)
		return 1;
	if (searchReceptionists(id) != 0)
		return 1;
	return 0;
}

int Organization::checkIfMatch(string& id, string& pass)const
{

	User* toCheck;

	toCheck = searchTherapists(id);
	if (toCheck != 0)
		return toCheck->checkIfMatch(pass);

	toCheck = searchPatients(id);
	if (toCheck != 0)
		return toCheck->checkIfMatch(pass);

	toCheck = searchReceptionists(id);
	return toCheck->checkIfMatch(pass);
}


void addUserIntrnal(User*& user, User**& list, int& size, int& num)
{
	if (size<=num)//alocate memory if neded
	{
		User** temp = list;//copy old list
		size *= 2;
		list = new User*[size];//allocating new size of list
		for (int i = 0; i < num; i++)//copy the old list to new list
			list[i] = temp[i];
	}
	list[num] = user;
	num++;

}

void Organization::addUser(User* &user) {
	switch (user->wichType())
	{
	case 0://Add Therapists
		addUserIntrnal(user, therapists, sizeTherapists, numTherapists);
		break;
	case 1://Add Patients
		addUserIntrnal(user, patients, sizePatients, numPatients);
		break;
	case 2://Add Receptionist
		addUserIntrnal(user, receptionists, sizeReceptionist, numReceptionists);
		break;
	}

}

bool Organization::addAppointment(Appointment*& newAppointment)
{
	if (numReceptionists > 0)//if Receptionist exist
	{
		if (sizeAppointment <= numAppointments)//check if arr is max capacity yes->allocate memory multiply itself 
		{

			Appointment** temp = appointment;//copy old list
			sizeAppointment *= 2;
			appointment = new Appointment*[sizeAppointment];//allocating new size of list
			for (int i = 0; i < numAppointments; i++)//copy the old list to new list
				appointment[i] = temp[i];
		}
		appointment[numAppointments] = newAppointment;//add new appoinment to list

		addToReceptionist(appointment[numAppointments]);//add the apoinment to Receptionist list
		newAppointment->addAppointmentToPatient();//add the apoinment to Patient list
		numAppointments++;
		return true;
	}
	else return false;
}

void Organization::addToReceptionist(Appointment*& appointment)//add the apoinment to Receptionist list
 {
	int min= receptionists[0]->getNumAppointment(), minIndex=0;

		for (int i = 0; i < numReceptionists; i++)//search for Receptionist with the minimum appoimtment
			if (min > receptionists[i]->getNumAppointment())
			{
				min = receptionists[i]->getNumAppointment();
				minIndex = i;
			}
		receptionists[minIndex]->createAppointment(appointment);//add the apoinment to Receptionist list
}


void deleteUserIntrnal(User*& user, User**& list, int& size, int& num)
{
	User* to_delete;
	for (int i = 0; i < num; i++)
	{
		if (list[i] == user)
		{
			to_delete = list[i];
			num--;
			for (int j = i; j < num; j++)
				list[j] = list[j + 1];
			delete[]to_delete;
			return;
		}
	}
}

void Organization::deleteFromReceptionist(Appointment* appointment)
{
	for (int i = 0; i < numReceptionists; i++)
		if (receptionists[i]->deleteAppointment(appointment) == 1)//Try delete appoimtment from Receptionists, if found existing
			return;
}

void Organization::deleteUser(string& id)
{
	User* user = searchUser(id);
	int num;
	const Appointment* appointment;

	switch (user->wichType())//wich type
	{
	case 0://Therapists
		user->deleteUserAppointment();//delete user appointment and participants
		deleteUserIntrnal(user, therapists, sizeTherapists, numTherapists);//delete user
		break;
	case 1://if Patients
		num = user->getNumAppointment();
		appointment = user->getMyAppointment();
		for (int i = 0; i < num; i++)
		{
			deleteFromReceptionist((Appointment*)&appointment[i]);//delete peding appointment
		}
		user->deleteUserAppointment();//delete user appointment
		deleteUserIntrnal(user, patients, sizePatients, numPatients);
		break;
	case 2:
		user->deleteUserAppointment();
		deleteUserIntrnal(user, receptionists, sizeReceptionist, numReceptionists);
		break;
	}
}

bool Organization::deleteAppointment(User*& user)
{
	Appointment* to_delete;
	int choice;
	if (user->getMyAppointment() != 0)
	{
		user->printMyAppointments();
		cout << "Which appoinment do you want to cancel (number): ";//choose appointment
		cin >> choice;
		if (appointment[choice - 1]->getStatus() == 0)//if appoinment are pending
		{
			deleteFromReceptionist(appointment[choice - 1]);//delete from Receptionists
			user->deleteAppointment(appointment[choice - 1]);//delete from Patients
		}
		else
			appointment[choice - 1]->deleteAppointmentFromParticipants();//delete from Therapists & Patients


		for (int i = 0; i < numAppointments; i++)//delete from Appointmet arr
			if (appointment[i] == appointment[choice - 1])
			{
				to_delete = appointment[choice - 1];
				numAppointments--;
				for (int j = i; j < numAppointments; j++)
					appointment[j] = appointment[j + 1];
				delete[]to_delete;
				return 1;
			}
	}
	else
		cout << "------- No Appointments -------" << endl;
	return 0;
}


void Organization::printTherapists()const
{
	for (int i = 0; i < numTherapists; i++)
	{
		cout << i+1 << ") ";
		therapists[i]->printUser();
	}
	cout << "-----------------" << endl;
}

void Organization::printPatients()const
{
	for (int i = 0; i < numPatients; i++)
	{
		cout << i+1 << ") ";
		patients[i]->printUser();
	}
	cout << "-----------------" << endl;
}

void Organization::saveData(ofstream& file)const
{
	int i;

	file << "#Therapists:" << endl;
	for (i = 0; i < numTherapists; i++)
		therapists[i]->saveData(file);
	file << "# Receptionist:" << endl;
	for (i = 0; i < numReceptionists; i++)
		receptionists[i]->saveData(file);

	file << "#Patients:" << endl;
	for (i = 0; i < numPatients; i++)
		patients[i]->saveData(file);
}

void Organization::closeApp()//free memory
{
	for (int i = 0; i < numTherapists; i++)
		therapists[i]->closeApp();
	for (int i = 0; i < numPatients; i++)
		patients[i]->closeApp();
	for (int i = 0; i < numReceptionists; i++)
		receptionists[i]->closeApp();
	delete[]therapists;
	delete[]patients;
	delete[]receptionists;
}
//C'tors & D'tors

Organization::Organization(): therapists(0), patients(0), receptionists(0), appointment(0), sizeTherapists(dsize), sizePatients(dsize), sizeReceptionist(dsize),sizeAppointment(dsize),
numTherapists(0), numPatients(0), numReceptionists(0), numAppointments(0)
{
	therapists = new User*[dsize];
	patients = new User*[dsize];
	receptionists = new User*[dsize];
	appointment = new Appointment*[dsize];
}

Organization::~Organization() 
{
}
