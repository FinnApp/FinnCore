#include "Account.hpp"

#include "Category.hpp"
#include "Wallet.hpp"

Account::EmptyNameError::EmptyNameError() : std::runtime_error{"Account name shouldn't be empty"} {}

Account::Account(Id id, const std::string& name) : UniqueEntity{id}, name_(name)
{
    if (name.empty()) throw EmptyNameError{};
}

const std::string& Account::name() const
{
    return name_;
}

void Account::setName(const std::string& name)
{
    if (name.empty()) throw EmptyNameError{};

    name_ = name;
}

void Account::addWallet(Wallet&& wallet)
{
    wallets_.emplace_back(std::move(wallet));
}

void Account::removeWalletBy(Id walletId) {}

size_t Account::walletsCount() const
{
    return wallets_.size();
}

void Account::addCategory(Category&& category)
{
    categories_.emplace_back(std::move(category));
}

void Account::removeCategoryBy(Id categoryId) {}

size_t Account::categoriesCount() const
{
    return categories_.size();
}
