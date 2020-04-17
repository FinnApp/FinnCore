#pragma once

/*!
 * \file Transaction.hpp
 */

#include "NullEntityError.hpp"
#include "UniqueEntity.hpp"

#include <boost/date_time/posix_time/ptime.hpp>

/*!
 * Alias for boost type
 */
using DateTime = boost::posix_time::ptime;

/*!
 * Alias for boost type
 */
using Time = boost::posix_time::time_duration;

/*!
 * Alias for boost type
 */
using Date = boost::gregorian::date;

class Wallet;
class Category;

/*!
 * \brief The Transaction class
 *
 * Represents a single transaction in the wallet. Each transaction
 * has unqiue ID, assigned wallet and category, non-zero amount, type (income/expense) and date/time
 * occurence. Optionally, description can be specified to give more info about transaction.
 */
class Transaction : public UniqueEntity<Transaction>
{
public:
    /*!
     * \brief The Type enum
     *
     * Represents the transaction type. For now, only 2 types are available: income and expense
     */
    enum class Type
    {
        Income,
        Expense
    };

    /*!
     * \brief Exception is thrown if transaction is created with zero amount
     */
    struct ZeroAmountError : std::runtime_error
    {
        ZeroAmountError();
    };

    /*!
     * \brief Exception is thrown if transaction is created with invalid date/time
     */
    struct InvalidDateTimeError : std::runtime_error
    {
        InvalidDateTimeError();
    };

    /*!
     * Create Transaction with the given parameters. Description is left empty.
     * Transaction type is deduced from the amount sign.
     *
     * \param id Unique non-negative integer that represents category ID
     * \param amount Non-zero value that represents transaction amount
     * \param wallet Pointer to wallet the transaction is belonged to
     * \param category Pointer to category the transaction is associated with
     * \param dateTime Date/Time in POSIX format when the transaction has occured
     * \exception UniqueEntity::SameIdError is thrown if category with \p id already exists
     * \exception ZeroAmountError is thrown if \p amount equals zero
     * \exception NullEntityError is thrown if \p wallet or \p category is \b nullptr
     * \exception InvalidDateTimeError is thrown if \p dateTime is invalid
     */
    Transaction(Id id,
                double amount,
                std::weak_ptr<Wallet> wallet,
                std::weak_ptr<Category> category,
                const DateTime& dateTime);

    /*!
     * Create Transaction with the given parameters. Description is left empty.
     * Date/Time is generated from the current local time. Transaction type is deduced from the amount sign.
     *
     * \param id Unique non-negative integer that represents category ID
     * \param amount Non-zero value that represents transaction amount
     * \param wallet Pointer to wallet the transaction is belonged to
     * \param category Pointer to category the transaction is associated with
     * \exception UniqueEntity::SameIdError is thrown if category with \p id already exists
     * \exception ZeroAmountError is thrown if \p amount equals zero
     * \exception NullEntityError is thrown if \p wallet or \p category is \b nullptr
     */
    Transaction(Id id, double amount, std::weak_ptr<Wallet> wallet, std::weak_ptr<Category> category);

    /*!
     * \return Transaction amount rounded to 2 decimal places
     */
    double amount() const;

    /*!
     * \param amount New amount which will be rounded to 2 decimal places
     * \exception ZeroAmountError is thrown if \p amount equals zero
     */
    void updateAmount(double amount);

    /*!
     * Transaction doesn't own the wallet so the weak pointer is returned.
     *
     * \return Pointer to the wallet the transaction is belonged to.
     */
    std::weak_ptr<Wallet> wallet() const;
    // TODO tests that pointer equals to wallet where transaction belongs to

    /*!
     * Set new \p wallet for transaction. Transaction will be removed from the previous Wallet automatically.
     *
     * \exception NullEntityError is thrown if \p wallet is \b nullptr
     */
    void updateWallet(const std::weak_ptr<Wallet>& wallet);
    // TODO tests for invalid wallet, transaction removal from wallet, transaction insertion in new wallet,
    // pointer equals to new wallet transaction belongs to

    /*!
     * Transaction doesn't own the category so the weak pointer is returned.
     *
     * \return Pointer to the category the transaction is associated with.
     */
    std::weak_ptr<Category> category() const;
    // TODO tests that pointer equals to category transaction associated with

    /*!
     * \exception NullEntityError is thrown if \p category is \b nullptr
     */
    void updateCategory(const std::weak_ptr<Category>& category);
    // TODO tests for invalid category, pointer equals to new category transaction associated with

    /*!
     * \return Date/Time of transaction occurence in POSIX format
     */
    const DateTime& dateTime() const;
    // TODO DT is generated from local time

    /*!
     * \param dateTime POSIX Date/Time of transaction occurence
     * \exception InvalidDateTimeError is thrown if \p dateTime is invalid
     */
    void updateDateTime(const DateTime& dateTime);

    /*!
     * \return Date when transaction has occured
     */
    Date date() const;

    /*!
     * \return Time when transaction has occured
     */
    Time time() const;

    /*!
     * \return Income if amount is positive or Expense if amount is negative
     */
    Type type() const;

    /*!
     * \return Transaction description
     */
    const std::string& description() const;

    /*!
     * \param description Transaction description
     */
    void updateDescription(const std::string& description);

private:
    double amount_;
    std::weak_ptr<Wallet> wallet_;
    std::weak_ptr<Category> category_;
    DateTime dateTime_;
    std::string description_;
};
