#pragma once

#include "UniqueEntity.hpp"

/*!
 * \brief The Wallet class
 *
 * Represents the physical (e.g. cash) or virtual (e.g. credit/debit card, deposit) wallet.
 * It has assigned currency and contains a list of transactions.
 */
class Wallet : public UniqueEntity<Wallet>
{
public:
    /*!
     * \brief Constructor
     */
    Wallet(Id id);
};
