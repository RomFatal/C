#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "animal.h"
#include "Type.h"

//checking if the Animal ID already exist return 0 if alreday exist
int checkAvailabilityAnimal(Animal_Type* animalType, char* compare) 
{
	int i = 0;
	while (animalType != NULL)
	{
		if (strcmp(animalType->animalList->id, compare) == 0)
			return 0;
		if (animalType->placesAllowed == i)
		{
			if (strcmp(animalType->waitingList->id, compare) == 0)
				return 0;
			i++;
		}
		return 1;
	}
}

//check if id exsist return 0 if not
int checkID(Animal_Type* animalType, char* id)
{
	Animal_Type head = *animalType;

	while (head.animalList != NULL)
	{
		if (strcmp(head.animalList->id, id) == 0)
			return 1;
		head.animalList = head.animalList->Next;
	}
	while (head.waitingList != NULL)
	{
		if (strcmp(head.waitingList->id, id) == 0)
			return 1;
		head.waitingList = head.waitingList->Next;
	}
	return 0;
}

void getDataAnimal(char* line, char* typeName, char* id, char* animalName, int* wight, int* age)
{
	int j = 0, i = 2, size, c;//i=character counter in Array, he start from third character:(skip on action & ,)
	char wightC[25], ageC[25];
	while (line[i] != ',')//get typeName
	{
		typeName[i - 2] = line[i];
		i++;
	}
	typeName[i - 2] = '\0';
	i++;

	while (line[i] != ',')//get ID
	{
		id[j] = line[i];
		i++;
		j++;
	}
	id[j] = '\0';
	i++;

	j = 0;
	while (line[i] != ',')//get Name
	{
		animalName[j] = line[i];
		i++;
		j++;
	}
	animalName[j] = '\0';
	i++;

	j = 0;
	while (line[i] != ',')////get wight
	{
		wightC[j] = line[i];
		i++;
		j++;
	}
	i++;

	size = j;
	c = 0;
	while (size != c)//convert the wightAllowed from char to int number
	{
		*wight = *wight + (wightC[j - 1] - '0')*pow(10, c);
		c++;
		j--;
	}
	j = 0;

	while (line[i] != '\0')////get age
	{
		ageC[j] = line[i];
		i++;
		j++;
	}
	size = j;
	c = 0;
	while (size != c)//convert the ageAllowed from char to int number
	{
		*age = *age + (ageC[j - 1] - '0')*pow(10, c);
		c++;
		j--;
	}

}

void getDataAnimalRemove(char* line, char* typeName, char* id)
{
	int j = 0, i = 2, r;//i=character counter in Array, he start from third character:(skip on action & ,)
	char wightC[25], ageC[25];
	while (line[i] != ',')//get typeName
	{
		typeName[i - 2] = line[i];
		i++;
	}
	typeName[i - 2] = '\0';
	i++;

	while (line[i] != '\0')//get ID
	{
		id[j] = line[i];
		i++;
		j++;
	}
	id[j] = '\0';
}

//after deleted animal from type checking if ther is needed to move animal from waiting list to regular list
void moveFromWaitingList(Animal_Item** animalHead, Animal_Item** waitingHead)
{
	Animal_Item *listHead = *animalHead;
	Animal_Item *curr = *waitingHead, *prev = *waitingHead;

	if (*waitingHead == NULL)//if waiting list empty
		return;

	curr = *waitingHead;
	*waitingHead = (*waitingHead)->Next;
	curr->Next = listHead;
	*animalHead = curr;
	return;
}

