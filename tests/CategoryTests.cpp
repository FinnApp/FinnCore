#include "Utils.hpp"

#include "Category.hpp"

TEST(CategoryTests, CreateWithUniqueIdAndNameWithoutSubcategories)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    ASSERT_EQ(cat->id(), DefaultId);
    ASSERT_EQ(cat->name(), DefaultName);
    ASSERT_EQ(cat->subcategoriesCount(), 0);
    ASSERT_EQ(cat->parentCategory().lock(), nullptr);
}

TEST(CategoryTests, AddCategoryShouldIncreaseTheNumberOfCategories)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->addSubcategory(std::make_shared<Category>(DefaultId + 1, DefaultName));

    ASSERT_EQ(cat->subcategoriesCount(), 1);
}

TEST(CategoryTests, GetExistingSubcategoryById)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->addSubcategory(std::make_shared<Category>(DefaultId + 1, DefaultName));
    auto& subcategory = cat->subcategoryBy(DefaultId + 1);

    ASSERT_EQ(subcategory.id(), DefaultId + 1);
    ASSERT_EQ(subcategory.name(), DefaultName);
    ASSERT_EQ(subcategory.parentCategory().lock(), cat);
}

TEST(CategoryTests, GetNonExistingSubcategoryShouldThrowException)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->addSubcategory(std::make_shared<Category>(DefaultId + 1, DefaultName));

    ASSERT_THROW(cat->subcategoryBy(DefaultId), Category::SubcategoryNotFound);
}

TEST(CategoryTests, RemoveSubcategoryShouldDecreaseTheNumberOfSubcategories)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->addSubcategory(std::make_shared<Category>(DefaultId + 1, DefaultName));
    cat->removeSubcategoryBy(DefaultId + 1);

    ASSERT_EQ(cat->subcategoriesCount(), 0);
}

TEST(CategoryTests, RemovSubcategoryOnEmptyNumberOfSubcategoriesShouldDoNothing)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->removeSubcategoryBy(DefaultId);

    ASSERT_EQ(cat->subcategoriesCount(), 0);
}

TEST(CategoryTests, RemoveNotExistingSubcategoryShouldDoNothing)
{
    auto cat = std::make_shared<Category>(DefaultId, DefaultName);

    cat->addSubcategory(std::make_shared<Category>(DefaultId + 1, DefaultName));
    cat->removeSubcategoryBy(DefaultId);

    ASSERT_EQ(cat->subcategoriesCount(), 1);
}
