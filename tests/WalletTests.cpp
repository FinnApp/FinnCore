#include "WalletTests.hpp"

#include "TransactionTests.hpp"

TEST(WalletTests, CreateWithUniqueIdAndNameWithoutTransactions)
{
    auto w = createWallet();

    ASSERT_EQ(w->id(), DefaultId);
    ASSERT_EQ(w->name(), DefaultName);
    ASSERT_EQ(w->initialBalance(), 0);
    ASSERT_EQ(w->balance(), 0);
    ASSERT_EQ(w->transactionsCount(), 0);
}

TEST(WalletTests, CreateWithWalletWithInitialBalance)
{
    auto w = createWallet(DefaultId, DefaultName, 100);

    ASSERT_EQ(w->initialBalance(), 100);
    ASSERT_EQ(w->balance(), 100);
}

TEST(WalletTests, AddTransactionShouldIncreaseTheNumberOfTransactions)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(w));

    ASSERT_EQ(w->transactionsCount(), 1);
}

TEST(WalletTests, AddTransactionShouldIncreaseBalance)
{
    const double InitialBalance = 100;
    const double TransactionAmount = 10.5;
    auto w = createWallet(DefaultId, DefaultName, InitialBalance);

    for (int i = 0; i != 3; ++i)
    {
        w->addTransaction(createTransaction(Id{i}, TransactionAmount + i, w));
    }

    ASSERT_EQ(w->balance(), InitialBalance + 34.5);
}

TEST(WalletTests, AddIncomeAndExpenseTransactions)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(Id{0}, -10, w));
    w->addTransaction(createTransaction(Id{1}, 5, w));

    ASSERT_EQ(w->balance(), -5);
}

TEST(WalletTests, AddTransactionsWithSameAmountButWithDifferentSign)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(Id{0}, -10, w));
    w->addTransaction(createTransaction(Id{1}, 10, w));

    ASSERT_EQ(w->balance(), 0);
}

TEST(WalletTests, AddNullptrTransactionShouldThrowException)
{
    auto w = createWallet();

    ASSERT_THROW(w->addTransaction(nullptr), NullEntityError);
}

TEST(WalletTests, GetExistingTransactionById)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(w));
    auto& transaction = w->transactionBy(DefaultId);

    ASSERT_EQ(transaction.id(), DefaultId);
}

TEST(WalletTests, GetNonExistingTransactionShouldThrowException)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(w));

    ASSERT_THROW(w->transactionBy(DefaultId + 1), EntityNotFound);
}

TEST(WalletTests, RemoveTransactionShouldDecreaseTheNumberOfTransactions)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(w));
    w->removeTransactionBy(DefaultId);

    ASSERT_EQ(w->transactionsCount(), 0);
}

TEST(WalletTests, RemoveTransactionOnEmptyNumberOfTransactionsShouldDoNothing)
{
    auto w = createWallet();

    w->removeTransactionBy(DefaultId);

    ASSERT_EQ(w->transactionsCount(), 0);
}

TEST(WalletTests, RemoveNotExistingTransactionShouldDoNothing)
{
    auto w = createWallet();

    w->addTransaction(createTransaction(w));
    w->removeTransactionBy(DefaultId + 1);

    ASSERT_EQ(w->transactionsCount(), 1);
}
