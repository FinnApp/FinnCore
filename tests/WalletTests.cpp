#include "Utils.hpp"

#include "Transaction.hpp"
#include "Wallet.hpp"

TEST(WalletTests, CreateWithUniqueIdAndNameWithoutTransactionsAndCategories)
{
    Wallet w{DefaultId, DefaultName};

    ASSERT_EQ(w.id(), DefaultId);
    ASSERT_EQ(w.name(), DefaultName);
    ASSERT_EQ(w.transactionsCount(), 0);
}

TEST(WalletTests, AddTransactionShouldIncreaseTheNumberOfTransactions)
{
    Wallet w{DefaultId, DefaultName};

    w.addTransaction(std::make_shared<Transaction>(DefaultId));

    ASSERT_EQ(w.transactionsCount(), 1);
}

TEST(WalletTests, GetExistingtransactionById)
{
    Wallet w{DefaultId, DefaultName};

    w.addTransaction(std::make_shared<Transaction>(DefaultId));
    auto& transaction = w.transactionBy(DefaultId);

    ASSERT_EQ(transaction.id(), DefaultId);
}

TEST(WalletTests, GetNonExistingTransactionShouldThrowException)
{
    Wallet w{DefaultId, DefaultName};

    w.addTransaction(std::make_shared<Transaction>(DefaultId));

    ASSERT_THROW(w.transactionBy(DefaultId + 1), EntityNotFound);
}

TEST(WalletTests, RemoveTransactionShouldDecreaseTheNumberOfTransactions)
{
    Wallet w{DefaultId, DefaultName};

    w.addTransaction(std::make_shared<Transaction>(DefaultId));
    w.removeTransactionBy(DefaultId);

    ASSERT_EQ(w.transactionsCount(), 0);
}

TEST(WalletTests, RemoveTransactionOnEmptyNumberOfTransactionsShouldDoNothing)
{
    Wallet w{DefaultId, DefaultName};

    w.removeTransactionBy(DefaultId);

    ASSERT_EQ(w.transactionsCount(), 0);
}

TEST(WalletTests, RemoveNotExistingWalletShouldDoNothing)
{
    Wallet w{DefaultId, DefaultName};

    w.addTransaction(std::make_shared<Transaction>(DefaultId));
    w.removeTransactionBy(DefaultId + 1);

    ASSERT_EQ(w.transactionsCount(), 1);
}
