#include "CategoryTests.hpp"
#include "WalletTests.hpp"

#include "Account.hpp"

Account createAccount()
{
    return Account{DefaultId, DefaultName};
}

TEST(AccountTests, CreateWithUniqueIdAndNameWithoutWalletsAndCategories)
{
    auto acc = createAccount();

    ASSERT_EQ(acc.id(), DefaultId);
    ASSERT_EQ(acc.name(), DefaultName);
    ASSERT_EQ(acc.walletsCount(), 0);
    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, AddWalletShouldIncreaseTheNumberOfWallets)
{
    auto acc = createAccount();

    acc.addWallet(createWallet());

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, AddInvalidWalletShouldThrowException)
{
    auto acc = createAccount();

    ASSERT_THROW(acc.addWallet(nullptr), Account::InvalidWallet);
}

TEST(AccountTests, GetExistingWalletById)
{
    auto acc = createAccount();

    acc.addWallet(createWallet());
    auto& wallet = acc.walletBy(DefaultId);

    ASSERT_EQ(wallet.id(), DefaultId);
    ASSERT_EQ(wallet.name(), DefaultName);
}

TEST(AccountTests, GetNonExistingWalletShouldThrowException)
{
    auto acc = createAccount();

    acc.addWallet(createWallet());

    ASSERT_THROW(acc.walletBy(DefaultId + 1), EntityNotFound);
}

TEST(AccountTests, RemoveWalletShouldDecreaseTheNumberOfWallets)
{
    auto acc = createAccount();

    acc.addWallet(createWallet());
    acc.removeWalletBy(DefaultId);

    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveWalletOnEmptyNumberOfWalletsShouldDoNothing)
{
    auto acc = createAccount();

    acc.removeWalletBy(DefaultId);

    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveNotExistingWalletShouldDoNothing)
{
    auto acc = createAccount();

    acc.addWallet(createWallet());
    acc.removeWalletBy(DefaultId + 1);

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, AddCategoryShouldIncreaseTheNumberOfCategories)
{
    auto acc = createAccount();

    acc.addCategory(createCategory());

    ASSERT_EQ(acc.categoriesCount(), 1);
}

TEST(AccountTests, AddInvalidCategoryShouldThrowException)
{
    auto acc = createAccount();

    ASSERT_THROW(acc.addCategory(nullptr), Account::InvalidCategory);
}

TEST(AccountTests, AddNonRootCategoryShouldThrowException)
{
    auto acc = createAccount();

    auto rootCategory = createCategory();
    auto nonRootCategory = createCategory(DefaultId + 1, DefaultName);
    rootCategory->addSubcategory(nonRootCategory);

    ASSERT_THROW(acc.addCategory(std::move(nonRootCategory)), Account::NonRootCategory);
}

TEST(AccountTests, GetExistingCategoryById)
{
    auto acc = createAccount();

    acc.addCategory(createCategory());
    auto& category = acc.categoryBy(DefaultId);

    ASSERT_EQ(category.id(), DefaultId);
    ASSERT_EQ(category.name(), DefaultName);
}

TEST(AccountTests, GetNonExistingCategoryShouldThrowException)
{
    auto acc = createAccount();

    acc.addCategory(createCategory());

    ASSERT_THROW(acc.categoryBy(DefaultId + 1), EntityNotFound);
}

TEST(AccountTests, RemoveCategoryShouldDecreaseTheNumberOfCategories)
{
    auto acc = createAccount();

    acc.addCategory(createCategory());
    acc.removeCategoryBy(DefaultId);

    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, RemovCategoryOnEmptyNumberOfCategoriesShouldDoNothing)
{
    auto acc = createAccount();

    acc.removeCategoryBy(DefaultId);

    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, RemoveNotExistingCategoryShouldDoNothing)
{
    auto acc = createAccount();

    acc.addCategory(createCategory());
    acc.removeCategoryBy(DefaultId + 1);

    ASSERT_EQ(acc.categoriesCount(), 1);
}
