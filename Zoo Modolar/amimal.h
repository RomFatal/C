#include <stdio.h>
#include "Type.h"


#ifndef ANIMAL_H
#define ANIMAL_H


typedef struct Animal_t
{
	char* id;
	char* name;
	double wight;
	int age;
	struct Animal_Item* Next;
}Animal_Item;



void addAnimal(Animal_Type** animalType, Animal_Item** head, char* line, FILE* output);

void removeAnimal(Animal_Type** animalType, Animal_Item** head, char* line, FILE* output);

#endif