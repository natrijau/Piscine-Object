#ifndef	__BANK_HPP__
#define	__BANK_HPP__

#include	<vector>
#include	<iostream>
#include	"./Account.hpp"

class	Account;

class Bank {
	private:
		float					_liquidity;
		size_t					_nextId;
		std::vector<Account *> 	_clients;

		Account*	_findAccount(size_t id);
	
	public:
		Bank();
		Bank(float liquidity);
		~Bank();
		
		size_t createAccount(float nb);
		void deleteAccount(size_t id);
		void updateAccount(size_t id, float nb);
		
		void bankCredit(size_t id, float credit);

		friend std::ostream& operator<<(std::ostream& os, const Bank& bank);
};

#endif
