#include "Wallet.hpp"

#include "Transaction.hpp"

Wallet::Wallet(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

void Wallet::addTransaction(std::shared_ptr<Transaction>&& wallet)
{
    transactions_.add(std::move(wallet));
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
