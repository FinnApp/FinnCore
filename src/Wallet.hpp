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
     * Constructs wallet object with \p id and \p name
     *
     * \param id Unique non-negative integer that represents wallet ID
     * \param name Unicode string that represents wallet name
     * \param initialBalance Sets the initial balance for the wallet
     * \exception UniqueEntity::SameIdError is thrown if wallet with \p id already exists
     * \exception NamedEntity::EmptyNameError is thrown if \p name is empty
     */
    Wallet(Id id, const std::string& name, double initialBalance);

    /*!
     * \return Initial balance when no transaction has been made
     */
    double initialBalance() const;

    /*!
     * \return Accumulated wallet balance from all transactions amounts
     */
    double balance() const;
    // TODO tests with transactions

    /*!
     * Adds transaction to wallet. Transaction is owned by wallet
     */
    void addTransaction(std::shared_ptr<Transaction>&& wallet);
    // TODO tests for nullptr, probably change to unique_ptr

    /*!
     * Removes transaction with \p transactionId from wallet
     */
    void removeTransactionBy(Id transactionId);

    /*!
     * Retrives the transaction with \p transactionId from wallet
     *
     * \return Reference to existing transaction
     * \exception EntityNotFound is thrown if transaction with \p transactionId isn't found in the wallet
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
