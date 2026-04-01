#include	"includes/Bank.hpp"
#include	"includes/Account.hpp"

int main(){
	Bank bank = Bank(2000);

	Account* accountA = bank.creatAccount(100);
	Account* accountB = bank.creatAccount(100);
	
	bank.updateAccount(accountA->getId(), 100);

	bank.bankCredit(accountA->getId(), 20000);
	bank.bankCredit(accountA->getId(), 200);
	bank.bankCredit(accountB->getId(), 1500);
	std::cout << bank << std::endl;

	return (0);
}
