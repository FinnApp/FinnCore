#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "UniqueEntity.hpp"

class Wallet;
class Category;

/*!
 * \brief The Account class
 *
 * Repesents a single user and contains account-specific settings, wallets with transactions and categories.
 * You can create multiple accounts but each of them will have own data and settings.
 */
class Account : public UniqueEntity<Account>, public NamedEntity
{
public:
    /*!
     * \brief Exception is thrown when category is not root
     */
    struct NonRootCategory : std::runtime_error
    {
        /*!
         * \param categoryId is used in the exception message
         */
        NonRootCategory(Id categoryId);
    };

    /*!
     * \brief Exception is thrown if added wallet is nullptr
     */
    struct InvalidWallet : std::runtime_error
    {
        InvalidWallet();
    };

    /*!
     * \brief Exception is thrown if added category is nullptr
     */
    struct InvalidCategory : std::runtime_error
    {
        InvalidCategory();
    };

    /*!
     * Create account with \p id and \p name
     *
     * \param id Account ID
     * \param name Account name
     * \exception UniqueEntity::SameIdError is thrown if account with \p id already exists
     * \exception NamedEntity::EmptyNameError is thrown if \p name is empty
     */
    Account(Id id, const std::string& name);

    /*!
     * \return Account overall balance which is accumulated from wallets balances.
     * It assumes the same currency among all wallets.
     */
    double balance() const;
    // TODO tests with wallets

    /*!
     * Add \p wallet to the Account. \p wallet is owned by Account
     *
     * \exception InvalidWallet is thrown if \p wallet is nullptr
     */
    void addWallet(std::shared_ptr<Wallet>&& wallet);
    // TODO tests with nullptr

    /*!
     * Remove the wallet with \p walletId from the Account
     *
     * If wallet with \p walletId doesn't exists it will do nothing
     */
    void removeWalletBy(Id walletId);

    /*!
     * Retrive the wallet with \p walletId from the Account
     *
     * \return Reference to the existing wallet
     * \exception EntityNotFound is thrown if wallet with \p walletId isn't found in the account
     */
    Wallet& walletBy(Id walletId);

    /*!
     * \return Number of created wallets in the Account
     */
    size_t walletsCount() const;

    /*!
     * Add root \p category to the Account. \p category is owned by Account
     *
     * \exception NonRootCategory is thrown if \p category is not root
     * \exception InvalidCategory is thrown if \p category is nullptr
     */
    void addCategory(std::shared_ptr<Category>&& category);
    // TODO tests for nullptr

    /*!
     * Remove the category with \p categoryId from the Account
     *
     * If category with \p categoryId doesn't exists it will do nothing
     */
    void removeCategoryBy(Id categoryId);

    /*!
     * Retrive the category with \p walletId from category
     *
     * \return Reference to existing category
     * \exception EntityNotFound is thrown if category with \p categoryId isn't found in the account
     */
    Category& categoryBy(Id categoryId);

    /*!
     * \return Number of created categories in the Account
     */
    size_t categoriesCount() const;

private:
    EntityContainer<std::shared_ptr<Wallet>> wallets_;
    EntityContainer<std::shared_ptr<Category>> categories_;
};
