#pragma once

#include "UniqueEntity.hpp"

#include <stdexcept>
#include <string>
#include <vector>

class Wallet;
class Category;

/*!
 * \brief The Account class
 *
 * Repesents the single users and contains account-specific settings, wallets with transactions and categories.
 * You can create multiple accounts but each of them will have own data and information.
 */
class Account : public UniqueEntity<Account>
{
public:
    /*!
     * \brief Exception is thrown if name is empty
     */
    struct EmptyNameError : std::runtime_error
    {
        EmptyNameError();
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
     * \return Unicode Account name
     */
    const std::string& name() const;

    /*!
     * \param name Non-empty unicode string
     * \exception EmptyNameError is thrown if \p name is empty
     */
    void setName(const std::string& name);

    /*!
     * \brief addWallet
     * \param wallet
     */
    void addWallet(Wallet&& wallet);  // TODO walletBy

    void removeWalletBy(Id walletId);

    /*!
     * \return Number of created wallets in the Account
     */
    size_t walletsCount() const;

    /*!
     * \brief addCategory
     * \param category
     */
    void addCategory(Category&& category);  // TODO categoryBy

    void removeCategoryBy(Id categoryId);

    /*!
     * \return Number of created categories in the Account
     */
    size_t categoriesCount() const;

private:
    std::string name_;
    std::vector<Wallet> wallets_;
    std::vector<Category> categories_;
};
