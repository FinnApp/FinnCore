#pragma once

#include "Utils.hpp"

#include "Wallet.hpp"

const double DefaultInitialBalance = 0.0;

inline Wallet createWallet()
{
    return Wallet{DefaultId, DefaultName, DefaultInitialBalance};
}

inline Wallet createWallet(Id id, const std::string& name, double initialBalance)
{
    return Wallet{id, name, initialBalance};
}
