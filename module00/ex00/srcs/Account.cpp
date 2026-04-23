#include	"../includes/Account.hpp"

Account::Account(size_t id, float value) : _id(id), _balance(value), _credit(0){
	std::cout << "Account created" << std::endl;
	std::cout << *this << std::endl << std::endl;
};

Account::~Account(){
	std::cout << "Delete Account" << std::endl;
	std::cout << *this << std::endl << std::endl;
};

size_t Account::getId() const{
	return _id;
};

float Account::getBalance() const{
	return _balance;
};

float Account::getCredit() const{
	return _credit;
};

void Account::deposit(float value, bool isCredit){
	if (value > 0){
		if (isCredit)
			this->_credit += value;
		else
			this->_balance += value;
	}
	else
		std::cout << "Impossible to deposit negativ value" << std::endl;
};

void Account::withdraw(float value){
	if(value > 0 && _balance >= value)
		this->_balance -= value;
	else if (value > 0)
		std::cout << "Not enough money on account" << std::endl;
	else
		std::cout << "Impossible to withdraw negativ value" << std::endl;
};

std::ostream& operator<<(std::ostream& os, const Account& account){
	os << "id : [" << account.getId() << "] - balance : [" << account.getBalance() << "] - credit : [" << account.getCredit() << "]";
	return (os);
};