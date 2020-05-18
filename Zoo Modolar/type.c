#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "type.h"
#include "Animal.h"

typedef struct nodeItem {
	Animal_Item* val;
	struct nodeItem *Next;
} nodeItem;


typedef struct RRRR {
	void* data;
	int curr_index;
	int max_capacity;
}w;

int checkTypeExist(Animal_Type* animalType, char* type) //checking if the AnimalType name already exist return 0 if dosent existing

{
	while (animalType != NULL)
	{
		if (strcmp(animalType->typeName, type) == 0)
		{
			fprintf(stderr, "ERROR This type already exist\n");
			return 1;
		}
		animalType = animalType->Next;
	}
	return 0;
}

void getDatatype(char* line, char* typeName, int* place)
{
	int j = 0, i = 2, size;//i=character counter in Array, he start from third character:(skip on action & ,)
	char placeC[25];
	while (line[i] != ',')//get typeName
	{
		typeName[i - 2] = line[i];
		i++;
	}
	typeName[i - 2] = '\0';
	i++;

	while (line[i] != '\0')//get placesAllowed
	{
		placeC[j] = line[i];
		i++;
		j++;
	}

	size = j;
	i = 0;
	while (size != i)//convert the placesAllowed from char to int number
	{
		*place = *place + (placeC[j - 1] - '0')*pow(10, i);
		i++;
		j--;
	}
}

void sortList(nodeItem** nodeList, Animal_Item *head, int size)
{
	Animal_Item *currItem = head, *tmp;
	nodeItem   *nodeHead = *nodeList, *curr, *newHead;

	if (head->Next == NULL)//is only 1 cell return copy the cell and returnt
	{
		nodeHead = (nodeItem *)malloc(1 * sizeof(nodeItem));
		if (nodeHead == NULL)
		{
			fprintf(stderr, "ERROR Add a new Type to the Zoo: This Type already exist\n");
			return;
		}
		nodeHead->val = currItem;
		nodeHead->Next = NULL;
		(*nodeList) = nodeHead;
		return;
	}


	while (size != 0)//copy List from list to Node list
	{
		newHead = (nodeItem *)malloc(1 * sizeof(nodeItem));//Allocate
		if (newHead == NULL)
		{
			fprintf(stderr, "ERROR Add a new Type to the Zoo: This Type already exist\n");
			return;
		}
		newHead->val = currItem;
		if (nodeHead == NULL)
			newHead->Next = NULL;
		else
		{
			newHead->Next = nodeHead;
		}
		nodeHead = newHead;
		currItem = currItem->Next;
		size--;
	}

	(*nodeList) = nodeHead;
	while (nodeHead != NULL)//Go through the list and arrange it in alphabetical order
	{
		curr = nodeHead->Next;
		while (curr != NULL)//find Head
		{
			if (strcmp(nodeHead->val->name, curr->val->name) > 0)
			{
				tmp = nodeHead->val;
				nodeHead->val = curr->val;
				nodeHead->Next->val = tmp;
			}
			curr = curr->Next;
		}
		nodeHead = nodeHead->Next;
	}

}

void to_free(Animal_Type** typeList)
{
	Animal_Type* typeToFree;

	while (*typeList != NULL)
	{
		typeToFree = (*typeList);
		(*typeList) = (*typeList)->Next;
		free(typeToFree);
	}
}

void printAnimalList(nodeItem* nodeHead, FILE* output)
{
	nodeItem *to_free;

	while (nodeHead != NULL)
	{
		fprintf(output, "Animal Name:%s Animal ID:%s Wight:%.3lf Age:%d\n", nodeHead->val->name, nodeHead->val->id, nodeHead->val->wight, nodeHead->val->age);
		to_free = nodeHead;
		nodeHead = nodeHead->Next;
	}


}

