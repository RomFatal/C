#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

typedef void*  Element;

typedef struct vector_t* vector;

typedef enum { fail, success } Result;


typedef void(*print_type)(vector);

typedef void(*free_type)(vector);

Result vector_init(vector* v, int size, print_type print, free_type free); //initialize the vector

int vector_length(vector v); //get the length (element count) of the vector.

vector vector_set(int size, print_type print, free_type free); //set an element at said address.

Element vector_get(vector v, int index); //get an element from the vector.

void vector_delete(vector v, int index); //delete an element from the vector

void vector_free(vector v); //free a vector and its contents.

void vector_print(vector v); //print the vector.

Result vector_resize(vector v, int size); //resize a vector.

Result vector_insert(vector v, Element data);

void print_vec(vector v);

#endif