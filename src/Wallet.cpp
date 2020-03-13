#include "Wallet.hpp"

Wallet::Wallet(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}
