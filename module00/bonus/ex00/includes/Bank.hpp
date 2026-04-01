#ifndef	__BANK_HPP__
#define	__BANK_HPP__

#include	<map>
#include	<iostream>
#include	<stdexcept>

struct Bank {

	private:
		struct Account{
			const size_t	_id;
			float 			_balanceAccount;
			
			Account(size_t id, float value);
			size_t getId() const;
			float getValue() const;

			friend struct Bank;
		};

		float 								_liquidity;
		static size_t 						_nextId;
		std::map<size_t, Bank::Account> 	_clients;

		Account*	_findAccount(size_t id);
		
	public:
		Bank();
		Bank(float liquidity);

		bool updateLiquidity(float nb);

		Account* creatAccount(float nb);
		void deleteAccount(size_t id);

		void updateAccount(size_t id, float nb);
		void bankCredit(size_t id, float credit);

		float getLiquidity() const;
		const std::map<size_t, Account>& getClients() const;

		const Account& operator[](size_t id) const;
		friend std::ostream& operator<<(std::ostream& os, const Bank& bank);
};

std::ostream& operator<<(std::ostream& os, const Bank& bank);

#endif