void addAnimal(Animal_Type** animalType, Animal_Item** head, char* line, FILE* output)//
{
	int size, i = 0, wight = 0, age = 0;
	char id[25], animalName[25], typeName[25];
	Animal_Item *New_Animal, *curr;
	Animal_Type* typeHead = *animalType;

	getDataAnimal(line, typeName, id, animalName, &wight, &age);
	while (typeHead != NULL)
	{
		if (strcmp(typeHead->typeName, typeName) == 0)//searching the recosting typeName
		{
			if ((checkID(typeHead, id)) == 0)//searching the recosting ID
			{
				New_Animal = (Animal_Item *)malloc(1 * sizeof(Animal_Item));//Allocate and enter value
				if (New_Animal == NULL)
				{
					fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
					return;
				}
				size = strlen(id);
				New_Animal->id = (char *)malloc(size * sizeof(char));
				if (New_Animal->id == NULL)
				{
					fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
					return;
				}
				size = strlen(animalName);
				New_Animal->name = (char *)malloc(size * sizeof(char));
				if (New_Animal->name == NULL)
				{
					fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
					return;
				}
				strcpy(New_Animal->id, id);
				strcpy(New_Animal->name, animalName);
				New_Animal->wight = wight;
				New_Animal->age = age;
				curr = typeHead->animalList;

				while (curr != NULL)//check wich list to put the animal
				{
					curr = curr->Next;
					i++;
				}

				if (i < typeHead->placesAllowed)//if there is place
				{
					*head = New_Animal;
					New_Animal->Next = typeHead->animalList;
					typeHead->animalList = New_Animal;
					fprintf(output, "Add a new Animal to the Zoo: Sucssed Anmial Id:%s Name:%s as been added\n", id, animalName);
				}
				else//if there is not place
				{
					*head = New_Animal;
					(*head)->Next = typeHead->waitingList;
					typeHead->waitingList = *head;
					fprintf(output, "Add a new Animal to the Zoo: Sucssed Anmial Id:%s Name:%s as been added to Waiting List\n", id, animalName);
				}
				return;
			}
		}
		typeHead = typeHead->Next;
	}
	fprintf(output, "Add a new Animal to the Zoo: Faild this Id:%s already exist\n", id);
	fprintf(stderr, "ERROR Add a new Animal to the Zoo This Id already exist\n");
}

void removeAnimal(Animal_Type** animalType, Animal_Item** head, char* line, FILE* output)//
{
	int animalsize = 1;
	char typeName[25], id[25];
	Animal_Type* typeCurr = *animalType;
	Animal_Item *curr, *prev;

	getDataAnimalRemove(line, typeName, id);

	while (typeCurr != NULL)
	{
		if (strcmp(typeCurr->typeName, typeName) == 0)//check whice is the wanted class
		{
			curr = typeCurr->animalList;
			while (curr != NULL)//check whice is the wanted animal
			{
				if (curr->Next == NULL)//check if animal are the first cell
				{
					if ((strcmp(typeCurr->animalList->id, id)) == 0)//if first cell id are equal
					{
						*head = typeCurr->animalList;
						curr = *head;
						*head = (*head)->Next;
						typeCurr->animalList = *head;
						free(curr);
						fprintf(output, "Removing a Animal from the Zoo: Sucssed Animal Id:%s as been removed\n", id);
						moveFromWaitingList(&typeCurr->animalList, &typeCurr->waitingList);
						return;
					}
				}
				while (curr->Next != NULL)//if more than 1 cell
				{
					prev = curr;
					curr = curr->Next;
					if (0 == strcmp(curr->id, id))
					{
						prev->Next = curr->Next;
						free(curr);
						fprintf(output, "Removing a Animal from the Zoo: Sucssed Animal Id:%s as been removed\n", id);
						moveFromWaitingList(&typeCurr->animalList, &typeCurr->waitingList);
						return;
					}
					animalsize++;
				}
				if (animalsize >= typeCurr->placesAllowed)//Waiting list
				{
					curr = typeCurr->waitingList;
					if (typeCurr->waitingList == NULL) return;
					if ((strcmp(typeCurr->waitingList->id, id)) == 0)//if first cell id are equal
					{
						curr = typeCurr->waitingList;
						typeCurr->waitingList = NULL;
						free(curr);
						fprintf(output, "Removing a Animal from the Zoo: Sucssed Animal Id:%s as been removed\n", id);
						return;
					}
					while (curr->Next != NULL)//if more than 1 cell
					{
						prev = curr;
						curr = curr->Next;
						if (0 == strcmp(curr->id, id))
						{
							prev->Next = curr->Next;
							free(curr);
							fprintf(output, "Removing a Animal from the Zoo: Sucssed Animal Id:%s as been removed\n", id);
							return;
						}
						curr = curr->Next;
					}
				}
				curr = curr->Next;
				animalsize++;
			}
		}
		typeCurr = typeCurr->Next;
	}
	fprintf(output, "Removing a Animal from the Zoo: Faild Animal Id:%s dosent exist\n", id);
	fprintf(stderr, "ERROR This Type already exist\n");
}
