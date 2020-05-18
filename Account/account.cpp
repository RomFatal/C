#include "account.h"
//Methods
bool Account::deposit(int amount){
	if (amount <= 0)
	{
		cout << "deposit Failed" << endl;
		return 0;
	}
		balance += amount;
		cout << "deposit succeeded" << endl;
	return 1;
}

bool Account::withdraw(int amount) {
	if (amount >= 0)
	{
		cout << "withdraw Failed" << endl;
		return 0;
	}
		balance -= amount;
	cout << "withdraw succeeded" << endl;
	return 1;
}

bool Account::transfer(Account& other, int amount) {
	if (amount <= 0 || balance < amount)
	{
		cout << "transfer Failed" << endl;
		return 0;
	}
		balance -= amount;
		other.balance += amount;
		cout << "transfer succeeded" << endl;
	return 1;
}

void Account::printDetails(ostream& os) const {
	os << "Name of account:" << name << "  Age:" << age << "  Balance:" << balance <<endl;
}

int Account::getAge() const {
	return this->age;
}

char* Account::getName() const {
	return this->name;
}

double Account::getBalance() const {
	return balance;
}

bool Account::setAge(const int newAge) {
	if (newAge <= 0 || newAge >= 200)
	{
		cout << "setAge Failed" << endl;
		return 0;
	}
	age = newAge;
	cout << "setAge succeeded" << endl;
	return 1;
}

bool Account::setName(const char* newName) {
	if (newName == "")
	{
		cout << "setName Failed" << endl;
		return 0;
	}
	strcpy(this->name, newName);
	cout << "setName succeeded" << endl;
	return 1;
}

bool Account::setBalance(const double newBalance) {
	balance = newBalance;
	cout << "setBalance succeeded" << endl;
	return 1;
}


Account::Account() {
}

Account::Account(const char* nameIn, int ageIn, double balanceIn) {
	age = ageIn;
	name = strdup(nameIn);
	balance = balanceIn;
	return;
}

Account::~Account() {
	delete [] name;
	return;
}


