//Rom Fatal
#include <iostream>
#include <fstream>
#include "account.h"
using namespace std;

	ifstream cindata("dataBase.txt");
	ofstream coutdata("UpdatedDataBase.txt");

void getCustomers(ifstream& cindata, Account* &bank, int& accountnumber) {
	char name[50];
	int age;
	double balance;

	while (cindata >> name >> age >> balance) {//read data fron file

		Account *account = new Account[1]{ Account(name, age, balance) };//allocate account

		if (bank == NULL)
		{
			bank = new Account[1];
			bank[0] = *account;
		}
		else
		{
			Account* temp = bank;//copy old list
			bank = new Account[accountnumber + 1];//allocating new size of list
			for (int i = 0;  i < accountnumber; i++)//copy the old list to new list
				bank[i] = temp[i];
			bank[accountnumber] = *account;//saving new account in the list
		}
		accountnumber += 1;
	}
}

int main() {
	int accountnumber = 0;
	Account *bank = NULL;


	getCustomers(cindata, bank, accountnumber);
	//check the end cases in the following order: one successful one failed
	bank[9].deposit(100);
	bank[12].deposit(-150);
	bank[5].withdraw(-150);
	bank[4].withdraw(150);
	bank[1].transfer(bank[4], 400);
	bank[1].transfer(bank[4], -20);
	bank[3].transfer(bank[1], 800000);
	cout << "Age:" << bank[0].getAge() << endl;
	cout << "Name:" << bank[11].getName() << endl;
	cout << "Balance:" << bank[8].getBalance() << endl;
	bank[24].setAge(20);
	bank[32].setAge(-30);
	bank[6].setName("Rafi");
	bank[16].setName("");
	bank[29].setBalance(55555);
	for (int i = 0; i < accountnumber; i++)//print list to file UpdatedDataBase.txt
		bank[i].printDetails(coutdata);

}