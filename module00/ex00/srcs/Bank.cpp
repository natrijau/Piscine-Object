#include	"../includes/Bank.hpp"

class Account;

Bank::Bank() : _liquidity(0), _nextId(0){
	std::cout << "Bank created\nLiquidity : " << _liquidity << std::endl << std::endl;
};

Bank::Bank(float liquidity) : _liquidity(liquidity), _nextId(0){
	std::cout << "Bank created\nLiquidity : " << liquidity << std::endl << std::endl;
};

Account* Bank::_findAccount(size_t id) {
	for (size_t i = 0; i < _clients.size(); ++i)
		if (_clients[i]->getId() == id)
			return _clients[i];
	std::cout << std::endl << "Account not found" << std::endl << std::endl;
	return NULL;
}

Bank::~Bank(){
	for(size_t i = 0; i < this->_clients.size(); i++)
		delete _clients[i];
	_clients.clear();
	std::cout << "Delete Bank" << std::endl << std::endl;
};

size_t	Bank::createAccount(float nb){
	if(nb < 0){
		std::cout << "Cannot create account with negative value"<< std::endl;
		return -1;
	}
	float taxe = nb * 0.05f;
	_liquidity += taxe;

	Account * newClient = new Account(_nextId++, nb - taxe);
	_clients.push_back(newClient);
	return newClient->getId();
};

void Bank::updateAccount(size_t id, float nb){
	Account *acc = _findAccount(id);
	if (!acc)
		return;
	if(nb > 0){
		std::cout << std::endl << *acc << std::endl;
		std::cout << "Request :" << std::endl << " - Deposit " << nb << "$" << std::endl << " - Taxe 5%" << std::endl; 
		float taxe = nb * 0.05f;
		_liquidity += taxe;
		acc->deposit(nb - taxe, false);
	}
	else{
		std::cout << std::endl << *acc << std::endl;
		std::cout << "Request :" << std::endl << " - Withdraw " << -nb << "$" << std::endl; 
		acc->withdraw(-nb);
	}
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
	if (credit < 0 ){
		std::cout << "Not negativ credit" << std::endl;
		return;
	}
	if (_liquidity < credit){
		std::cout << "Not enough liquidity" << std::endl << std::endl;
		return;
	}
	Account *account = _findAccount(id);
	if (!account)
		return;
	account->deposit(credit, true);
	std::cout << "Client [" << id << "] - credit [" << account->getCredit() << "]" << std::endl; 
	_liquidity -= credit;
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
	os << "Bank [Liquidity: " << bank._liquidity << "]" << std::endl << std::endl;
	os << "Accounts:" << std::endl;
	const std::vector<Account*>& clients = bank._clients;
	for (size_t i = 0; i < clients.size(); ++i)
		os << *clients[i] << std::endl;
	return os;
}