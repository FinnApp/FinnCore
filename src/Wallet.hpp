#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "NullEntityError.hpp"
#include "UniqueEntity.hpp"

class Transaction;

/*!
 * \brief The Wallet class
 *
 * Represents the physical (e.g. cash) or virtual (e.g. credit/debit card, deposit) wallet.
 * It contains a list of transactions.
 */
class Wallet : public UniqueEntity<Wallet>, public NamedEntity
{
public:
    /*!
     * Create wallet with \p id and \p name
     *
     * \param id Wallet ID
     * \param name Wallet name
     * \param initialBalance Balance when no transaction has been made
     * \exception UniqueEntity::SameIdError is thrown if wallet with \p id already exists
     * \exception NamedEntity::EmptyNameError is thrown if \p name is empty
     */
    Wallet(Id id, const std::string& name, double initialBalance);

    /*!
     * \return Initial balance when no transaction has been made
     */
    double initialBalance() const;

    /*!
     * \return Accumulated Wallet balance from all transactions amounts
     */
    double balance() const;

    /*!
     * Add \p transaction to the Wallet. \p transaction is owned by Wallet
     *
     * \exception NullEntityError is thrown if \p transaction is nullptr
     */
    void addTransaction(std::shared_ptr<Transaction>&& transaction);

    /*!
     * Remove the transaction with \p transactionId from Wallet
     */
    void removeTransactionBy(Id transactionId);

    /*!
     * Retrive the transaction with \p transactionId from Wallet
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
