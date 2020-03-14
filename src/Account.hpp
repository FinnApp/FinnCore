#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "UniqueEntity.hpp"

class Wallet;
class Category;

/*!
 * \brief The Account class
 *
 * Repesents the single users and contains account-specific settings, wallets with transactions and categories.
 * You can create multiple accounts but each of them will have own data and information.
 */
class Account : public UniqueEntity<Account>, public NamedEntity
{
public:
    /*!
     * \brief Exception is thrown is category with some ID is not root
     */
    struct NonRootCategory : std::runtime_error
    {
        /*!
         * \param categoryId is used in exception message
         */
        NonRootCategory(Id categoryId);
    };

    /*!
     * \brief Constructor
     *
     * Constructs account object with \p id and \p name
     *
     * \param id Unique non-negative integer that represents account ID
     * \param name Unicode string that represents account name
     * \exception SameIdError is thrown if account with \p id already exists
     * \exception EmptyNameError is thrown if \p name is empty
     */
    Account(Id id, const std::string& name);

    /*!
     * \brief Adds wallet to account
     *
     * Wallet is owned by account
     */
    void addWallet(Wallet&& wallet);

    /*!
     * \brief Removes wallet with \p walletId from account
     */
    void removeWalletBy(Id walletId);

    /*!
     * \brief Retrives the wallet with \p walletId from account
     * \return Reference to existing wallet
     * \exception NotFound is thrown if wallet with \p walletId isn't found in the account
     */
    Wallet& walletBy(Id walletId);

    /*!
     * \return Number of created wallets in the Account
     */
    size_t walletsCount() const;

    /*!
     * \brief Adds category to account
     *
     * Category is owned by account
     *
     * \exception NonRootCategory is thrown if \p category is not root
     */
    void addCategory(std::shared_ptr<Category>&& category);

    /*!
     * \brief Removes category with \p categoryId from account
     */
    void removeCategoryBy(Id categoryId);

    /*!
     * \brief Retrives the category with \p walletId from category
     * \return Reference to existing category
     * \exception NotFound is thrown if category with \p categoryId isn't found in the account
     */
    Category& categoryBy(Id categoryId);

    /*!
     * \return Number of created categories in the Account
     */
    size_t categoriesCount() const;

private:
    EntityContainer<Wallet> wallets_;
    EntityContainer<std::shared_ptr<Category>> categories_;
};
