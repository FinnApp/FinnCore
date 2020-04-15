#pragma once

#include "EntityContainer.hpp"
#include "NamedEntity.hpp"
#include "NullEntityError.hpp"
#include "UniqueEntity.hpp"

/*!
 * \brief The Category class
 *
 * Represents the transaction category and has tree structure:
 * category has subcategories which also can have subcategories and so on.
 */
class Category : public UniqueEntity<Category>, public NamedEntity, public std::enable_shared_from_this<Category>
{
public:
    /*!
     * Create category with \p id and \p name.
     * Category is root by default unless added as a subcategory to another category.
     *
     * \param id Category ID
     * \param name Category name
     * \exception UniqueEntity::SameIdError is thrown if category with \p id already exists
     * \exception NamedEntity::EmptyNameError is thrown if \p name is empty
     */
    Category(Id id, const std::string& name);

    /*!
     * Add \p subcategory to the Category. \p subcateogry is owned by parent Category.
     * There is not limit for nested level.
     *
     * \exception NullEntityError is thrown if \p subcategory is nullptr
     */
    void addSubcategory(const std::shared_ptr<Category>& subcategory);

    /*!
     * Remove the subcategory with \p subcategoryId from parent Category
     */
    void removeSubcategoryBy(Id subcategoryId);

    /*!
     * Retrive the subcategory with \p subcategoryId from parent Category
     *
     * \return Reference to the existing subcategory
     * \exception EntityNotFound is thrown if subcategory with \p subcategoryId isn't found in the parent category
     */
    Category& subcategoryBy(Id subcategoryId);

    /*!
     * \return Number of created subcategories in the parent Category
     */
    size_t subcategoriesCount() const;

    /*!
     * Subcategory doesn't own its parent so the weak pointer is used.
     *
     * \return Weak pointer to parent category. It can be checked if parent category is alive
     */
    std::weak_ptr<Category> parentCategory() const;

private:
    void setParentCategory(std::shared_ptr<Category>&& parentCategory);

private:
    std::weak_ptr<Category> parentCategory_;
    EntityContainer<std::shared_ptr<Category>> subcategories_;
};
