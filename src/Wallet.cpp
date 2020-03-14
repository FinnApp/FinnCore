#include "Wallet.hpp"

#include "Transaction.hpp"

#include <algorithm>

Wallet::TransactionNotFound::TransactionNotFound(Id transactionId) :
    std::runtime_error{"Transaction with ID " + std::to_string(transactionId) + " not found"}
{
}

Wallet::Wallet(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

void Wallet::addTransaction(std::shared_ptr<Transaction>&& wallet)
{
    transactions_.emplace_back(std::move(wallet));
}

void Wallet::removeTransactionBy(Id transactionId)
{
    transactions_.erase(std::remove_if(transactions_.begin(), transactions_.end(), IdPredicate{transactionId}),
                        transactions_.end());
}

Transaction& Wallet::transactionBy(Id transactionId)
{
    auto it = std::find_if(transactions_.begin(), transactions_.end(), IdPredicate{transactionId});

    if (it == transactions_.end()) throw TransactionNotFound{transactionId};

    return **it;
}

size_t Wallet::transactionsCount() const
{
    return transactions_.size();
}
