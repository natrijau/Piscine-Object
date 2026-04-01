#include	"includes/Bank.hpp"

int main(){
	try {
		Bank bank(2000);

		size_t accountA = bank.creatAccount(500)->getId();
		size_t accountB = bank.creatAccount(1000)->getId();

		bank.updateAccount(accountA, 100);

		bank.bankCredit(accountA, 20000);
		bank.bankCredit(accountA, 200);
		bank.bankCredit(accountB, 1500);

		std::cout << bank << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
