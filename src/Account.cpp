#include "Account.hpp"

#include "Category.hpp"
#include "Wallet.hpp"

Account::NonRootCategory::NonRootCategory(Id categoryId) :
    std::runtime_error{"Category with ID " + std::to_string(categoryId) + "is not root"}
{
}

Account::Account(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

double Account::balance() const
{
    double balance = 0.0;
    for (auto&& wallet : wallets_)
    {
        balance += wallet->balance();
    }
    return balance;
}

void Account::addWallet(std::shared_ptr<Wallet>&& wallet)
{
    if (!wallet) throw NullEntityError{"Added wallet is invalid"};

    wallets_.add(std::move(wallet));
}

void Account::removeWalletBy(Id walletId)
{
    wallets_.removeBy(walletId);
}

Wallet& Account::walletBy(Id walletId)
{
    return *wallets_.entityBy(walletId);
}

size_t Account::walletsCount() const
{
    return wallets_.count();
}

void Account::addCategory(std::shared_ptr<Category>&& category)
{
    if (!category) throw NullEntityError{"Added category is invalid"};
    if (category->parentCategory().lock()) throw NonRootCategory{category->id()};

    categories_.add(std::move(category));
}

void Account::removeCategoryBy(Id categoryId)
{
    return categories_.removeBy(categoryId);
}

Category& Account::categoryBy(Id categoryId)
{
    return *categories_.entityBy(categoryId);
}

size_t Account::categoriesCount() const
{
    return categories_.count();
}
