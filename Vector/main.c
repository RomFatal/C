//Presented by Rom Fatal
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

//a student structure, which will be used in this program.
typedef struct student_t
{
	float studentAvg;
	int studentId;
	char* studentName;
}student;

/*Will allocate and create a student type, given the correct arugments.
* returns : NULL if allocation failed, allocated student pointer is successful.
*/

student* createStudent(char* name, int id, float average);
int* int_create(int data);
void print_student(student* data);
void print_int(int* data);
void free_student(student* data);
void free_generic();

int main(int argc, char** argv)
{
	//declare an integer vector, initialize with size of 4 and copy, print and free functions.

	vector integerVec;
	if ((vector_init(&integerVec, 4,print_int, free_generic)) == 0)
		return -1;
	
	int index = 0;  int newSize = 0;
	//insert members to the vector.
	for (index = 0; index < 128; index++)
	{
		vector_insert(integerVec,int_create(index * 2 + index + 1));
	}
	//print all the contents of the vector.
	printf("Integer vector, size count : %d\n", vector_length(integerVec));
	vector_print(integerVec);

	newSize = vector_length(integerVec) / 4;
	//now remove members from the vector.
	for (index = 128; index > newSize; index--)
	{
		vector_delete(integerVec, index);
	}
	printf("Integer vector, size count : %d\n", vector_length(integerVec));
	vector_print(integerVec);


	//a student vector.
	vector studentVec;
	if (vector_init(&studentVec, 4, print_student,free_student) == 0)
		return -1;

	 index = 0;  newSize = 0;
	//insert members to the vector.
	for (index = 0; index < 48; index++)
	{
		vector_insert(studentVec, createStudent("Test Student", index * 10 + index * 30, index * index / (index + 1)));
	}
	//print all the contents of the vector.
	vector_print(studentVec);

	newSize = vector_length(studentVec) / 4;
	//now remove members from the vector.
	for (index = 48; index > newSize; index--)
	{
		vector_delete(studentVec, index);
	}
	printf("Student vector:  size count : %d\n", vector_length(studentVec));
	vector_print(studentVec);

	//create a vector of vectors
	vector vectorVec;
	if (vector_init(&vectorVec, 4,print_vec, free_generic) == 0)
		return -1;
	//resize it to 3, see what happens.
	vector_resize(vectorVec, 2);
	//inset current program vectors.
	vector_insert(vectorVec, integerVec);
	vector_insert(vectorVec, studentVec);
	//print vector of vectors.
	vector_print(vectorVec);

	void* v1 = vector_get(vectorVec, 1);
	printf("Testing the fetching of a vector from a vector's vector : \n");
	vector_print(v1);

	//farewell, vectors!
	vector_free(v1);
	vector_free(vectorVec);
	vector_free(studentVec);


	return 42;
}


student* createStudent(char* name, int id, float average)
{
	char to[25];
	student* newStudent = (student*)malloc(sizeof(student));
	strcpy(to, name);

	if (newStudent == NULL)
	{
		return NULL;
	}
	int x = strlen(name);
	newStudent->studentName = (char*)malloc(sizeof(char) * strlen(name)+1);

	if (newStudent->studentName == NULL)
	{
		free(newStudent);
		return NULL;
	}

	newStudent->studentAvg = average;
	newStudent->studentId = id;
	strcpy(newStudent->studentName, name);
	return newStudent;

}

int* int_create(int data)
{
	int *new_int= (int*)malloc(sizeof(int));
	if (new_int == NULL)
	{
		return NULL;
	}
	*new_int = data;
	return new_int;
}

void print_student(student* data)
{
	printf("Student Name:%s Id:%d Average:%d\n",data->studentName,data->studentId,data->studentAvg);
}

void print_int(int* data)
{
	printf("The number is:%d\n", *data);
}

void free_student(student* data)
{
	char* to_free = data->studentName;
	free(to_free);
}

void free_generic()
{

}

