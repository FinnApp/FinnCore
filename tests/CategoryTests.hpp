#pragma once

#include "Utils.hpp"

#include "Category.hpp"

inline std::shared_ptr<Category> createCategory()
{
    return std::make_shared<Category>(DefaultId, DefaultName);
}

inline std::shared_ptr<Category> createCategory(Id id, const std::string& name)
{
    return std::make_shared<Category>(id, name);
}
