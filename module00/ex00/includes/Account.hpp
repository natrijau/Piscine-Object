#ifndef	__ACCOUNT_HPP__
#define	__ACCOUNT_HPP__

#include	"./Bank.hpp"
#include	<iostream>

class Bank;

class	Account
{
	private:
		const size_t	_id;
		float _balanceAccount;

		void	deposit(float value);
		void	withdraw(float value);

		Account(float value);

		friend class Bank; 

	public:
		~Account();

		size_t getId() const;
		float getValue() const;
};

std::ostream& operator<<(std::ostream& os, const Account& account);

#endif