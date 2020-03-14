#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "UniqueEntity.hpp"

#include <memory>

class Transaction;

/*!
 * \brief The Wallet class
 *
 * Represents the physical (e.g. cash) or virtual (e.g. credit/debit card, deposit) wallet.
 * It has assigned currency and contains a list of transactions.
 */
class Wallet : public UniqueEntity<Wallet>, public NamedEntity
{
public:
    /*!
     * \brief Constructor
     *
     * Constructs wallet object with \p id and \p name
     *
     * \param id Unique non-negative integer that represents wallet ID
     * \param name Unicode string that represents wallet name
     * \param initialBalance Sets the initial balance for the wallet
     * \exception SameIdError is thrown if wallet with \p id already exists
     * \exception EmptyNameError is thrown if \p name is empty
     */
    Wallet(Id id, const std::string& name, double initialBalance);

    /*!
     * \brief initialBalance
     * \return
     */
    double initialBalance() const;

    /*!
     * \brief balance
     * \return
     */
    double balance() const;

    /*!
     * \brief Adds transaction to wallet
     *
     * Transaction is owned by wallet
     */
    void addTransaction(std::shared_ptr<Transaction>&& wallet);

    /*!
     * \brief Removes transaction with \p transactionId from wallet
     */
    void removeTransactionBy(Id transactionId);

    /*!
     * \brief Retrives the transaction with \p transactionId from wallet
     * \return Reference to existing transaction
     * \exception NotFound is thrown if transaction with \p transactionId isn't found in the wallet
     */
    Transaction& transactionBy(Id transactionId);

    /*!
     * \return Number of created transactions in the Wallet
     */
    size_t transactionsCount() const;

private:
    EntityContainer<std::shared_ptr<Transaction>> transactions_;
    double initialBalance_;
};
