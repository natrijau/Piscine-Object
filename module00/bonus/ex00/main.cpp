#include	"includes/Bank.hpp"

static void updateDeletedAccount(Bank& bank, size_t id, float amount) {
	try {
		bank.updateAccount(id, amount);
		std::cout << "Updated account ID: " << id << " with amount: " << amount << "$" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Error updating account: " << e.what() << std::endl;
	}
}

static void deleteBadAccount(Bank& bank, size_t id) {
	try {
		bank.deleteAccount(id);
		std::cout << "Account with ID: " << id << " deleted successfully." << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Error deleting account: " << e.what() << std::endl;
	}
}

static void badAccountcredit(Bank& bank, size_t id, float credit) {
	try {
		bank.bankCredit(id, credit);
		std::cout << "Credit of " << credit << "$ approved for account ID: " << id << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Error processing credit: " << e.what() << std::endl;
	}
}

static void badCredit(Bank& bank, size_t id, float credit) {
	try {
		bank.bankCredit(id, credit);
		std::cout << "Credit of " << credit << "$ approved for account ID: " << id << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Error processing credit: " << e.what() << std::endl;
	}
}

static void depositFalseAccount(Bank& bank, size_t id, float amount) {
	try {
		bank.updateAccount(id, amount);
		std::cout << "Deposited " << amount << "$ to account ID: " << id << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Error depositing to account: " << e.what() << std::endl;
	}
}

static size_t createBadAccount(Bank& bank) {
	try {
		size_t accountId = bank.creatAccount(-100)->getId();
		std::cout << "Account created with ID: " << accountId << std::endl;
		return accountId;
	} catch (const std::exception& e) {
		std::cout << "Error creating account: " << e.what() << std::endl;
	}
	return 0;
}

int main(){
	try {
		Bank bank(2000);

		std::cout << "==== Create Accounts ====" << std::endl;
		size_t accountA = bank.creatAccount(1000)->getId();
		size_t accountB = createBadAccount(bank);
		std::cout << "=========================" << std::endl << std::endl;

		std::cout << bank << std::endl;

		std::cout << "==== Deposit Accounts ===" << std::endl;
		bank.updateAccount(accountA, 100);
		depositFalseAccount(bank, accountB, 100);
		std::cout << "=========================" << std::endl << std::endl;

		std::cout << bank << std::endl;

		std::cout << "=== Withdraw Accounts ===" << std::endl;
		bank.updateAccount(accountA, -100);
		depositFalseAccount(bank, accountB, -100);
		std::cout << "=========================" << std::endl << std::endl;

		std::cout << bank << std::endl;

		std::cout << "====== Bank Credit ======" << std::endl;
		bank.bankCredit(accountA, 200);
		badCredit(bank, accountA, -100);
		badAccountcredit(bank, accountB, 100);
		std::cout << "=========================" << std::endl << std::endl;

		std::cout << bank << std::endl;

		std::cout << "==== Delete Account ====" << std::endl;
		bank.deleteAccount(accountA);
		deleteBadAccount(bank, accountA);
		std::cout << "\nupdate deleted account" << std::endl;
		updateDeletedAccount(bank, accountA, 100);
		std::cout << "\ncredit deleted account" << std::endl;
		bank.bankCredit(accountA, 100);
		std::cout << "=========================" << std::endl << std::endl;

	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
