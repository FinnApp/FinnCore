#pragma once

#include "Utils.hpp"

#include "CategoryTests.hpp"
#include "Transaction.hpp"
#include "WalletTests.hpp"

#include <boost/date_time/date.hpp>

const double DefaultAmount = 5.0;
const boost::posix_time::ptime DefaultCreateionDate{boost::gregorian::date{2020, 11, 26}};

inline std::shared_ptr<Transaction> createTransaction(std::weak_ptr<Wallet> wallet, std::weak_ptr<Category> category)
{
    return std::make_shared<Transaction>(DefaultId, DefaultAmount, wallet, category, DefaultCreateionDate);
}

inline std::shared_ptr<Transaction> createTransaction()
{
    return std::make_shared<Transaction>(
        DefaultId, DefaultAmount, createWallet(), createCategory(), DefaultCreateionDate);
}
