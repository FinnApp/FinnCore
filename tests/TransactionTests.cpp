#include "TransactionTests.hpp"

const std::vector<std::pair<double, double>> TransactionAmounts = {{1.5678, 1.57},
                                                                   {-1.5678, -1.57},
                                                                   {1.566, 1.57},
                                                                   {-1.566, -1.57},
                                                                   {1.565, 1.57},
                                                                   {-1.565, -1.57},
                                                                   {1.564, 1.56},
                                                                   {-1.564, -1.56},
                                                                   {1.56, 1.56},
                                                                   {-1.56, -1.56},
                                                                   {1.5, 1.50},
                                                                   {-1.5, -1.50}};

class RoundAmountTests : public testing::TestWithParam<std::pair<double, double>>
{
};

TEST(TransactionTests, CreateWithWalletCategoryDateAndAmount)
{
    auto wallet = createWallet();
    auto category = createCategory();
    auto trans = createTransaction(DefaultId, DefaultAmount, wallet, category, DefaultCreationDT);

    ASSERT_EQ(trans->id(), DefaultId);
    ASSERT_EQ(trans->amount(), DefaultAmount);
    ASSERT_EQ(trans->type(), Transaction::Type::Income);
    ASSERT_EQ(trans->dateTime(), DefaultCreationDT);
    ASSERT_EQ(trans->date(), DefaultCreationDate);
    ASSERT_EQ(trans->time(), DefaultCreationTime);
    ASSERT_EQ(trans->wallet().lock(), wallet);
    ASSERT_EQ(trans->category().lock(), category);
    ASSERT_EQ(trans->description(), std::string{});
}

TEST(TransactionTests, CreateWithEmptyWalletShouldThrowException)
{
    ASSERT_THROW(createTransaction(DefaultId, DefaultAmount, {}, createCategory(), DefaultCreationDT),
                 NullEntityError<Wallet>);
}

TEST(TransactionTests, CreateWithEmptyCategoryShouldThrowException)
{
    ASSERT_THROW(createTransaction(DefaultId, DefaultAmount, createWallet(), {}, DefaultCreationDT),
                 NullEntityError<Category>);
}

TEST(TransactionTests, CreateWithZeroAmountShouldThrowException)
{
    ASSERT_THROW(createTransaction(DefaultId, 0, createWallet(), createCategory(), DefaultCreationDT),
                 Transaction::ZeroAmountError);
}

TEST(TransactionTests, CreateWithInvalidDtShouldThrowException)
{
    ASSERT_THROW(createTransaction(DefaultId, DefaultAmount, createWallet(), createCategory(), {}),
                 Transaction::InvalidDateTimeError);
}

TEST(TransactionTests, CreateWithPositiveAmountTypeShouldBeIncome)
{
    auto trans = createTransaction(DefaultId, 1, createWallet(), createCategory(), DefaultCreationDT);

    ASSERT_EQ(trans->type(), Transaction::Type::Income);
}

TEST(TransactionTests, CreateWithNegativeAmountTypeShouldBeExpense)
{
    auto trans = createTransaction(DefaultId, -1, createWallet(), createCategory(), DefaultCreationDT);

    ASSERT_EQ(trans->type(), Transaction::Type::Expense);
}

TEST_P(RoundAmountTests, CreateAndRoundAmountTo2DecimalPlaces)
{
    auto trans = createTransaction(DefaultId, GetParam().first, createWallet(), createCategory(), DefaultCreationDT);

    ASSERT_EQ(trans->amount(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(CreateSuite, RoundAmountTests, testing::ValuesIn(TransactionAmounts));

TEST(TransactionTests, UpdateWithZeroAmountShouldThrowException)
{
    auto trans = createTransaction();

    ASSERT_THROW(trans->updateAmount(0), Transaction::ZeroAmountError);
}

TEST(TransactionTests, UpdateWithPositiveAmountTypeShouldBeIncome)
{
    auto trans = createTransaction();

    trans->updateAmount(1);

    ASSERT_EQ(trans->type(), Transaction::Type::Income);
}

TEST(TransactionTests, UpdateWithNegativeAmountTypeShouldBeExpense)
{
    auto trans = createTransaction();

    trans->updateAmount(-1);

    ASSERT_EQ(trans->type(), Transaction::Type::Expense);
}

TEST_P(RoundAmountTests, UpdateAndRoundAmountTo2DecimalPlaces)
{
    auto trans = createTransaction();

    trans->updateAmount(GetParam().first);

    ASSERT_EQ(trans->amount(), GetParam().second);
}

INSTANTIATE_TEST_CASE_P(UpdateSuite, RoundAmountTests, testing::ValuesIn(TransactionAmounts));

TEST(TransactionTests, UpdateWithInvalidDtShouldThrowException)
{
    auto trans = createTransaction();

    ASSERT_THROW(trans->updateDateTime({}), Transaction::InvalidDateTimeError);
}

TEST(TransactionTests, UpdateWithValidDt)
{
    Date date{2020, 1, 1};
    Time time{1, 0, 0};
    DateTime dt{date, time};
    auto trans = createTransaction();

    trans->updateDateTime(dt);

    ASSERT_EQ(trans->dateTime(), dt);
    ASSERT_EQ(trans->date(), date);
    ASSERT_EQ(trans->time(), time);
}

TEST(TransactionTests, UpdateWithNewDescription)
{
    auto trans = createTransaction();
    std::string desr{"new descri[tion"};

    trans->updateDescription(desr);

    ASSERT_EQ(trans->description(), desr);
}

TEST(TransactionTests, UpdateWithInvalidCategoryShouldThrowException)
{
    auto trans = createTransaction();

    ASSERT_THROW(trans->updateCategory({}), NullEntityError<Category>);
}

TEST(TransactionTests, RemoveAssignedCategoryShouldMadeTransactionUnassignedToAnyCategory)
{
    auto category = createCategory();
    auto trans = createTransaction(category);

    category.reset();

    ASSERT_TRUE(trans->category().expired());
}

TEST(TransactionTests, UpdateWithValidCategoryShouldChangeTheAssginedCategory)
{
    auto previousCategory = createCategory(Id{0}, DefaultName);
    auto newCategory = createCategory(Id{1}, DefaultName);
    auto trans = createTransaction(previousCategory);

    trans->updateCategory(newCategory);

    ASSERT_EQ(trans->category().lock(), newCategory);
}

TEST(TransactionTests, UpdateWithInvalidWalletShouldThrowException)
{
    auto trans = createTransaction();

    ASSERT_THROW(trans->updateWallet({}), NullEntityError<Wallet>);
}

TEST(TransactionTests, UpdateWithNewWalletShouldAddItToNewAndRemoveFromPrevious)
{
    auto previousWallet = createWallet(Id{0});
    auto newWallet = createWallet(Id{1});
    previousWallet->addTransaction(createTransaction(previousWallet));
    auto& trans = previousWallet->transactionBy(DefaultId);

    trans.updateWallet(newWallet);

    ASSERT_EQ(trans.wallet().lock(), newWallet);
    ASSERT_EQ(&newWallet->transactionBy(DefaultId), &trans);
    ASSERT_THROW(previousWallet->transactionBy(DefaultId), EntityNotFound);
}
