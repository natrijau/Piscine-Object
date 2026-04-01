#include	"../includes/Bank.hpp"

class Account;

Bank::Bank() : _liquidity(0){
	std::cout << "Bank created. Liquidity : " << _liquidity << std::endl << std::endl;
};

Bank::Bank(float liquidity) : _liquidity(liquidity){
	std::cout << "Bank created. Liquidity : " << liquidity << std::endl << std::endl;
};

Account* Bank::_findAccount(size_t id) {
	for (size_t i = 0; i < _clients.size(); ++i)
		if (_clients[i]->getId() == id)
			return _clients[i];
	std::cout << "Account [" << id << "] not found" << std::endl << std::endl;
	return NULL;
}

Bank::~Bank(){
	for(size_t i = 0; i < this->_clients.size(); i++){
		delete _clients[i];
	}
	 _clients.clear();
	std::cout << "Delete Bank" << std::endl << std::endl;
};

bool Bank::updateLiquidity(float nb){
	if (this->_liquidity - nb < 0)
		return false;
	this->_liquidity -= nb;
	return true;
};

Account* Bank::creatAccount(float nb){
	if(nb < 0){
		std::cout << "Cannot create account with negative value" << std::endl;
		return NULL;
	}
	Account * newClient = new Account(nb);
	_clients.push_back(newClient);
	return newClient;
};

void Bank::updateAccount(size_t id, float nb){
	Account *acc = _findAccount(id);
	if (!acc)
		return;
	if(nb > 0){
		std::cout << *acc << std::endl; 
		std::cout << " - Deposit " << nb << "$" << std::endl << " - Taxe 0.5%" << std::endl; 
		_liquidity += nb * 0.5;
		acc->deposit(nb * 0.95);
	}
	else
		acc->withdraw(nb);
};

void Bank::deleteAccount(size_t id){
	for(size_t i = 0; i < this->_clients.size(); i++){
		if (_clients[i]->getId() == id){
			delete this->_clients[i]; 
			_clients.erase(_clients.begin() + i);
			return;
		}
	}
};

void Bank::bankCredit(size_t id, float credit){
	std::cout << "Client [" << id << "] request a " << credit << " credit" << std::endl; 
	if (credit < 0)
		return;
	if (_liquidity - credit < 0)
	{
		std::cout << "Not enough liquidity" << std::endl << std::endl;
		return;
	}
	for(size_t i = 0; i < this->_clients.size(); i++){
		if (i == id){
			std::cout << "Credit approved" << std::endl << std::endl;
			_clients[i]->deposit(credit);
			this->_liquidity -= credit;
			break;
		}
	}
};

float Bank::getLiquidity() const {
    return _liquidity;
}

const	std::vector<Account *>& Bank::getClients() const{
	return _clients;
};


std::ostream& operator<<(std::ostream& os, const Bank& bank) {
    os << "Bank [Liquidity: " << bank.getLiquidity() << "]" << std::endl;
    os << "Accounts:" << std::endl;
	const std::vector<Account*>& clients = bank.getClients();
    for (size_t i = 0; i < clients.size(); ++i) {
        os << *clients[i] << std::endl;
    }
    return os;
}