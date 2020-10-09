#include "pch.h"
#include "gtest/gtest.h"
#include "test.h"

struct BankAccount
{
	int balance = 0;

	BankAccount()
	{
	}

	explicit BankAccount(const int balance)
		: balance{ balance }
	{
	}
	void deposit(int amount)
	{
		balance += amount;
	}

	bool withdraw(int amount)
	{
		if (amount <= balance)
		{
			balance -= amount;
			return true;
		}
		return false;
	}
};

struct BankAccountTest : testing::Test
{
	BankAccount* account;
	BankAccountTest()
	{
		account = new BankAccount;
	}

	virtual ~BankAccountTest()
	{
		delete account;
	}
};

TEST_F(BankAccountTest, BankAccountStartsEmpty) {

	EXPECT_EQ(0, account->balance);
}

TEST_F(BankAccountTest, CanDepositMoney)
{
	account->deposit(100);
	EXPECT_EQ(100, account->balance);
}

TEST_F(BankAccountTest, BankAccountHasMoney)
{
	account->deposit(100);
	EXPECT_EQ(100, account->balance);
	//EXPECT_EQ(50, account->balance);
}

struct newBankAccountTest : testing::Test
{
	BankAccount* account;
	newBankAccountTest()
	{
		account = new BankAccount;
		account->deposit(50);
	}

	virtual ~newBankAccountTest()
	{
		delete account;
	}
};

struct account_state
{
	int initial_balance;
	int withdraw_amount;
	int final_balance;
	bool success;

	friend std::ostream& operator<<(std::ostream& os, const account_state& obj)
	{
		return os
			<< "initial_balance: " << obj.initial_balance
			<< " withdraw_amount: " << obj.withdraw_amount
			<< " final_balance: " << obj.final_balance
			<< " success: " << obj.success;
	}
};

struct WithdrawAccountTest : BankAccountTest, testing::WithParamInterface<account_state>
{
	WithdrawAccountTest()
	{
		account->balance = GetParam().initial_balance;
	}
};

TEST_P(WithdrawAccountTest, FinalBalance)
{
	auto as = GetParam();
	auto success = account->withdraw(as.withdraw_amount);
	EXPECT_EQ(as.final_balance, account->balance);
	EXPECT_EQ(as.success, success);
}

INSTANTIATE_TEST_CASE_P(Default, WithdrawAccountTest, testing::Values(account_state{ 100,50,50, true }, account_state{ 100, 200, 100, false }));

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST_F(newBankAccountTest, BankAccountStartsEmpty) {

	EXPECT_EQ(50, account->balance);
	account->withdraw(20);
	EXPECT_EQ(30, account->balance);
}

TEST_F(newBankAccountTest, EmptyFinalBalance)
{
	account->withdraw(account->balance);
	EXPECT_EQ(0, account->balance);
}

TEST_F(newBankAccountTest, deposit200)
{
	account->deposit(200);
	EXPECT_EQ(250, account->balance);
}

TEST_F(newBankAccountTest, deposit300)
{
	account->deposit(300);
	EXPECT_EQ(350, account->balance);
}

TEST_F(newBankAccountTest, deposit400)
{
	account->deposit(400);
	EXPECT_EQ(450, account->balance);
}

TEST_F(newBankAccountTest, deposit500)
{
	account->deposit(500);
	EXPECT_EQ(550, account->balance);
}