void addType(Animal_Type **head, char* line, FILE* output)
{
	int size, place = 0;
	char typeName[25];
	Animal_Type* new_type, *curr;

	getDatatype(line, typeName, &place);

	if (checkTypeExist(*head, typeName) == 0)//if type not exist
	{
		new_type = (Animal_Type *)malloc(1 * sizeof(Animal_Type));//Allocate
		if (new_type == NULL)
		{
			fprintf(stderr, "ERROR Add a new Type to the Zoo: This Type already exist\n");
			fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
			return;
		}

		size = strlen(typeName);
		new_type->typeName = (char *)malloc(size * sizeof(char));
		if (new_type->typeName == NULL)
		{
			fprintf(stderr, "ERROR Add a new Type to the Zoo: This Type already exist\n");
			fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
			return;
		}

		strcpy(new_type->typeName, typeName);
		new_type->placesAllowed = place;
		new_type->animalList = NULL;
		new_type->waitingList = NULL;

		if (*head == NULL)//if first cell
		{
			new_type->Next = NULL;
			*head = new_type;
		}
		else
		{
			curr = *head;
			*head = new_type;
			new_type->Next = curr;
		}
		fprintf(output, "Add a new Type to the Zoo: Sucssed %s Type as been added\n", &typeName);
	}
	else
	{
		fprintf(output, "Add a new Type to the Zoo: Faild TypeName:%s already exist\n", &typeName);
		fprintf(stderr, "ERROR Add a new Type to the Zoo: This Type already exist\n");
		return;
	}
}

void removeType(Animal_Type **head, char* line, FILE* output)
{
	int i = 2;
	char typeName[25];
	Animal_Type *curr = *head, *prev = *head;

	while (line[i] != '\0')//get typeName
	{
		typeName[i - 2] = line[i];
		i++;
	}
	typeName[i - 2] = '\0';

	if (*head == NULL) return;//if list empty
	if (0 == strcmp((*head)->typeName, typeName))//if first cell
	{
		curr = *head;
		*head = (*head)->Next;
		free(curr);
		fprintf(output, "Removing a Type from the Zoo: Sucssed Type:%s as been removed\n", typeName);
		return;
	}
	while (curr->Next != NULL)//if more than 1 cell
	{
		prev = curr;
		curr = curr->Next;
		if (0 == strcmp(curr->typeName, typeName))
		{
			prev->Next = curr->Next;
			free(curr);
			fprintf(output, "Removing a Type from the Zoo: Sucssed Type:%s as been removed\n", typeName);
			return;
		}
	}
	fprintf(output, "Removing a Type from the Zoo: Faild Type:%s dosent exist\n", typeName);
	fprintf(stderr, "ERROR This Type already exist\n");
}

void printType(Animal_Type* head, char* line, FILE* output)//
{
	int i = 2, animalNum = 0, animalWaitNum = 0;
	char typeName[25];
	Animal_Type *curr = head, *prev = head;
	Animal_Item *AnimalHead, *waitnigHead;
	nodeItem* nodeHead = NULL;

	while (line[i] != '\0')//get typeName
	{
		typeName[i - 2] = line[i];
		i++;
	}
	typeName[i - 2] = '\0';

	if (curr == NULL)
	{
		fprintf(output, "Print Type Details:%s Type list is empty\n", typeName);
		fprintf(stderr, "Print Type Details:%s Type list is empty\n", typeName);
		return;
	}

	while (curr != NULL)
	{
		if (strcmp(curr->typeName, typeName) == 0)
		{
			AnimalHead = curr->animalList;
			waitnigHead = curr->waitingList;
			while (AnimalHead != NULL)//count animal Numcer
			{
				AnimalHead = AnimalHead->Next;
				animalNum++;
			}
			while (waitnigHead != NULL)//count waitnig animal Numcer
			{
				waitnigHead = waitnigHead->Next;
				animalWaitNum++;
			}
			fprintf(output, "Type Details: TypeName:%s AnimalNumber:%d AnimalWaitingNumber:%d\n", typeName, animalNum, animalWaitNum);

			if (curr->animalList == NULL)
			{
				fprintf(output, "The Animal List is empty\n");
				return;
			}
			else
			{
				fprintf(output, "The Animal in the regular list are:\n");
				sortList(&nodeHead, curr->animalList, animalNum);//sort list
				printAnimalList(nodeHead, output);//print

				if (curr->waitingList == NULL)
				{
					fprintf(output, "The Animal Waiting List is empty\n");
					return;
				}
				else
				{
					fprintf(output, "The Animal in the Waiting list are:\n");
					sortList(&nodeHead, curr->waitingList, animalWaitNum);//sort waiting list
					printAnimalList(nodeHead, output);//print
					return;
				}
			}
		}
		curr = curr->Next;
	}
	fprintf(output, "Print Type Details: Type dosent exist\n", typeName);
	fprintf(stderr, "Print Type Details: Type dosent exist\n");
}