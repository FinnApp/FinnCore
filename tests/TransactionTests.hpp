#pragma once

#include "Utils.hpp"

#include "CategoryTests.hpp"
#include "Transaction.hpp"
#include "WalletTests.hpp"

#include <boost/date_time/date.hpp>

const double DefaultAmount = 5.0;
const Date DefaultCreationDate{2020, 11, 26};
const Time DefaultCreationTime{3, 0, 0};
const DateTime DefaultCreationDT{DefaultCreationDate, DefaultCreationTime};

inline std::shared_ptr<Transaction> createTransaction(double amount,
                                                      std::weak_ptr<Wallet> wallet,
                                                      std::weak_ptr<Category> category,
                                                      const DateTime& dt)
{
    return std::make_shared<Transaction>(DefaultId, amount, wallet, category, dt);
}

inline std::shared_ptr<Transaction> createTransaction()
{
    return std::make_shared<Transaction>(DefaultId, DefaultAmount, createWallet(), createCategory(), DefaultCreationDT);
}
