#include "Category.hpp"

Category::Category(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

void Category::addSubcategory(const std::shared_ptr<Category>& subcategory)
{
    subcategory->setParentCategory(shared_from_this());
    subcategories_.add(subcategory);
}

void Category::removeSubcategoryBy(Id subcategoryId)
{
    subcategories_.removeBy(subcategoryId);
}

Category& Category::subcategoryBy(Id subcategoryId)
{
    return *subcategories_.entityBy(subcategoryId);
}

size_t Category::subcategoriesCount() const
{
    return subcategories_.count();
}

std::weak_ptr<Category> Category::parentCategory() const
{
    return parentCategory_;
}

void Category::setParentCategory(std::shared_ptr<Category>&& parentCategory)
{
    assert(parentCategory);

    parentCategory_ = std::move(parentCategory);
}
