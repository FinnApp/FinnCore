#pragma once

#include "NamedEntity.hpp"
#include "UniqueEntity.hpp"

#include <vector>

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
     * \brief Exception is thrown is transaction with some ID is not found
     */
    struct TransactionNotFound : std::runtime_error
    {
        /*!
         * \param transactionId is used in exception message
         */
        TransactionNotFound(Id transactionId);
    };

    /*!
     * \brief Constructor
     *
     * Constructs wallet object with \p id and \p name
     *
     * \param id Unique non-negative integer that represents wallet ID
     * \param name Unicode string that represents wallet name
     * \exception SameIdError is thrown if wallet with \p id already exists
     * \exception EmptyNameError is thrown if \p name is empty
     */
    Wallet(Id id, const std::string& name);

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
     * \exception TransactionNotFound is thrown if transaction with \p transactionId isn't found in the wallet
     */
    Transaction& transactionBy(Id transactionId);

    /*!
     * \return Number of created transactions in the Wallet
     */
    size_t transactionsCount() const;

private:
    std::vector<std::shared_ptr<Transaction>> transactions_;
};
