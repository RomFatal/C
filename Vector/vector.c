#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


struct vector_t {
	Element* array;
	int curr_index;
	int max_capacity;
	print_type print;
	free_type free;
};


Result place_add_manager(vector v)//if need more capacity double the capacity
{
	if (v->curr_index == v->max_capacity)
	{
		v->max_capacity = v->max_capacity * 2;
		v->array = (Element*)realloc(v->array, v->max_capacity * sizeof(Element));
		if (v->array == NULL)
			return fail;
	}
	return success;
}

void place_delete_manager(vector v)//if index/capcity>=4 free half of memory
{
	float size;
	if (v->curr_index>0)
	{
		size = v->max_capacity / v->curr_index;

		if (size >= 4)
		{
			v->max_capacity = v->max_capacity / 2;
			v->array = (Element*)realloc(v->array, v->max_capacity * sizeof(Element));
			if (v->array == NULL)
				return NULL;
		}
	}
}

Result vector_init(vector* v, int size, print_type print, free_type free) //initialize the vector
{
	if (size <= 0) return fail;

	*v = (struct vector_t*)malloc(sizeof(struct vector_t));
	if (*v == NULL)
		return fail;
	(*v)->array = (Element*)malloc(size * sizeof(Element));
	if ((*v)->array == NULL)
	{
		free(*v);
		return fail;
	}
	(*v)->curr_index = 0;
	(*v)->max_capacity = size;
	(*v)->free = free;
	(*v)->print = print;
	return success;
}//add func instal

int vector_length(vector v) //get the length (element count) of the vector.
{
	return v->curr_index;
}

vector vector_set(int size, print_type print, free_type free) //set an element at said address.
{
	vector newVec;
	vector_init(&newVec,size, print, free);
	return newVec;
}

Element vector_get(vector v, int index) //get an element from the vector.
{
	return v->array[index-1];
}

void vector_delete(vector v, int index) //delete an element from the vector
{
	if (v->curr_index == 0)
		return;
	if (v->curr_index != 1)
		for (int i = index - 1; i < v->curr_index; i++)
		{
			v->array[i] = v->array[i + 1];
		}
	v->curr_index--;
	place_delete_manager(v);
}

void vector_free(vector v) //free a vector and its contents.
{
	for (int i = 0; i<v->curr_index; i++)
		v->free(v->array[i]);
	free(v->array);
	free(v);
}

void vector_print(vector v) //print the vector.
{
	printf("***Vector Start***\n"); 
	for (int i = 0; i < v->curr_index; i++)
	{
		printf("%d.",i+1);
		v->print(v->array[i]);
	}
	printf("***Vector End***\n");
}

Result vector_resize(vector v, int size) //resize a vector.
{
	if (size > v->curr_index)
	{
		v->array = (Element*)realloc(v->array, size * sizeof(Element));
		if (v->array == NULL)
			return fail;
	}
	else
	{
		printf("The number of elements is begar than the requsted size new size:%d\n",v->curr_index);
		v->array = (Element*)realloc(v->array, v->curr_index * sizeof(Element));
		if (v->array == NULL)
			return fail;
	}
	v->max_capacity = size;
	return success;
}

Result vector_insert(vector v, Element data)
{
	Result result =place_add_manager(v);
	if (result == fail) return result;
	v->array[v->curr_index] = data;
	v->curr_index++;
	return result;
}

Element vector_insert_int(vector v, Element data)
{
	int data_int = (int)data;
	v->array[v->curr_index] = data;

}

void print_vec(vector v)
{
	printf("Vector Size:%d Vector_capcity:%d\n", v->curr_index, v->max_capacity);
	for (int i = 0; i < v->curr_index; i++)
		v->print(v->array[i]);
}


