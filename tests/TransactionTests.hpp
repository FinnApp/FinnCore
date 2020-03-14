#pragma once

#include "Utils.hpp"

#include "Transaction.hpp"

const double DefaultAmount = 5.0;

inline std::shared_ptr<Transaction> createTransaction()
{
    return std::make_shared<Transaction>(DefaultId, DefaultAmount);
}
