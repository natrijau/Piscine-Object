#include	"includes/Bank.hpp"
#include	<iostream>

static void printBank(Bank& bank){
	std::cout << "=== BANK STATUS ===" << std::endl << std::endl;
	std::cout << bank << std::endl;
	std::cout << "===================" << std::endl << std::endl;
}

int main(){
	Bank bank(2000);

	std::cout << "===== CREATE ======" << std::endl;
	size_t a = bank.createAccount(100);
	size_t b = bank.createAccount(200);
	size_t c = bank.createAccount(300);
	size_t d = bank.createAccount(-1);
	size_t e = bank.createAccount(3.2);
	(void) c;
	(void) d;
	(void) e;
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "===== DEPOSIT =====" << std::endl;
	bank.updateAccount(a, 100);
	bank.updateAccount(b, 50);
	bank.updateAccount(999, 100);
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "===== WITHDRAW ====" << std::endl;
	bank.updateAccount(a, -50);
	bank.updateAccount(b, -5000);
	bank.updateAccount(999, -10);
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "====== CREDIT ======" << std::endl;
	bank.bankCredit(a, 1500);
	bank.bankCredit(a, 100000);
	bank.bankCredit(999, 100);
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "====== DELETE =====" << std::endl;
	bank.deleteAccount(b);
	bank.deleteAccount(999);
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "=== USE AFTER DELETE (safe) ===" << std::endl;
	bank.updateAccount(b, 100);
	bank.bankCredit(b, 100);
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "=== MASS TEST ===" << std::endl;
	for (int i = 0; i < 50; i++){
		size_t id = bank.createAccount(200);
		bank.updateAccount(id, 5);
		bank.updateAccount(id, -3);
	}
	std::cout << "===================" << std::endl << std::endl;
	printBank(bank);

	std::cout << "END TEST" << std::endl;
	std::cout << "===================" << std::endl << std::endl;
	return 0;
}