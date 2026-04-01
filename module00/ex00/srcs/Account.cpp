#include	"../includes/Account.hpp"

static size_t ids = 0;

Account::Account(float value) : _id(ids++), _balanceAccount(value){
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

float Account::getValue() const{
	return _balanceAccount;
};

void Account::deposit(float value){
	if (value > 0){
		this->_balanceAccount += value;
		std::cout << *this << std::endl << std::endl;
	}
	else
		std::cout << "Impossible to deposit negativ value" << std::endl;
};

void Account::withdraw(float value){
	if(value > 0 && _balanceAccount >= value){
		this->_balanceAccount -= value;
		std::cout << *this << std::endl << std::endl;
	}
};

std::ostream& operator<<(std::ostream& os, const Account& account){
	os << "id : [" << account.getId() << "] - liquidity : [" << account.getValue() << "]";
	return (os);
};