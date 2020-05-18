#pragma once
#pragma once
#include <stdio.h>
#include "interface.c"

#ifndef DEFINE_H
#define DEFINE_H
/*exept from create all the function get chart_head as parmeter*/
typedef struct chart chart;
//get a file name and return pointer to chart if fails return NULL
chart* create_new_chart(char *file_name);
//save and close currect file, get a new chart from manger input
chart* add_new_chart(chart* chart_head);
/*serching for a line if find print all line colmun and let you chose
wich colmun do you want you update*/
void update_line(chart* chart_head);
//print all line and colmun in chart
void print_chart(chart* chart_head);
/*serching for a line if find print all line colmun and let you chose
wich colmun do you want you delet*/
void delet_line(chart* chart_head);
//add a line to the head of the chart, get the line data from user input
void usher_add_line(chart* chart_head);
//sort list by chosing colmun up or down
void sort(chart* chart_head);
//close the program,print open chart closing open file and free memory
void close(chart* chart_head);
/*update colmun in chart, you will be able to use this function only if the chart is empty
let you choosing if you want to add or delet colmun from chart*/
void update_structer(chart* chart_head);

#endif