#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include <stdio.h>
#include "Type.h"

typedef struct Animal_Item 
{
	char* id;
	char* name;
	double wight;
	int age;
	struct Animal_Item* Next;
}Animal_Item;

/*Adding and allocate a new Animal and put himself in the requested type.
condision: The requested type exist, and there is not any other animal with the same ID
expects get double ptr of animal Type,double ptr of animal list, full line command from input ,file and ptr to output file*/
void addAnimal(struct Animal_Type** animalType, Animal_Item** head, char* line, FILE* output);

/*removing and free a Animal from the requested type.
condision: The requested type exist, and the requested ID already exist in the type.
expects get double ptr of animal Type,double ptr of animal list, full line command from input ,file and ptr to output file*/
void removeAnimal(struct Animal_Type** animalType, Animal_Item** head, char* line, FILE* output);

#endif