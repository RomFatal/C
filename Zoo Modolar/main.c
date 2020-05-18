#include <stdio.h>
#include "Animal.h"
#include "Type.h"

int main(int argc, char* argv[])
{
	int action = 0;
	Animal_Type* animalType = NULL;
	Animal_Item* animalitem = NULL;
	FILE *database, *output;
	char line[256] = "\0", r;

	if (argc != 3) {//get 2 txt file input and output
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
	fscanf(database, "%c", &r);//prepae next reading read after /n  character
	if (line[0] == '#' || line[0] == '\n')//if empty line go to next line
		goto nextLine;

	action = line[0] - '0';//get action convert from char to int
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
