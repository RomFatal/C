#pragma once
#ifndef TYPE_H
#define TYPE_H

#include <stdio.h>
#include <math.h> 
#include "Animal.h"

typedef struct Animal_Type
{
	char* typeName;
	int placesAllowed;
	struct Animal_Item * animalList;
	struct Animal_Item * waitingList;
	struct Animal_Type* Next;
}Animal_Type;

/*Adding and allocate a new type of animal to the Zoo. if the type dosent exist .
expects get double ptr of animal list full line command from input file and ptr to output file*/
void addType(Animal_Type **head, char* line, FILE* output);

/*removing and free type from the Zoo. if the requested type exist .
expects get double ptr of animal list full line command from input file and ptr to output file*/
void removeType(Animal_Type **head, char* line, FILE* output);

/*print type details and all animal details in all types. if the requested type exist.
expects get ptr of animal list full line command from input file and ptr to output file*/
void printType(Animal_Type* head, char* line, FILE* output);


#endif