#pragma once

#include "UniqueEntity.hpp"

/*!
 * \brief The Category class
 *
 * Represents the transaction category and has tree structure:
 * category has subcategories which also can have subsubcategories and so on.
 */
class Category : public UniqueEntity<Category>
{
public:
    /*!
     * \brief Constructor
     */
    Category(Id id);
};
