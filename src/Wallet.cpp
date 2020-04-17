#include "Wallet.hpp"

#include "Transaction.hpp"

Wallet::Wallet(Id id, const std::string& name, double initialBalance) :
    UniqueEntity{id},
    NamedEntity{name},
    initialBalance_{initialBalance}
{
}

double Wallet::initialBalance() const
{
    return initialBalance_;
}

double Wallet::balance() const
{
    double balance = initialBalance_;
    for (auto&& transaction : transactions_)
    {
        balance += transaction->amount();
    }
    return balance;
}

void Wallet::addTransaction(std::shared_ptr<Transaction>&& transaction)
{
    if (!transaction) throw NullEntityError{"Added transaction is invalid"};

    transactions_.add(std::move(transaction));
}

void Wallet::removeTransactionBy(Id transactionId)
{
    transactions_.removeBy(transactionId);
}

Transaction& Wallet::transactionBy(Id transactionId)
{
    return *transactions_.entityBy(transactionId);
}

size_t Wallet::transactionsCount() const
{
    return transactions_.count();
}
