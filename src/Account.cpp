#include "Account.hpp"

#include "Category.hpp"
#include "Wallet.hpp"

#include <algorithm>

Account::WalletNotFound::WalletNotFound(Id walletId) :
    std::runtime_error{"Wallet with ID " + std::to_string(walletId) + " not found"}
{
}

Account::CategoryNotFound::CategoryNotFound(Id categoryId) :
    std::runtime_error{"Category with ID " + std::to_string(categoryId) + " not found"}
{
}

Account::NonRootCateogry::NonRootCateogry(Id categoryId) :
    std::runtime_error{"Category with ID " + std::to_string(categoryId) + " not root"}
{
}

Account::Account(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

void Account::addWallet(Wallet&& wallet)
{
    wallets_.emplace_back(std::move(wallet));
}

void Account::removeWalletBy(Id walletId)
{
    wallets_.erase(std::remove_if(wallets_.begin(), wallets_.end(), IdPredicate{walletId}), wallets_.end());
}

Wallet& Account::walletBy(Id walletId)
{
    auto it = std::find_if(wallets_.begin(), wallets_.end(), IdPredicate{walletId});

    if (it == wallets_.end()) throw WalletNotFound{walletId};

    return *it;
}

size_t Account::walletsCount() const
{
    return wallets_.size();
}

void Account::addCategory(std::shared_ptr<Category>&& category)
{
    assert(category);

    if (category->parentCategory().lock()) throw NonRootCateogry{category->id()};

    categories_.emplace_back(std::move(category));
}

void Account::removeCategoryBy(Id categoryId)
{
    categories_.erase(std::remove_if(categories_.begin(), categories_.end(), IdPredicate{categoryId}),
                      categories_.end());
}

Category& Account::categoryBy(Id categoryId)
{
    auto it = std::find_if(categories_.begin(), categories_.end(), IdPredicate{categoryId});

    if (it == categories_.end()) throw CategoryNotFound{categoryId};

    return **it;
}

size_t Account::categoriesCount() const
{
    return categories_.size();
}
