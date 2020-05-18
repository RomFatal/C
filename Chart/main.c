//Presented by ROM Fatal

#include <stdio.h>
#include <stdlib.h>
#include "interface.h"


int main(int argc, char* argv[])
{
	int action = 0, i;
	char file_name[25];
	chart* head = NULL;
	char line[256] = "\0", r;
	if (argc != 2) {//get one txt file
		printf("Error");
		exit(1);
	}

	if (argv[1] == NULL) {
		printf("Error");
		exit(1);
	}

	strcpy(file_name, argv[1]);
	head = create_new_chart(file_name);

	do
	{
	meanmenu:printf("Mean Menu: 1.Add Line 2.Update Line 3.Delet Line 4.Search 5.Sort 6.Print 7.Manager Menu 8.Exit\n");
		printf("Enter action number: ");
		scanf("%d", &action);

		switch (action)
		{
		case 1:
			usher_add_line(head);
			break;
		case 2:
			update_line(head);
			break;
		case 3:
			delet_line(head);
			break;
		case 4:
			search(head);
			break;
		case 5:
			sort(head);
			break;
		case 6:
			print_chart(head);
			break;
		case 7:
			goto managermenu;
		case 8:
			close(head);
			return;
			break;

		}

	} while (action != 8);


	do
	{
	managermenu:printf("Manager Menu: 1.Save And Load 2.Add New Chart 3.Update Chart Structers 4.Mean Menu 5.Close\n");
		printf("Enter action number: ");
		scanf("%d", &action);
		switch (action)
		{
		case 1:
			head = load_save(head);
			if (head == NULL)
				action = 4;
			break;
		case 2:
			head = add_new_chart(head);
			break;
		case 3:
			update_structer(head);
			break;
		case 4:
			goto meanmenu;
		case 5:
			close(head);
			return;
			break;
		}
	} while (action != 5);
	printf("Thank you Hope you are enjoyed from our services");
}