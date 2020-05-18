//presenter by ROM FATAL
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NumberOfCustomer = 0;
const int startsize = 16;

typedef struct
{
	char* Id;
	char* FirstName;
	char* LastName;
	char* BankName;
	float Balance;


}BankCustomer;

int get1Customer(FILE* database, BankCustomer* C, int i, char character)//getting only one customer
{
	int size = 0;
	char temp[30];//Temp string 

	do {//get id
		temp[size] = character;//temp = name
		fscanf(database, "%c", &character);
		size++;
	} while (character != '|');
	temp[size] = '\0';
	size++;
	C[i].Id = (char *)malloc(size * sizeof(char));
	if (C[i].Id == NULL)
	{
		printf("Out of memory\n");
		return 1;
	}
	for (int j = 0; j < size; j++)
		C[i].Id[j] = temp[j];

	size = 0;
	fscanf(database, "%c", &character);//get name
	do {
		temp[size] = character;// temp=name
		fscanf(database, "%c", &character);
		size++;
	} while (character != '|');
	temp[size] = '\0';
	size++;
	C[i].FirstName = (char *)malloc(size * sizeof(char));
	if (C[i].FirstName == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	for (int j = 0; j < size; j++)
		C[i].FirstName[j] = temp[j];

	size = 0;
	fscanf(database, "%c", &character);//get last name
	do {
		temp[size] = character;//temp=last name
		fscanf(database, "%c", &character);
		size++;
	} while (character != '|');
	temp[size] = '\0';
	size++;
	C[i].LastName = (char *)malloc(size * sizeof(char));
	if (C[i].LastName == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}
	for (int j = 0; j < size; j++)
		C[i].LastName[j] = temp[j];

	size = 0;
	fscanf(database, "%c", &character);//get bank name
	do {
		temp[size] = character;//temp=bank
		fscanf(database, "%c", &character);
		size++;
	} while (character != '|');
	temp[size] = '\0';
	size++;
	C[i].BankName = (char *)malloc(size * sizeof(char));
	if (C[i].BankName == NULL)
	{
		printf("Out of memory\n");
		return 1;
	}
	for (int j = 0; j < size; j++)
		C[i].BankName[j] = temp[j];

	fscanf(database, "%f", &C[i].Balance);//get balance
	return 0;
}

BankCustomer* GetAllCustomer(FILE* database) //getting all cusotmers
{
	char lastcharacter = 0;
	BankCustomer* C;


	fscanf(database, "%c", &lastcharacter);//get first digit
	while (lastcharacter == '#' || lastcharacter == '/n')//chacking if get a vaild line
	{
		fscanf(database, "%*[^\n]\n", NULL);//if empty line skip a line
		fscanf(database, "%c", &lastcharacter);//get next chracter
	}

	C = (BankCustomer *)malloc(startsize * sizeof(BankCustomer));//getting first customer
	if (C == NULL)
	{
		printf("Out of memory\n");
		return 0;
	}


	do {

		if (NumberOfCustomer >= startsize)//If the first memory allocation size full do reallocation
		{
			C = (BankCustomer *)realloc(C, (NumberOfCustomer + 1) * sizeof(BankCustomer));
			if (C == NULL)
			{
				printf("Out of memory\n");
				return 0;
			}
		}
		get1Customer(database, C, NumberOfCustomer, lastcharacter);

		fscanf(database, "%c", &lastcharacter);//go to next \n
		NumberOfCustomer++;
	} while (fscanf(database, "%c", &lastcharacter) != EOF);//do if its not end of file and you need to  
	return C;
}

void PrintCustomer(BankCustomer C)// Print Customer Details 
{
	printf("This is yours detials\n");
	printf("Id:%s | FirstName:%s | LastName:%s | BankName:%s | Balance:%3.f\n", C.Id, C.FirstName, C.LastName, C.BankName, C.Balance);
	printf("Hope you enjoy.. return to the main menu\n");
}  

void Withrawal(float* Balance) //Withrawal money
{
	float amount;
	printf("Enter the amount you want to withdraw:\n");
	scanf("%f", &amount);
	if (amount < *Balance) {
		*Balance -= amount;
		printf("Successed to Withrawal %3.f $ from your acount\nHope you enjoy.. return to the main menu\n", amount);
	}
	else
		printf("There is not enough money in the account return to the main menu\n");
}

void Deposit(float* Balance)//Deposit money 
{
	float amount;
	printf("Enter the amount you want to Deposit:\n");
	scanf("%f", &amount);
	if (amount>0) {
		*Balance += amount;
		printf("Successed to Deposit %3.f $ to your acount\nHope you enjoy.. return to the main menu\n", amount);
	}
	else
		printf("Faild to Deposit nagtive number account return to the main menu\n");
}

int Transference(BankCustomer* C, int customernumber)  //Transference money
{
	int Verificationcheck = 1, chois, i;
	float amount;
	char id[30];

	do {
		printf("Enter the ID of the account to which you want to transfer the money: \n");
		scanf("%s", &id);
		for (i = 0; i < NumberOfCustomer; i++)//serach customer
		{
			Verificationcheck = strcmp(id, C[i].Id);//check pass match

			if (Verificationcheck == 0)
			{
				printf("Enter the amount you want to Transference:\n");
				scanf("%f", &amount);
				if (amount < C[customernumber].Balance && amount > 0)
				{
					printf("Successed amount of **%3.f$** was Transference\n", amount);
					C[customernumber].Balance -= amount;
					C[i].Balance += amount;
					goto nextaction;
				}
				else
				{
					printf("There is not enough money in the account.. return to the main menu...\n");
					return 0;
				}
			}

		}
		if (i == NumberOfCustomer)
		{
			printf("Not able to find the acount\n");
			return 1;
		}
	nextaction:printf("Would you like to do more actions: 1.Yes ** 2.No\n");
		scanf("%d", &chois);
	} while (chois != 2);
	printf("Thank you... return to the main menu\n");
	return 0;
}

void output(BankCustomer* C)//create output file
{
	int i;
	FILE* fp;
	fp = fopen("output.txt", "w");
	if (fp != NULL)
	{
		for (i = 0; i < NumberOfCustomer; i++)
		{
			fprintf(fp, "%s|%s|%s|%s|%3.f\n", C[i].Id, C[i].FirstName, C[i].LastName, C[i].BankName, C[i].Balance);
		}
		fprintf(fp, "presenter by ROM FATAL");
		fclose(fp);
	}
	else
		printf("Error writing to output file failed\n");
}

void freelist(BankCustomer* C) {
	int i;
	for (i = 0; i < NumberOfCustomer; i++) {
		free(C[i].Id);
		free(C[i].FirstName);
		free(C[i].LastName);
		free(C[i].BankName);
	}
	free(C);
}

int main()
{
	int CustomerChoise = 0;
	char Password[30];
	FILE *database;
	BankCustomer* C;//C=Customer

	database = fopen("simulationExample.txt", "r");

	if (database != NULL)//if success to read file
	{
		C = GetAllCustomer(database);//getting data base
		if (C == NULL)
			return 1;
		printf("Hello Please enter your account password or 'bye' to Exit: \n");
		scanf("%s", &Password);

		while (strcmp(Password, "bye") != 0)
		{
			for (int i = 0; i < NumberOfCustomer; i++)//serach customer
			{
				if (strcmp(Password, C[i].Id) == 0)//check pass match
				{
					printf("Successful verification - Hello %s\n",C[i].FirstName);
					while (CustomerChoise != 5)//main menu
					{
						printf("You have 5 options:\n1.Withrawal ** 2.Deposit ** 3.Transference ** 4.Print acount info ** 5.Log Out\n");
						scanf("%d", &CustomerChoise);
						if (CustomerChoise >= 1 && CustomerChoise <= 5)
						{
							switch (CustomerChoise)
							{
							case 1:
								Withrawal(&C[i].Balance);
								break;
							case 2:
								Deposit(&C[i].Balance);
								break;
							case 3:
								Transference(C, i);
								break;
							case 4:
								PrintCustomer(C[i]);
								break;
							case 5:
								goto nextC;//if logout, get next customer
							}
						}
						else
							printf("Not a vaild cohis try again\n");
					}
				}

			}
		nextC:printf("Please enter your account password or 'bye' to Exit: \n");
			scanf("%s", &Password);
			CustomerChoise = 0;
		}
		printf("Thank you and hope you enjoyed our service\n");
		output(C);
		freelist(C);
	}
	else { printf("Faild to read from database\n "); }
	return 0;
}