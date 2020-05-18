#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "interface.h"
#define mux_col 5
#define mux_char 25


typedef struct col
{
	char* col_data;
	struct col* next_colmun;
}col;

typedef struct line
{
	struct col* col_head;
	struct line* next_line;
}line;

typedef struct chart
{
	struct line* line_head;
	FILE* file;
	int line_num;
	int colmun_num;
	char* file_name;
	char* chart_name;
}chart;//chart

//removing a used chars
void removed_dirty_char(char* line)
{
	int i = 0, j = 0, size = strlen(line);
	char tmp;

	while (line[0] != ','&&line[0] != ':'&&line[0] != '\0')
	{
		while (j != size)
		{
			line[j] = line[j + 1];
			j++;
		}
		j = 0;
		size--;
	}

	while (j != size)
	{
		line[j] = line[j + 1];
		j++;
	}

}
//get data from File
int get_data(FILE* data, int* colnumber, char* table_name, char* col_data[mux_col])
{
	char *col_ptr, line[256] = { '\n' }, c, new_col[mux_char];
	int i = 0, size, Eof = 1;

	if (fscanf(data, "%[^\n]s", line) == EOF)//prepae next reading read 
		Eof = 0;

	while (Eof && (line[0] == '#' || line[0] == '\n'))
	{
		if (fscanf(data, "%c", &c) == EOF)//prepae next reading read /n ) == EOF)
			Eof = 0;
		fscanf(data, "%[^\n]s", line);//prepae next reading read 
	}

	if (Eof == 0)
		return NULL;


	if (table_name != NULL)//read only if this the first line in file
	{
		sscanf(line, " %[^:]", new_col);
		strcpy(table_name, new_col);
		removed_dirty_char(line);
	}

	while (line[0] != '\0')//get all colmun data
	{

		sscanf(line, " %[^,]", new_col);
		size = strlen(new_col);
		col_ptr = (char*)malloc(size * sizeof(char));
		if (col_ptr == NULL)
		{
			printf("Faild to Allocate\n");
			return NULL;
		}
		strcpy(col_ptr, new_col);
		col_data[i] = col_ptr;
		removed_dirty_char(line);
		i++;
		if (colnumber != NULL)
			(*colnumber)++;
	}

}
//get data from line
int get_data_line(char *line, int colnumber, char* col_data[mux_col])
{
	char *col_ptr = { '\n' }, new_col[mux_char];
	int i = 0, size;

	while (i != colnumber)//get all colmun data
	{
		sscanf(line, " %[^,]", new_col);
		col_ptr = strdup(new_col);
		if (col_ptr == NULL)
		{
			printf("Faild to Allocate\n");
			return NULL;
		}
		col_data[i] = col_ptr;
		removed_dirty_char(line);
		i++;
	}

	return col_ptr;

}
//print chart
void print_chart(chart* chart_head)
{
	int i = 0, j = 0, chois;
	line* curr_line = (line*)chart_head->line_head;
	col* curr_col;
	char c[2];

		do
		{
			printf("Enter the number of muximum print line (1-20):\n");
			scanf("%d", &chois);
		} while (chois > 20 || chois < 0);


	curr_col = curr_line->col_head;
	printf("Chart Name: %s\n", chart_head->chart_name);
	while (curr_col != NULL)//print the type of colmun wite sparation
	{
		printf("%-*s",mux_char-10, curr_col->col_data);
		curr_col = curr_col->next_colmun;
	}
	printf("\n");
	curr_line = curr_line->next_line;
	while (i < (chart_head->colmun_num * (mux_char - 10)))
	{
		printf("=");
		i++;
	}
	printf("\n");

	i = 1;
	while (c[0] != 'q')//print until end in bath of 20 line press any key to continue to print or q to finis
	{
		while (curr_line != NULL && j < chois)
		{

			curr_col = curr_line->col_head;
			printf("%d.", i);
			while (curr_col != NULL)
			{
				printf("%-*s", mux_char - 10, curr_col->col_data);
				curr_col = curr_col->next_colmun;
			}
			printf("\n");
			curr_line = curr_line->next_line;
			i++;
			j++;
		}
		if (curr_line == NULL)
			c[0] = 'q';
		else
		{
			printf("enter q to exit or any other key to continue: ");
			scanf("%s", c);
			j = 0;
		}
	}
	printf("\n");

}
//add 1 col
col* add_col(void* head, char* col, struct col** curr)
{
	int size;
	struct col *new_col;

	new_col = (struct col*)malloc(1 * sizeof(struct col));
	if (new_col == NULL)
	{
		printf("Faild to Allocate\n");
		return NULL;
	}
	size = strlen(col);
	new_col->col_data = (char*)malloc((size + 1) * sizeof(char));
	if (new_col->col_data == NULL)
	{
		printf("Faild to Allocate\n");
		return NULL;
	}
	strcpy(new_col->col_data, col);

	if (*curr == NULL)
		new_col->next_colmun = NULL;
	else
		new_col->next_colmun = *curr;

	*curr = new_col;


	return new_col;
}
//add line of data for a chart with 5 colmun
col* add_line(void* head, char** col_data, int colnumber)
{
	col *curr = NULL;
	while (colnumber != 0)
	{
		head = add_col(head, col_data[colnumber - 1], &curr);
		colnumber--;
	}
	return head;
}
//add line in use of user
void usher_add_line(chart* chart_head)//ללבדוק שלא צריך להחזיר שורה
{
	char *col_data[mux_col], line[256];
	struct line* new_line, hea, *new_head;

	printf("Add Line Center: pleas enter a line with: *%d* colmun with ',' between: ", chart_head->colmun_num);
	scanf("%s", line);
	get_data_line(line, chart_head->colmun_num, col_data);

	new_line = (struct line*)malloc(1 * sizeof(struct line));//allocat line
	if (chart_head->line_head == NULL)
	{
		printf("Faild to Allocate\n");
		return;
	}

	new_head = chart_head->line_head;
	new_head = new_head->next_line;//first cell of data
	new_line->col_head = add_line(chart_head->line_head, col_data, chart_head->colmun_num);
	chart_head->line_num++;

	new_line->next_line = new_head;
	chart_head->line_head->next_line = new_line;
}
//allocat & copy all Line data in a linkind list
void create_line(chart* chart_head, FILE* data, char** col_data, int colnumber)
{
	int Eof = 1;
	col* new_col;
	line* tail, *new_line;
	char line[256] = { '\n' }, c;

	chart_head->line_head = (struct line*)malloc(1 * sizeof(struct line));//allocat line
	if (chart_head->line_head == NULL)
	{
		printf("Faild to Allocate\n");
		return NULL;
	}
	chart_head->line_head->col_head = add_line(chart_head->line_head, col_data, colnumber);
	chart_head->line_head->next_line = NULL;
	chart_head->line_num = 1;
	tail = chart_head->line_head;//get head

	do//read a Full line until EOF
	{

		Eof = get_data(data, NULL, NULL, col_data);
		if (Eof)
		{
			new_line = (struct line*)malloc(1 * sizeof(struct line));//create next line
			if (new_line == NULL)
			{
				printf("Faild to Allocate\n");
				return NULL;
			}
			new_line->col_head = add_line(chart_head->line_head, col_data, colnumber);
			new_line->next_line = NULL;
			while (tail->next_line != NULL)
				tail = tail->next_line;

			tail->next_line = new_line;

			chart_head->line_num++;
			line[0] = '\n';
		}
	} while (Eof != 0);
}
//create a new chart in a linkind list
chart* create_new_chart(char *file_name)
{
	int colnumber = 0, size, eof = 1;
	char table_name[mux_char], c, *col_data[mux_col];
	chart* new_chart;
	FILE *data;
	
	data = fopen(file_name, "r");//open file
	if (data == NULL)
	{
		printf("The file cold not be open\n");
		return NULL;
	}
	get_data(data, &colnumber, table_name, col_data);

	new_chart = (struct chart*)malloc(1 * sizeof(struct chart));//alocate chart
	if (new_chart == NULL)
	{
		printf("Faild to Allocate\n");
		return NULL;
	}
	new_chart->file = data;
	new_chart->line_head = NULL;
	new_chart->colmun_num = colnumber;
	new_chart->chart_name = strdup(table_name);
	new_chart->file_name = strdup(file_name);
	create_line(new_chart, data, col_data, colnumber);

	return new_chart;
}
//serch for item return a new list with relvent item
line* search(chart* chart_head)
{
	int j = 1, i = 0, size;
	line* curr_line = (line*)chart_head->line_head, *node_curr, *line_tmp, *new_node = NULL, *node_head = NULL;
	col* curr_col, *col_head;
	char search_word[mux_char];
	printf("Enter a word to search for:\n");
	scanf("%s", search_word);

	curr_col = curr_line->col_head;
	while (curr_col != NULL)//print colmun type with spartaion ==
	{
		printf("%-15s", curr_col->col_data);
		curr_col = curr_col->next_colmun;
	}
	printf("\n");
	curr_line = curr_line->next_line;

	while (i < (chart_head->colmun_num * 14))
	{
		printf("=");
		i++;
	}
	printf("\n");

	curr_line = (line*)chart_head->line_head->next_line;
	while (curr_line != NULL)//crearing a new list that match to search
	{
		curr_col = curr_line->col_head;
		while (curr_col != NULL)
		{
			col_head = curr_line->col_head;
			if (strcmp(curr_col->col_data, search_word) == 0)//if find a match creating a new line
			{

				new_node = (line*)malloc(1 * sizeof(line));
				if (new_node == NULL)
				{
					printf("Faild to Allocate\n");
					return NULL;
				}
				new_node->col_head = &col_head->col_data;
				if (node_head == NULL)
					new_node->next_line = NULL;
				else
					new_node->next_line = node_head;
				printf("%d.", j);

				while (col_head != NULL)
				{

					printf("%-15s", col_head->col_data);
					col_head = col_head->next_colmun;
					
				}
				j++;
				printf("\n");
				goto nextline;
			}
			curr_col = curr_col->next_colmun;//pass to next col
		}
		printf("\n");
	nextline:curr_line = curr_line->next_line;//pass to next cell
	}
	node_head = new_node;
	node_curr = new_node;
	if (node_head == NULL)
	{
		printf("Reslt Number:0 The requested word dosent exist!\n");
		return NULL;
	}
	if ((j - 1) != 1)//if more than one result show all resualt and chos line
	{
		if (node_curr != NULL)
		{
			printf("Enter a requested line number:\n");
			scanf("%d", &j);
		}

		for (int count = 1; count < j; i++)
		{
			node_curr = node_curr->next_line;
		}
	}
	printf("\nLine has found!!\n");
	return node_head;
}
//update a col in line
void update_line(chart* chart_head)
{
	int i = 0, chois;
	col* curr = chart_head->line_head->col_head, *tmp;
	line* node_head, *curr_node;
	char new_char[mux_char];
	printf("Update center: you are moving to seraching items\n");
	node_head = search(chart_head);
	if (node_head != NULL)//if find items
	{
		tmp = node_head->col_head;

		while (node_head->col_head != NULL)//print chart colmun type
		{
			printf("%d.%-15s", i + 1, node_head->col_head->col_data);
			node_head->col_head = node_head->col_head->next_colmun;
			i++;
		}
		printf("\nEnter the numer of colmunt that you are want to change:\n");
		scanf("%d", &chois);

		node_head->col_head = tmp;
		while (chois - 1 != 0)//count colmun
		{
			tmp = tmp->next_colmun;
			chois--;
		}

		printf("Entrer a New string to updating:\n");//get new string to update
		scanf("%s", new_char);

		strcpy(tmp->col_data, new_char);

		while (node_head != NULL)////free temp node list
		{
			curr_node = node_head;
			node_head = node_head->next_line;
			free(curr_node);
		}
		printf("Updat Sucsed\n");
	}
	else
		printf("Updat Faild\n");
}
//delet a line
void delet_line(chart* chart_head)
{
	int chois = 1;
	line* node_head, *curr_node, *curr_line = chart_head->line_head, *pre = NULL;
	chart node_chart;
	char new_char[mux_char];

	printf("Delet Center: you are moving to seraching items\n");
	node_head = search(chart_head);
	curr_node = node_head;

	if (node_head != NULL)////if find items
	{
		if (node_head->next_line != NULL)//if more than one result
		{
			printf("\nEnter the numer of Line that you are want to Delet:\n");
			scanf("%d", &chois);
		}

		while (curr_line->col_head != curr_node->col_head)//find the requested line in the chart
		{
			pre = curr_line;
			curr_line = curr_line->next_line;
		}

		if (chart_head->line_head == curr_node)//if first cell
		{
			pre = chart_head->line_head;
			chart_head->line_head = chart_head->line_head->next_line;
			free(pre);
		}
		else
		{
			pre->next_line = curr_line->next_line;
			free(curr_line);
		}

		while (node_head != NULL)////free temp node list
		{
			curr_node = node_head;
			node_head = node_head->next_line;
			free(curr_node);
		}
		printf("Delet Sucsed\n");
	}
	else
		printf("Delet Faild\n");
}
//help to sort function
line* sort_help(chart* chart_head, int chois, int direction)
{
	int i = 1;
	line *curr_line , *pre, *new_line_head, *line_head = chart_head->line_head,*tmp,*tmp2,*pre_curr_line;
	col* col_curr, *col_head;

	pre = line_head;
	line_head = chart_head->line_head->next_line;//skip type

	while (line_head->next_line != NULL)//crearing a new list that match to search
	{
		new_line_head = line_head;
		curr_line = line_head->next_line;
		while (curr_line != NULL)
		{
			col_head = new_line_head->col_head;
			col_curr = curr_line->col_head;
			for (; i < chois; i++)
			{
				col_head = col_head->next_colmun;
				col_curr = col_curr->next_colmun;
			}
			if (direction == 1)//if up
				if (strcmp(col_head->col_data, col_curr->col_data) > 0)
				{
					if (new_line_head->next_line == curr_line)//if switch
					{
						tmp = curr_line->next_line;
						pre_curr_line = new_line_head;
						pre->next_line = curr_line;
						curr_line->next_line = new_line_head;
						new_line_head->next_line = tmp;
						new_line_head = pre->next_line;
						curr_line = tmp;
					}
					else//if  replaced
					{
						tmp = new_line_head->next_line;
						tmp2 = curr_line->next_line;
						pre->next_line = curr_line;
						curr_line->next_line = tmp;
						new_line_head->next_line = tmp2;
						curr_line = new_line_head->next_line;
						pre_curr_line->next_line = new_line_head;
						pre_curr_line = new_line_head;
						new_line_head = pre->next_line;
					}
				}
				else
					curr_line = curr_line->next_line;
			else
			if (strcmp(col_head->col_data, col_curr->col_data) < 0)
			{
				if (new_line_head->next_line == curr_line)//if switch
				{
					tmp = curr_line->next_line;
					pre_curr_line = new_line_head;
					pre->next_line = curr_line;
					curr_line->next_line = new_line_head;
					new_line_head->next_line = tmp;
					new_line_head = pre->next_line;
					curr_line = tmp;
				}
				else//if  replaced
				{
					tmp = new_line_head->next_line;
					tmp2 = curr_line->next_line;
					pre->next_line = curr_line;
					curr_line->next_line = tmp;
					new_line_head->next_line = tmp2;
					curr_line = new_line_head->next_line;
					pre_curr_line->next_line = new_line_head;
					pre_curr_line = new_line_head;
					new_line_head = pre->next_line;
				}
			}
			else
				curr_line = curr_line->next_line;
		}
		pre = pre->next_line;
		line_head = pre->next_line;
	}
	return chart_head->line_head;
}
//sort chart by col
void sort(chart* chart_head)
{
	int i = 0;
	line* node_head, *curr_node;
	int chois, direction;
	printf("Sort Center: pleas chose colmun to sort by (1-%d):\n", chart_head->colmun_num);
	scanf("%d", &chois);
	printf("chose derction 1->'A-Z' 2->'Z-A':\n");
	scanf("%d", &direction);


	sort_help(chart_head, chois, direction);
	chart_head->line_head;

	if (chart_head->line_head != NULL)//if find items
	{
		printf("sort Sucsed\n");
	}
	else
		printf("Faild list is empty\n");
}
//use the 
void print_to_file(chart* chart_head)
{
	int i = 0, j = 0, chois;
	line* curr_line = (line*)chart_head->line_head;
	col* curr_col;

	curr_col = curr_line->col_head;

	while (curr_col != NULL)//print the type of colmun wite sparation
	{
		fprintf(chart_head->file,"%-*s", mux_char - 10, curr_col->col_data);
		curr_col = curr_col->next_colmun;
	}
	fprintf(chart_head->file, "\n");
	curr_line = curr_line->next_line;
	while (i < (chart_head->colmun_num * (mux_char - 10)))
	{
		fprintf(chart_head->file, "=");
		i++;
	}
	fprintf(chart_head->file, "\n");

	i = 1;

		while (curr_line != NULL )
		{

			curr_col = curr_line->col_head;
			fprintf(chart_head->file, "%d.", i);
			while (curr_col != NULL)
			{
				fprintf(chart_head->file, "%-*s", mux_char - 10, curr_col->col_data);
				curr_col = curr_col->next_colmun;
			}
			fprintf(chart_head->file, "\n");
			curr_line = curr_line->next_line;
			i++;
		}
	fprintf(chart_head->file, "\n");

}
//save currect file and get a new file to open a new chart
chart* load_save(chart* head)
{
	int chois=1;
	chart *new_head;
	char file_name[mux_char];
	FILE* data;
	head->file = fopen(head->file_name, "w");
	print_to_file(head);
	close(head);
	printf("Saved!!!\n");

	while (chois == 1)
	{
		printf("Pleas Enter the Name of the New File you want to Load:\n");
		snprintf(file_name, mux_char, "%s.txt", file_name);
		scanf("%s", file_name);

		new_head = create_new_chart(file_name);
		
		if (new_head != NULL)
		{
			printf("New chart has Loded!!!\n");
			return new_head;
		}
		else
		{
			printf("The file cold not be found options:\n1.Try diffrent file name 2.Add a new chart 3.Exit\n");
			scanf("%d", &chois);
		}
	}
	if (chois == 2)
	{
		new_head = add_new_chart;
		return new_head;
	}
	return NULL;
}
//save currect file and get a new chart from manger input
chart* add_new_chart(chart* chart_head)
{
	int colnumber;
	char line[256], *col_data[mux_col], tmp[mux_char];
	chart *new_chart;
	
	chart_head->file = fopen(chart_head->file_name, "w");
	close(chart_head);

	new_chart = (struct chart*)malloc(1 * sizeof(struct chart));//alocate chart
	printf("Enter the chart name:  ");
	scanf("%s", tmp);
	printf("Enter number of colmun: ");
	scanf("%d", &colnumber);
	new_chart->chart_name = strdup(tmp);
	printf("outfile name that you want to creat: ");
	scanf("%s", tmp);
	new_chart->file_name = strdup(tmp);
	snprintf(tmp, mux_char, "%s.txt", tmp);
	new_chart->file = fopen(tmp,"w");//open file;
	printf("pleas enter a line with:%d colmun with ',' between: ", colnumber);
	scanf("%s", line);
	new_chart->line_head = NULL;
	new_chart->colmun_num = colnumber;
	get_data_line(line, colnumber, col_data);
	new_chart->line_head = (struct line*)malloc(1 * sizeof(struct line));//allocat line
	if (new_chart->line_head == NULL)
	{
		printf("Faild to Allocate\n");
		return NULL;
	}
	new_chart->line_head->col_head = add_line(chart_head->line_head, col_data, colnumber);
	new_chart->line_head->next_line = NULL;
	new_chart->line_num = 1;
	add_line(new_chart->line_head, col_data, colnumber);

	return new_chart;


}
//add or remove colmun
void update_structer(chart* chart_head)
{
	int i = 0,chois;
	col *curr = chart_head->line_head->col_head,*pre=NULL,*new_col,*tmp;
	char col_name[mux_char];
	printf("Update Structer Center:you want to add or delet colmun: 1.Add 2.Delet: ");
	scanf("%d", &chois);

	if (chart_head->line_head->next_line == NULL)
	{
		if (chois != 1)//delet
		{
			printf("Wich colmun you want to delet (1-%d)\n", chart_head->colmun_num);
			while (chart_head->colmun_num > i)//count colmun//print colmun
			{
				printf("%d.%s ",i+1, curr->col_data);
				curr = curr->next_colmun;
				i++;
			}
			printf("\n");
			scanf("%d", &chois);
			curr = chart_head->line_head->col_head;
			i = 0;
			for (; i+1 < chois; i++)//get curr colmun
			{
				pre = curr;
				curr = curr->next_colmun;
			}
			if (pre == NULL)
			{
				chart_head->line_head->col_head = chart_head->line_head->col_head->next_colmun;
				free(curr);
			}
			else
			{
				pre->next_colmun = curr->next_colmun;
				free(curr);
			}
			chart_head->colmun_num--;
			printf("Chart has Update sucssfuly\n");
			return;
		}
		else//add
		{
			if (chart_head->colmun_num != 5)
			{
				printf("Enter the name of the new colmun: ");
				scanf("%s", col_name);
				new_col = (col*)malloc(1 * sizeof(struct col));
				new_col->col_data = strdup(col_name);

				printf("were to put colmun(1-%d): \n", chart_head->colmun_num+1);
				while (chart_head->colmun_num < i)//count colmun
				{
					printf("%d.%s ", i, curr->col_data);
					curr = curr->next_colmun;
					i++;
				}
				scanf("%d", &chois);
				curr = chart_head->line_head->col_head;
				i = 0;
				for (; i+1 < chois; i++)
				{
					pre = curr;
					curr = curr->next_colmun;
				}
				if (pre == NULL)
				{
					tmp = chart_head->line_head->col_head;
					chart_head->line_head->col_head = new_col;
					new_col->next_colmun = tmp;
				}
				else
				{
					tmp = pre->next_colmun;
					pre->next_colmun = new_col;
					new_col->next_colmun = tmp;
				}
				chart_head->colmun_num++;
				printf("Chart has Update sucssfuly\n");
				return;
			}
			else
			{
				printf("Faild the chart is FULL");
				return;
			}

		}
	}
	else
		printf("Faild the chart is Not empty\n");

}
//close all file anf free memory
void close(chart* chart_head)
{
	line* line_to_free;
	col* col_to_free;
	chart_head->file = fopen(chart_head->file_name, "w");
	print_to_file(chart_head);
		while (chart_head->line_head != NULL)
		{
			while (chart_head->line_head->col_head == NULL)
			{
				col_to_free = chart_head->line_head->col_head;
				chart_head->line_head->col_head = chart_head->line_head->col_head->next_colmun;
				free(col_to_free->col_data);
				free(col_to_free);
			}
			line_to_free = chart_head->line_head;
			chart_head->line_head = chart_head->line_head->next_line;
			free(line_to_free->col_head);
		}
		free(chart_head->chart_name);
		free(chart_head->file_name);
		fclose(chart_head->file);
		free(chart_head);

}