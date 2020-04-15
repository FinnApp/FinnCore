#include "CategoryTests.hpp"

TEST(CategoryTests, CreateWithUniqueIdAndNameWithoutSubcategories)
{
    auto cat = createCategory();

    ASSERT_EQ(cat->id(), DefaultId);
    ASSERT_EQ(cat->name(), DefaultName);
    ASSERT_EQ(cat->subcategoriesCount(), 0);
    ASSERT_EQ(cat->parentCategory().lock(), nullptr);
}

TEST(CategoryTests, AddCategoryShouldIncreaseTheNumberOfCategories)
{
    auto cat = createCategory();

    cat->addSubcategory(createCategory(DefaultId + 1, DefaultName));

    ASSERT_EQ(cat->subcategoriesCount(), 1);
}

TEST(CategoryTests, AddNullptrCategoryShouldThrowException)
{
    auto cat = createCategory();

    ASSERT_THROW(cat->addSubcategory(nullptr), NullEntityError<Category>);
}

TEST(CategoryTests, GetExistingSubcategoryById)
{
    auto cat = createCategory();

    cat->addSubcategory(createCategory(DefaultId + 1, DefaultName));
    auto& subcategory = cat->subcategoryBy(DefaultId + 1);

    ASSERT_EQ(subcategory.id(), DefaultId + 1);
    ASSERT_EQ(subcategory.name(), DefaultName);
    ASSERT_EQ(subcategory.parentCategory().lock(), cat);
}

TEST(CategoryTests, GetNonExistingSubcategoryShouldThrowException)
{
    auto cat = createCategory();

    cat->addSubcategory(createCategory(DefaultId + 1, DefaultName));

    ASSERT_THROW(cat->subcategoryBy(DefaultId), EntityNotFound);
}

TEST(CategoryTests, RemoveSubcategoryShouldDecreaseTheNumberOfSubcategories)
{
    auto cat = createCategory();

    cat->addSubcategory(createCategory(DefaultId + 1, DefaultName));
    cat->removeSubcategoryBy(DefaultId + 1);

    ASSERT_EQ(cat->subcategoriesCount(), 0);
}

TEST(CategoryTests, RemovSubcategoryOnEmptyNumberOfSubcategoriesShouldDoNothing)
{
    auto cat = createCategory();

    cat->removeSubcategoryBy(DefaultId);

    ASSERT_EQ(cat->subcategoriesCount(), 0);
}

TEST(CategoryTests, RemoveNotExistingSubcategoryShouldDoNothing)
{
    auto cat = createCategory();

    cat->addSubcategory(createCategory(DefaultId + 1, DefaultName));
    cat->removeSubcategoryBy(DefaultId);

    ASSERT_EQ(cat->subcategoriesCount(), 1);
}
