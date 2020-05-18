#include "framework.h"
#include <string>
#include <fstream>
#include "user.h"
#include "organization.h"
#include "appointment.h"


//Methods


int statusConvert(string& str)//status to string
{
	if (str == "pending") return 0;
	else if (str == "approved") return 1;
	else if (str == "canceled") return 2;
	return -1;
}

void getTimeFromFile(fstream& file, tm*& time)
{
	char dot;
	tm* t = new tm[1];
	file >> t->tm_mday;
	file.get(dot);
	file >> t->tm_mon;
	file.get(dot);
	file >> t->tm_year;
	file.get(dot);
	file >> t->tm_hour;
	file.get(dot);
	file >> t->tm_min >> dot;
	t->tm_isdst = 0;
	t->tm_wday = 0;
	t->tm_yday = 0;
	t->tm_sec = 0;
	time = t;
}

void Framework::getData(fstream& file) //get all data from file
{

	string first, last, id, pass, notes, line;
	userType type;
	tm* t;
	int age = 50;
	organization = new Organization;
	file >> line;
nextLine:while (!file.eof())
{

	if (line[0] == '#')//get data from file on user
	{
		getline(file, line);
		goto nextLine;
	}
	type = (userType)((line[1] - 48) - 1);
	file >> age >> line;
	getline(file, first, ',');
	first.erase(0, 1);
	getline(file, last, ',');
	last.erase(0, 1);
	getline(file, id, ',');
	id.erase(0, 1);
	getline(file, pass, ',');
	pass.erase(0, 1);
	getline(file, notes);
	notes.erase(0, 1);

	User *user = new User[1]{ User(type, age, first, last, id, pass, notes) };//allocate user
	organization->addUser(user);//add to arr
	file >> line;

	if (line[0] == '>')//check for existing appointment
	{
		string therapistsID, patientsID, date, time, notes, tempStatus,dot;
		User *therapist;
		while (line[0] == '>' && type == 1 && !file.eof())//add only patients appoinment
		{
			getline(file, therapistsID, ',');//get data on appoinment
			therapistsID.erase(0, 1);
			getline(file, patientsID, ',');
				patientsID.erase(0, 1);
			if (patientsID == id)//if patients ask appointment for himself
			{
				getTimeFromFile(file, t);
				getline(file, notes, ',');
				notes.erase(0, 1);
				getline(file, tempStatus, '.');
				tempStatus.erase(0, 1);
				Status status = (Status)statusConvert(tempStatus);//string to type
				therapist = organization->searchTherapists(therapistsID);//search for therapists
				Appointment *newAppointment = new Appointment[1]{ Appointment(therapist, user, t , notes, status) };//create new appoinment
				organization->addAppointment(newAppointment);//add appoinment
				file >> line;
			}
		}
	}
}
}

