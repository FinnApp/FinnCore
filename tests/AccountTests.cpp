#include "Utils.hpp"

#include "Account.hpp"
#include "Category.hpp"
#include "Wallet.hpp"

TEST(AccountTests, CreateWithUniqueIdAndNameWithoutWalletsAndCategories)
{
    Account acc{DefaultId, DefaultName};

    ASSERT_EQ(acc.id(), DefaultId);
    ASSERT_EQ(acc.name(), DefaultName);
    ASSERT_EQ(acc.walletsCount(), 0);
    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, AddWalletShouldIncreaseTheNumberOfWallets)
{
    Account acc{DefaultId, DefaultName};

    acc.addWallet(Wallet{DefaultId, DefaultName});

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, GetExistingWalletById)
{
    Account acc{DefaultId, DefaultName};

    acc.addWallet(Wallet{DefaultId, DefaultName});
    auto& wallet = acc.walletBy(DefaultId);

    ASSERT_EQ(wallet.id(), DefaultId);
    ASSERT_EQ(wallet.name(), DefaultName);
}

TEST(AccountTests, GetNonExistingWalletShouldThrowException)
{
    Account acc{DefaultId, DefaultName};

    acc.addWallet(Wallet{DefaultId, DefaultName});

    ASSERT_THROW(acc.walletBy(DefaultId + 1), Account::InvalidWallet);
}

TEST(AccountTests, RemoveWalletShouldDecreaseTheNumberOfWallets)
{
    Account acc{DefaultId, DefaultName};

    acc.addWallet(Wallet{DefaultId, DefaultName});
    acc.removeWalletBy(DefaultId);

    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveWalletOnEmptyNumberOfWalletsShouldDoNothing)
{
    Account acc{DefaultId, DefaultName};

    acc.removeWalletBy(DefaultId);

    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveNotExistingWalletShouldDoNothing)
{
    Account acc{DefaultId, DefaultName};

    acc.addWallet(Wallet{DefaultId, DefaultName});
    acc.removeWalletBy(DefaultId + 1);

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, AddCategoryShouldIncreaseTheNumberOfCategories)
{
    Account acc{DefaultId, DefaultName};

    acc.addCategory(std::make_shared<Category>(DefaultId, DefaultName));

    ASSERT_EQ(acc.categoriesCount(), 1);
}

TEST(AccountTests, AddNonRootCategoryShouldThrowException)
{
    Account acc{DefaultId, DefaultName};

    auto rootCategory = std::make_shared<Category>(DefaultId, DefaultName);
    auto nonRootCategory = std::make_shared<Category>(DefaultId + 1, DefaultName);
    rootCategory->addSubcategory(nonRootCategory);

    ASSERT_THROW(acc.addCategory(std::move(nonRootCategory)), Account::NonRootCateogry);
}

TEST(AccountTests, GetExistingCategoryById)
{
    Account acc{DefaultId, DefaultName};

    acc.addCategory(std::make_shared<Category>(DefaultId, DefaultName));
    auto& category = acc.categoryBy(DefaultId);

    ASSERT_EQ(category.id(), DefaultId);
    ASSERT_EQ(category.name(), DefaultName);
}

TEST(AccountTests, GetNonExistingCategoryShouldThrowException)
{
    Account acc{DefaultId, DefaultName};

    acc.addCategory(std::make_shared<Category>(DefaultId, DefaultName));

    ASSERT_THROW(acc.categoryBy(DefaultId + 1), Account::InvalidCategory);
}

TEST(AccountTests, RemoveCategoryShouldDecreaseTheNumberOfCategories)
{
    Account acc{DefaultId, DefaultName};

    acc.addCategory(std::make_shared<Category>(DefaultId, DefaultName));
    acc.removeCategoryBy(DefaultId);

    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, RemovCategoryOnEmptyNumberOfCategoriesShouldDoNothing)
{
    Account acc{DefaultId, DefaultName};

    acc.removeCategoryBy(DefaultId);

    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, RemoveNotExistingCategoryShouldDoNothing)
{
    Account acc{DefaultId, DefaultName};

    acc.addCategory(std::make_shared<Category>(DefaultId, DefaultName));
    acc.removeCategoryBy(DefaultId + 1);

    ASSERT_EQ(acc.categoriesCount(), 1);
}
