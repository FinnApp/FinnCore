#include "Utils.hpp"

#include "Account.hpp"
#include "Category.hpp"
#include "Wallet.hpp"

const std::string DefaultAccountName{"Maxim"};
const std::vector<std::string> UnicodeNames{"Максим", "Zwölf", "Γαζέες", "Árvíztűrő"};

class AccountUnicodeNameTests : public testing::TestWithParam<std::string>
{
};

TEST(AccountTests, CreateWithUniqueIdAndNameWithoutWalletsAndCategories)
{
    Account acc{DefaultId, DefaultAccountName};

    ASSERT_EQ(acc.id(), DefaultId);
    ASSERT_EQ(acc.name(), DefaultAccountName);
    ASSERT_EQ(acc.walletsCount(), 0);
    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, CreateWithEmptyNameShouldThrowException)
{
    ASSERT_THROW(Account(DefaultId, {}), Account::EmptyNameError);
}

TEST_P(AccountUnicodeNameTests, CreateWithUnicodeName)
{
    Account acc{DefaultId, GetParam()};

    ASSERT_EQ(acc.name(), GetParam());
}

INSTANTIATE_TEST_CASE_P(Suite, AccountUnicodeNameTests, testing::ValuesIn(UnicodeNames));

TEST(AccountTests, ChangeAccountName)
{
    const std::string NewName = DefaultAccountName + "New";
    Account acc{DefaultId, DefaultAccountName};

    acc.setName(NewName);

    ASSERT_EQ(acc.name(), NewName);
}

TEST(AccountTests, ChangeAccountNameToEmptyShouldThrowException)
{
    Account acc{DefaultId, DefaultAccountName};

    ASSERT_THROW(acc.setName({}), Account::EmptyNameError);
}

TEST(AccountTests, AddWalletShouldIncreaseTheNumberOfWallets)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addWallet(Wallet{DefaultId});

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, RemoveWalletShouldDecreaseTheNumberOfWallets)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addWallet(Wallet{DefaultId});
    acc.removeWalletBy(DefaultId);

    //    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveWalletOnEmptyNumberOfWalletsShouldDoNothing)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.removeWalletBy(DefaultId);

    ASSERT_EQ(acc.walletsCount(), 0);
}

TEST(AccountTests, RemoveNotExistingWalletShouldDoNothing)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addWallet(Wallet{DefaultId});
    acc.removeWalletBy(DefaultId + 1);

    ASSERT_EQ(acc.walletsCount(), 1);
}

TEST(AccountTests, AddCategoryShouldIncreaseTheNumberOfCategories)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addCategory(Category{DefaultId});

    ASSERT_EQ(acc.categoriesCount(), 1);
}

TEST(AccountTests, RemoveCategoryShouldDecreaseTheNumberOfCategories)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addCategory(Category{DefaultId});
    acc.removeCategoryBy(DefaultId);

    //    ASSERT_EQ(acc.categoriesCount(), 0);
}

TEST(AccountTests, RemoveNotExistingCategoryShouldDoNothing)
{
    Account acc{DefaultId, DefaultAccountName};

    acc.addCategory(Category{DefaultId});
    acc.removeCategoryBy(DefaultId + 1);

    ASSERT_EQ(acc.categoriesCount(), 1);
}
