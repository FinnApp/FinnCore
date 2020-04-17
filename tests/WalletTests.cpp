#include "WalletTests.hpp"

#include "TransactionTests.hpp"

std::shared_ptr<Transaction> createTransaction(std::weak_ptr<Wallet> wallet)
{
    return createTransaction(DefaultAmount, wallet, createCategory(), DefaultCreationDT);
}

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

TEST(WalletTests, AddNullptrTransactionShouldThrowException)
{
    auto w = createWallet();

    ASSERT_THROW(w->addTransaction(nullptr), NullEntityError<Transaction>);
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
