#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

typedef struct
{
	char* id;
	char* name;
	double wight;
	int age;
	struct Animal_Item* Next;
}Animal_Item;

typedef struct
{
	char* typeName;
	int placesAllowed;
	Animal_Item* animalList;
	Animal_Ite* waitingList;
	struct Animal_Type* Next;
}Animal_Type;

typedef struct nodeItem {
	Animal_Item* val;
	struct nodeItem *Next;
} nodeItem;

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

int checkAvailabilityAnimal(Animal_Type* animalType, char* compare) //checking if the Animal ID already exist return 0 if alreday exist
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

int checkID(Animal_Type* animalType,char* id)//check if id exsist return 0 if not
{
	Animal_Type head = *animalType;

	while (head.animalList!=NULL)
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

void getDatatype(char* line, char* typeName, int* place) 
{
	int j=0,i = 2,size;//i=character counter in Array, he start from third character:(skip on action & ,)
	char placeC[25];
	while (line[i] != ',' )//get typeName
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
		*place = *place + (placeC[j-1] - '0')*pow(10, i);
		i++;
		j--;
	}
}

void getDataAnimal(char* line, char* typeName, char* id, char* animalName ,int* wight , int* age)
{
	int j = 0, i = 2, size,c;//i=character counter in Array, he start from third character:(skip on action & ,)
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

void moveFromWaitingList( Animal_Item** animalHead, Animal_Item** waitingHead)
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

void sortList(nodeItem** nodeList, Animal_Item *head, int size)
{
	Animal_Item *currItem = head, *tmp;
	nodeItem   *nodeHead = *nodeList, *curr, *newHead;

	if (head->Next == NULL)//is only 1 cell return
	{
		nodeHead = (nodeItem *)malloc(1 * sizeof(nodeItem));
		nodeHead->val = currItem;
		nodeHead->Next=NULL;
		(*nodeList) = nodeHead;
		return;
	}


	

	//(*nodeList) = nodeHead;
	while (size!=0)//copy List
	{
		newHead = (nodeItem *)malloc(1 * sizeof(nodeItem));//Allocate
		newHead->val = currItem;
		if (nodeHead == NULL)
			newHead->Next = NULL;
		else
		{
			newHead->Next= nodeHead;
		}
		nodeHead = newHead;
		currItem = currItem->Next;
		size--;
	}

	  (*nodeList)=nodeHead;
	while (nodeHead != NULL)
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

	while (*typeList!=NULL)
	{
		//freeAnimalList((*typeList)->animalList);
		//freeAnimalList((*typeList)->waitingList);
		typeToFree = (*typeList);
		(*typeList) = (*typeList)->Next;
		//free(&typeToFree->typeName);
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

void addType(Animal_Type **head, char* line,FILE* output)//adding new type of animal
{
	int size,place=0;
	char typeName[25];
	Animal_Type* new_type,*curr;

	getDatatype(line, typeName, &place);

	if (checkTypeExist(*head, typeName) == 0)//if type not exist
	{
		new_type = (Animal_Type *)malloc(1 * sizeof(Animal_Type));//Allocate
		if (new_type == NULL)
		{
			fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
				return;
		}

		size = strlen(typeName);
		new_type->typeName = (char *)malloc(size * sizeof(char));
		if (new_type->typeName == NULL)
		{
			fprintf(output, "Add a new Type to the Zoo: Faild, Out of memory\n");
			return;
		}

		strcpy(new_type->typeName, typeName);
		new_type->placesAllowed = place;
		new_type->animalList = NULL;
		new_type->waitingList = NULL;

		if (*head == NULL)
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
	}
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

void removeType(Animal_Type **head, char* line, FILE* output)
{
	int i = 2;
	char typeName[25];
	Animal_Type *curr = *head, *prev= *head;

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
						moveFromWaitingList( &typeCurr->animalList, &typeCurr->waitingList);
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

void printType(Animal_Type* head, char* line, FILE* output)//
{
	int i = 2, animalNum=0, animalWaitNum=0;
	char typeName[25];
	Animal_Type *curr = head, *prev = head;
	Animal_Item *AnimalHead, *waitnigHead;
	nodeItem* nodeHead=NULL;

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
				sortList(&nodeHead, curr->animalList, animalNum);
				printAnimalList(nodeHead, output);

				if (curr->waitingList == NULL)
				{
					fprintf(output, "The Animal Waiting List is empty\n");
					return;
				}
				else
				{
					fprintf(output, "The Animal in the Waiting list are:\n");
					sortList(&nodeHead, curr->waitingList, animalWaitNum);
					printAnimalList(nodeHead, output);
					return;
				}
			}
		}
		curr = curr->Next;
	}
	fprintf(output, "Print Type Details: Type dosent exist\n", typeName);
	fprintf(stderr, "Print Type Details: Type dosent exist\n");
}

int main(int argc, char* argv[])
{
	int action = 0;
	Animal_Type* animalType = NULL;
	Animal_Item* animalitem = NULL;
	FILE *database, *output;
	char line[256] = "\0", r;

	if (argc != 3) {//get one txt file
		printf("Error");
		exit(1);
	}

	if (argv[1] == NULL && argv[2] == NULL) {
		printf("Error");
		exit(1);
	}

	database = fopen(argv[1], "r");//open file
	output = fopen(argv[2], "w");//open file

nextLine: while (fscanf(database, "%[^\n]s", line) != EOF)//read a Full line
{
	fscanf(database, "%c", &r);//prepae next reading read /n 
	if (line[0] == '#' || line[0] == '\n')
		goto nextLine;

	action = line[0] - '0';//get action NUM
	if (action >= 1 && action <= 5)//Menu
	{
		switch (action)
		{
		case 1:
			addType(&animalType, line, output);
			break;
		case 2:
			removeType(&animalType, line, output);
			break;
		case 3:
			addAnimal(&animalType, &animalitem, line, output);
			break;
		case 4:
			removeAnimal(&animalType, &animalitem, line, output);
			break;
		case 5:
			printType(animalType, line, output);
			break;
		}
	}
	else
		printf("Not a vaild cohis try again\n");
	action = 0;
}
		  to_free(&animalType);
		  printf("Thank you and hope you enjoyed our service\n");
		  fprintf(output, "Thank you and hope you enjoyed our service!!!\n");
		  return 0;
}
