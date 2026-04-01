#include	"../includes/Bank.hpp"

size_t Bank::_nextId = 1;

/********/
//Account
/********/

Bank::Account::Account(size_t id, float value) :_id(id), _balanceAccount(value){
	std::cout << "Account created" << std::endl;
}

size_t Bank::Account::getId() const{
	return _id;
};

float Bank::Account::getValue() const{
	return _balanceAccount;
};


/******/
//Bank
/******/

Bank::Bank() : _liquidity(0){
	std::cout << "Bank created. Liquidity : " << _liquidity << std::endl << std::endl;
};

Bank::Bank(float liquidity) : _liquidity(liquidity){
	std::cout << "Bank created. Liquidity : " << liquidity << std::endl << std::endl;
};

Bank::Account* Bank::_findAccount(size_t id) {
	std::map<size_t, Account>::iterator it = _clients.find(id);
	
	if(it == _clients.end())
		throw std::runtime_error("Account not found");
	
	return &(it->second);
};

bool Bank::updateLiquidity(float nb){
	
	if (this->_liquidity - nb < 0)
		return false;
	
	this->_liquidity -= nb;
	return true;
};

Bank::Account* Bank::creatAccount(float nb){
	if(nb < 0)
		throw std::runtime_error("Cannot create account with negative value");

	size_t newClientId = _nextId++;
	if(_clients.find(newClientId) != _clients.end())
		throw std::runtime_error("Account ID exists");

	_clients.insert(std::make_pair(newClientId, Account(newClientId, nb)));
	return	&_clients.find(newClientId)->second;
};

void Bank::updateAccount(size_t id, float nb){
	Account *acc = _findAccount(id);
	if (!acc)
		return;
	if(nb > 0){
		//std::cout << *acc << std::endl; 
		std::cout << " - Deposit " << nb << "$" << std::endl << " - Taxe 0.5%" << std::endl; 
		float tax = nb * 0.05f;
		_liquidity += tax;
		acc->_balanceAccount += (nb - tax);
	}
	else
		acc->_balanceAccount += nb;
};

void Bank::deleteAccount(size_t id){
	if(_clients.find(id) == _clients.end())
		throw std::runtime_error("Account Id dont exists");
	_clients.erase(id);
};

void Bank::bankCredit(size_t id, float credit){
	std::cout << "Client [" << id << "] request a " << credit << " credit" << std::endl; 
	if (credit < 0)
		throw std::runtime_error("Not negativ Credit");
	if (_liquidity - credit < 0)
		throw std::runtime_error("Not enough liquidity");

	Account *acc = _findAccount(id);
	if (!acc)
		return;
	std::cout << "Credit approved" << std::endl << std::endl;
	acc->_balanceAccount += credit;
	_liquidity -= credit;
};

float Bank::getLiquidity() const {
    return _liquidity;
}

const	std::map<size_t, Bank::Account>& Bank::getClients() const{
	return _clients;
};

const Bank::Account& Bank::operator[](size_t id) const{
	std::map<size_t, Account>::const_iterator it = _clients.find(id);
	if(it == _clients.end())
		throw std::runtime_error("Accoutn not found");

	return it->second;
};

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
	os << "Bank liquidity: " << bank._liquidity << "\nAccounts:\n";
	std::map<size_t, Bank::Account>::const_iterator it = bank._clients.begin();
	std::map<size_t, Bank::Account>::const_iterator end = bank._clients.end();

	for (; it != end; ++it) {
		os << "ID: " << it->first
			<< " Balance: " << it->second.getValue() << "\n";
	}
	return os;
}