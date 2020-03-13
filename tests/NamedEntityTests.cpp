#include "NamedEntity.hpp"
#include "Utils.hpp"

const std::vector<std::string> UnicodeNames{"Максим", "Zwölf", "Γαζέες", "Árvíztűrő"};

class UnicodeNameTests : public testing::TestWithParam<std::string>
{
};

TEST(NamedEntityTests, CreateWithUniqueIdAndNameWithoutWalletsAndCategories)
{
    NamedEntity acc{DefaultName};

    ASSERT_EQ(acc.name(), DefaultName);
}

TEST(NamedEntityTests, CreateWithEmptyNameShouldThrowException)
{
    ASSERT_THROW(NamedEntity({}), NamedEntity::EmptyNameError);
}

TEST_P(UnicodeNameTests, CreateWithUnicodeName)
{
    NamedEntity acc{GetParam()};

    ASSERT_EQ(acc.name(), GetParam());
}

INSTANTIATE_TEST_CASE_P(Suite, UnicodeNameTests, testing::ValuesIn(UnicodeNames));

TEST(NamedEntityTests, ChangeNamedEntityName)
{
    const std::string NewName = DefaultName + "New";
    NamedEntity acc{DefaultName};

    acc.setName(NewName);

    ASSERT_EQ(acc.name(), NewName);
}

TEST(NamedEntityTests, ChangeNamedEntityNameToEmptyShouldThrowException)
{
    NamedEntity acc{DefaultName};

    ASSERT_THROW(acc.setName({}), NamedEntity::EmptyNameError);
}
