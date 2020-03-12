#include "Id.hpp"
#include "Utils.hpp"

TEST(IdTests, CreateValidId)
{
    Id id{1};

    ASSERT_TRUE(id.valid());
}

TEST(IdTests, CreateInvalidId)
{
    Id id{-1};

    ASSERT_FALSE(id.valid());
}

TEST(IdTests, CopyConstructId)
{
    Id id{1}, anotherId{id};

    ASSERT_TRUE(anotherId.valid());
    ASSERT_EQ(anotherId, id);
}

TEST(IdTests, CopyAssignId)
{
    Id id{1}, anotherId{2};

    anotherId = id;

    ASSERT_TRUE(anotherId.valid());
    ASSERT_EQ(anotherId, id);
}

TEST(IdTests, MoveConstructId)
{
    Id id{1}, anotherId{std::move(id)};

    ASSERT_TRUE(anotherId.valid());
    ASSERT_FALSE(id.valid());
    ASSERT_EQ(anotherId, 1);
    ASSERT_EQ(id, InvalidId);
}

TEST(IdTests, MoveAssignId)
{
    Id id{1}, anotherId{2};

    anotherId = std::move(id);

    ASSERT_TRUE(anotherId.valid());
    ASSERT_FALSE(id.valid());
    ASSERT_EQ(anotherId, 1);
    ASSERT_EQ(id, InvalidId);
}
