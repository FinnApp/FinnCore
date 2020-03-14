#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "UniqueEntity.hpp"

#include <memory>

/*!
 * \brief The Category class
 *
 * Represents the transaction category and has tree structure:
 * category has subcategories which also can have subsubcategories and so on.
 */
class Category : public UniqueEntity<Category>, public NamedEntity, public std::enable_shared_from_this<Category>
{
public:
    /*!
     * \brief Constructor
     *
     * Constructs category object with \p id and \p name
     *
     * \param id Unique non-negative integer that represents category ID
     * \param name Unicode string that represents category name
     * \exception SameIdError is thrown if category with \p id already exists
     * \exception EmptyNameError is thrown if \p name is empty
     */
    Category(Id id, const std::string& name);

    /*!
     * \brief Adds subcategory to account
     *
     * Subcateogry is owned by parent category. Subcategory has reference to its parent.
     */
    void addSubcategory(const std::shared_ptr<Category>& subcategory);

    /*!
     * \brief Removes subcategory with \p subcategoryId from parent category
     */
    void removeSubcategoryBy(Id subcategoryId);

    /*!
     * \brief Retrives the subcategory with \p subcategoryId from category
     * \return Reference to existing subcategory
     * \exception NotFound is thrown if subcategory with \p subcategoryId isn't found in the parent category
     */
    Category& subcategoryBy(Id subcategoryId);

    /*!
     * \return Number of created subcategories in the Category
     */
    size_t subcategoriesCount() const;

    /*!
     * \return Weak pointer to parent category. It can be checked to find if parent category is alive
     */
    std::weak_ptr<Category> parentCategory() const;

private:
    void setParentCategory(std::shared_ptr<Category>&& parentCategory);

private:
    std::weak_ptr<Category> parentCategory_;
    EntityContainer<std::shared_ptr<Category>> subcategories_;
};
