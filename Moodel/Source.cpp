//Rom Fatal 204027395
//Tal Shlev 313584914
//Shar Robinshtin 208997452
#include <iostream>
#include <fstream>
#include <string>
#include "college.h"
using namespace std;

void getDataInit(ifstream& file, College& college);

void getDataSimulation(ifstream& file, College& college, ostream& out);

int main(int argc, char* argv[])
{	
	College college;
	if (argc != 4) {
		printf("Error");
		exit(1);
	}
	if (argv[1] == NULL && argv[2] == NULL && argv[3] == NULL) {
		printf("Error");
		exit(1);
	}

	ifstream init(argv[1]), simulation(argv[2]);
	ofstream output(argv[3], std::ios::out | std::ios::trunc);
	getDataInit(init, college);
	getDataSimulation(simulation, college, output);


	return 0;
}

void getDataInit(ifstream& file, College& college)
{
	char tempc[50];
	string line, type, first, temp, collageName, departmentName, templine, courseName;
	file >> line;
	int i = 0, j = 0, courseNumber, coursePoints,endfile=0,endline=0;
nextLine:while (!file.eof())
{

	if (line[0] == '#')//get data from file on user
	{
		getline(file, line);
		goto nextLine;
	}
	getline(file, temp, ':');
	getline(file, collageName);
	first.erase(0, 1);
	college.updateCollegeName(collageName);
	getline(file, temp, ':');
	getline(file, templine);
	endline = templine.length();
	for ( ; i < endline;)
	 {
		while (templine[i] != ',' && i < endline)
		{
			tempc[j] = templine[i];

			i++;
			j++;
		}
		tempc[i] = '\0';
		departmentName = tempc;
		college.addDepartment(departmentName);
		j = 0;
		i++;
	}

	getline(file, temp, ':');
	getline(file, templine);
	i = 0;
	endline = templine.length();
	for ( ; i < endline;)
	{
		while (templine[i] != ',' && i < endline)
		{
			tempc[j] = templine[i];

			i++;
			j++;
		}
		tempc[i] = '\0';
		courseNumber = atoi(tempc);
		college.addCourse(courseNumber);
		j = 0;
		i++;
	}
	getline(file, templine);
	endfile = 0;
nextLine2:while (!file.eof() || endfile < 2)
{

	if (templine[0] == '#')//get data from file on CourseDetails
	{
		getline(file, templine);
		endfile += file.eof();
		goto nextLine2;
	}
	i = 0;
	while (templine[i] != ':')
	{
		tempc[j] = templine[i];
		i++;
		j++;
	}
	tempc[i] = '\0';
	i++;
	j = 0;
	while (templine[i] != ',')
	{
		tempc[j] = templine[i];
		i++;
		j++;
	}
	tempc[j] = '\0';
	courseNumber = atoi(tempc);
	i++;
	j = 0;

	while (templine[i] != ',')
	{
		tempc[j] = templine[i];
		i++;
		j++;
	}
	tempc[j] = '\0';
	departmentName = tempc;

	i++;
	j = 0;

	while (templine[i] != ',')
	{
		tempc[j] = templine[i];
		i++;
		j++;
	}
	tempc[j] = '\0';
	coursePoints = atoi(tempc);
	i++;
	j = 0;
	endline = templine.length();
	for ( ; i < endline;i++)
	{
		tempc[j] = templine[i];
		j++;
	}
	tempc[j] = '\0';
	courseName = tempc;
	getline(file, templine);
	endfile += file.eof();
	college.updateCourseDetails(courseNumber, coursePoints, courseName, departmentName);
}
}
file.close();
}

void getDataSimulation(ifstream& file, College& college, ostream& out) {
	char temp;
	string first,last, line, adress,department;
	int type, id, yearS, courseId;
nextLine:while (!file.eof())
{
	temp =file.get();
	if (temp == '#'||temp=='\n')//get data from file on user
	{
		if(temp != '\n')
		getline(file, line);
		goto nextLine;
	}
	type = (int)((temp - 48));
	file.get();
	switch (type)
	{
	case 1:
		getline(file, first,',');
		getline(file, last, ',');
		file >> id;
		file.get();
		getline(file, adress, ',');
		file >> yearS;
		file.get();
		getline(file, department);
		college.addStudent(first, last, id, yearS, adress, department);
		break;
	case 2:
		file >> id;
		file.get();
		file >> courseId;
		college.signUpCourse(id, courseId);
		break;
	case 3:
		file >> courseId;
		college.completionCourse(courseId);
		break;
	case 4:
		file >> id;
		file.get();
		file >> courseId;
		college.graduateStudent(id, courseId);
		break;
	case 5:
		file >> id;
		file.get();
		file >> courseId;
		college.removeStudent(id, courseId);
		break;
	case 6:
		file >> id;
		file.get();
		file >> yearS;
		college.deleteStudent(id, yearS);
		break;
	case 7:
		getline(file, department,',');
		file >> yearS;
		college.printDepartmentCycleDetailses(out, department, yearS);
		break;
	case 8:
		file >> courseId;
		college.printCourseDetails(out, courseId);
		break;
	}
	getline(file, line);
}
		 file.close();
}
