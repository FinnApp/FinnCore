#pragma once

#include "Utils.hpp"

#include "Wallet.hpp"

const double DefaultInitialBalance = 0.0;

inline std::shared_ptr<Wallet> createWallet()
{
    return std::make_shared<Wallet>(DefaultId, DefaultName, DefaultInitialBalance);
}

inline std::shared_ptr<Wallet> createWallet(Id id, const std::string& name, double initialBalance)
{
    return std::make_shared<Wallet>(id, name, initialBalance);
}
