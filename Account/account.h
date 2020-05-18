#pragma once
#include <iostream>
using namespace std;

class Account
{
public:
	//Methods
	bool deposit(int amount);
	bool withdraw(int amount);
	bool transfer(Account& other, int amount);
	void printDetails(ostream& os) const;
	int getAge() const;
	char* getName() const;
	double getBalance() const;
	bool setAge(const int newAge);
	bool setName(const char* newName);
	bool setBalance(const double newBalance);

    //C'tors & D'tors
	Account(const char* name,int age,double balance=0);
	Account();
	~Account();

private:
//Data member
	char* name;
	int age;
	double balance;
};

