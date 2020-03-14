#pragma once

#include "UniqueEntity.hpp"

/*!
 * \brief The Transaction class
 */
class Transaction : public UniqueEntity<Transaction>
{
public:
    /*!
     * \brief Transaction
     * \param id
     * \param amount
     */
    Transaction(Id id, double amount);

    /*!
     * \brief amount
     * \return
     */
    double amount() const;

private:
    double amount_;
};
