#include "Category.hpp"

#include <algorithm>
#include <cassert>

Category::SubcategoryNotFound::SubcategoryNotFound(Id categoryId) :
    std::runtime_error{"Subcategory with ID " + std::to_string(categoryId) + " not found"}
{
}

Category::Category(Id id, const std::string& name) : UniqueEntity{id}, NamedEntity{name} {}

void Category::addSubcategory(const std::shared_ptr<Category>& subcategory)
{
    assert(subcategory);

    subcategory->setParentCategory(shared_from_this());
    subcategories_.emplace_back(subcategory);
}

void Category::removeSubcategoryBy(Id subcategoryId)
{
    subcategories_.erase(std::remove_if(subcategories_.begin(), subcategories_.end(), IdPredicate{subcategoryId}),
                         subcategories_.end());
}

Category& Category::subcategoryBy(Id subcategoryId)
{
    auto it = std::find_if(subcategories_.begin(), subcategories_.end(), IdPredicate{subcategoryId});

    if (it == subcategories_.end()) throw SubcategoryNotFound{subcategoryId};

    return **it;
}

size_t Category::subcategoriesCount() const
{
    return subcategories_.size();
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
