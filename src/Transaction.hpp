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
     */
    Transaction(Id id) : UniqueEntity{id} {}
};
