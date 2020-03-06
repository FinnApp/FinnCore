#include <gtest/gtest.h>

#include "Account.hpp"

TEST(AccountTests, DummyTest)
{
    ASSERT_EQ(Account::getCount(), 43);
}