void Framework::loadMainMenu()
{
	int choice1 = 0, choice2 = 0, choice3 = 3, type;
	User *user, *temp;
	string id, pass;
	Appointment* newAppointment;

Mainmenu:while (choice1 != 4)
{
	cout << "Main Menu:" << endl << "1) Login" << endl << "2) Signup" << endl << "3) Delete User" << endl << "4) Exit" << endl;
	cin >> choice1;
	switch (choice1)
	{
	case 1:
		cout << "Enter Your Id: ";
		cin >> id;
		if (checkIfExist(id))
		{
		tryAgain:cout << "Enter Your Password: ";
			cin >> pass;
			type = checkIfMatch(id, pass);
			if (type != -1)//user and pass match
			{
				switch (type)
				{
				case 0://Therapists
					user = organization->searchTherapists(id);
					while (1)
					{
						cout << "1) Browse Patients." << endl << "2) Browse appoinment." << endl << "3) Cancel an appoinment." << endl << "4) Update User." << endl << "5) Rerturn to main menu." << endl;
						cin >> choice2;
						switch (choice2)
						{
						case 1:
							user->printMyPatients();
							break;
						case 2:
							user->printMyAppointments();
							break;
						case 3:
							organization->deleteAppointment(user);
							break;
						case 4:
							user->setMode();
						case 5:
							goto Mainmenu;
						}
					}
				case 1://Patients
					user = organization->searchPatients(id);
					while (1)
					{
						cout << "1) Browse therapste." << endl << "2) Request appoinment." << endl << "3) view my appoinment." << endl << "4) Cancel an appoinment." << endl << "5) Update User info." << endl << "6) Rerturn to main menu." << endl;
						cin >> choice2;
						switch (choice2)
						{
						case 1:
							cout << "List of Therapists:" << endl;
							organization->printTherapists();
							cout << "Do you want to search (by id):" << endl;
							cout << "1) yes" << endl << "2) No" << endl;
							cin >> choice3;
							if (choice3 == 1)
							{
								cout << "Enter id: ";
								cin >> id;
								temp = organization->searchTherapists(id);
								if (temp != 0)
								{
									temp->printUser();
									cout << "-----------------" << endl;
								}
								else
									cout << "Not Found -------" << endl;
							}
							break;
						case 2:
							temp = organization->chooseTherapists();
							newAppointment = user->requestAppointment(temp);
							organization->addAppointment(newAppointment);
							break;
						case 3:
							user->printMyAppointments();
							break;
						case 4:
							organization->deleteAppointment(user);
							break;
						case 5:
							user->setMode();
						case 6:
							goto Mainmenu;
						}
					}
					break;
				case 2://Receptionis
					user = organization->searchReceptionists(id);
					while (1)
					{
						cout << "1) Browse therapstes." << endl << "2) View appoinment of therapste." << endl << "3) Review appoinments." << endl << "4) Update User info." << endl << "5) Rerturn to main menu." << endl;
						cin >> choice2;
						switch (choice2)
						{
						case 1:
							cout << "List of Therapists:" << endl;
							organization->printTherapists();
							cout << "Do you want to search (by id):" << endl;
							cout << "1) yes" << endl << "2) No" << endl;
							cin >> choice3;
							if (choice3 == 1)
							{
								cout << "Enter id: ";
								cin >> id;
								temp = organization->searchTherapists(id);
								if (temp != 0)
								{
									temp->printUser();
									cout << "-----------------" << endl;
								}
								else
									cout << "Not Found -------" << endl;
							}
							break;
						case 2:
							cout << "Selecte a Therapists do you like to view is appointment:" << endl;
							temp = organization->chooseTherapists();
							temp->printMyAppointments();
							break;
						case 3:
							user->reviewAppointment();
							break;
						case 4:
							user->setMode();
						case 5:
							goto Mainmenu;
						}
					}
				}
			}
			else
			{
				cout << "Password incorect" << endl << "1) Try again" << endl << "2) Return to main menu" << endl;
				cin >> choice3;
				if (choice3 == 1)
					goto tryAgain;
			}
			break;
		}
		else
			cout << "Try again - User not exist" << endl;
		break;
	case 2:
		signup();
		break;
	case 3:
		cout << "Enter id of user you want to delete: ";
		cin >> id;
		organization->deleteUser(id);
		break;
	case 4:
		cout << "Thank you that uses in our services" << endl;
		break;
	default:
		cout << "Try Again" << endl;
		break;

	}
}
}

void Framework::signup()
{
	string first, last, id, pass, notes;
	int age, tempType;
	userType type;
	cout << "Signup:" << endl;
	cout << "Enter your type (number): 1.Therapists 2.Patients 3.Receptionist" << endl;
	cin >> tempType;
	type = (userType)((tempType)-1);
	cout << "Enter your id: " << endl;
	cin >> id;
	if (checkIfExist(id) != 1)
	{
		cout << "Enter your password: " << endl;
		cin >> pass;
		cout << "Enter your first name: " << endl;
		cin >> first;
		cout << "Enter your last name: " << endl;
		cin >> last;
		cout << "Enter your age: " << endl;
		cin >> age;
		cout << "Enter your notes: " << endl;
		cin >> notes;
		User *user = new User[1]{ User(type, age, first, last, id, pass, notes) };//allocate user
		organization->addUser(user);//add to arr
		cout << "Sucssed - You are a new member" << endl;
	}
	else
		cout << "Not posibal - This Id alredy exist in the system" << endl;
}

bool Framework::checkIfExist(string& id) const
{
	return organization->checkIfExist(id);
}

int Framework::checkIfMatch(string& id, string& pass) const
{
	return organization->checkIfMatch(id, pass);
}


void Framework::saveDataToFile(ofstream& file)
{
	organization->saveData(file);
}

void Framework::closeApp()//free memory
{
	organization->closeApp();
	delete[]organization;
}
//C'tors & D'tors

Framework::Framework(fstream& file)
{
	getData(file);
}

Framework::~Framework()
{
}
