#ifndef	__ACCOUNT_HPP__
#define	__ACCOUNT_HPP__

#include	"./Bank.hpp"
#include	<iostream>

class Bank;

class	Account
{
	private:
		const size_t	_id;
		float 			_balance;
		float			_credit;

		void	deposit(float value, bool isCredit);
		void	withdraw(float value);

		Account(size_t id, float value);

		friend class Bank; 

	public:
		~Account();

		size_t getId() const;
		float getBalance() const;
};

std::ostream& operator<<(std::ostream& os, const Account& account);

#endif