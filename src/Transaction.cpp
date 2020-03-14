#include "Transaction.hpp"

Transaction::Transaction(Id id, double amount) : UniqueEntity{id}, amount_{amount} {}

double Transaction::amount() const
{
    return amount_;
}
