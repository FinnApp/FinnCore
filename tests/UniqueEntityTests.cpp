#include "UniqueEntity.hpp"
#include "Utils.hpp"

class Dummy
{
};

TEST(UniqueEntityTests, CreateEntitysWithDifferentIdsAndSameNamesShouldBeOk)
{
    UniqueEntity<Dummy> entity{DefaultId};
    UniqueEntity<Dummy> anotherEntity{DefaultId + 1};

    ASSERT_EQ(entity.id(), DefaultId);
    ASSERT_EQ(anotherEntity.id(), DefaultId + 1);
}

TEST(UniqueEntityTests, CreateEntitysWithInvalidIdShouldThrowException)
{
    ASSERT_THROW(UniqueEntity<Dummy>{InvalidId}, UniqueEntity<Dummy>::InvalidIdError);
}

TEST(UniqueEntityTests, CreateEntityWithExistingIdShouldThrowException)
{
    UniqueEntity<Dummy> entity{DefaultId};

    ASSERT_THROW(UniqueEntity<Dummy>{DefaultId}, UniqueEntity<Dummy>::SameIdError);
}

TEST(UniqueEntityTests, CreateEntityWithPreviouslyExistingIdShouldOk)
{
    {
        UniqueEntity<Dummy> entity{DefaultId};

        ASSERT_EQ(entity.id(), DefaultId);
    }

    UniqueEntity<Dummy> entity{DefaultId};

    ASSERT_EQ(entity.id(), DefaultId);
}

TEST(UniqueEntityTests, MoveConstructEntityFromValidEntity)
{
    UniqueEntity<Dummy> movedEntity{DefaultId};
    UniqueEntity<Dummy> entity{std::move(movedEntity)};

    ASSERT_EQ(entity.id(), DefaultId);
    ASSERT_EQ(movedEntity.id(), InvalidId);
}

TEST(UniqueEntityTests, MoveConstructEntityFromInvalidEntityShouldThrowException)
{
    UniqueEntity<Dummy> movedEntity{DefaultId};
    UniqueEntity<Dummy> validEntity{std::move(movedEntity)};

    ASSERT_THROW(UniqueEntity<Dummy>{std::move(movedEntity)}, UniqueEntity<Dummy>::InvalidIdError);
}

TEST(UniqueEntityTests, MoveAssignEntityFromValidEntity)
{
    UniqueEntity<Dummy> movedEntity{DefaultId};
    UniqueEntity<Dummy> entity{DefaultId + 1};

    entity = std::move(movedEntity);

    ASSERT_EQ(entity.id(), DefaultId);
    ASSERT_EQ(movedEntity.id(), InvalidId);
}

TEST(UniqueEntityTests, MoveAssignEntityFromInvalidEntityShouldThrowException)
{
    UniqueEntity<Dummy> movedEntity{DefaultId};
    UniqueEntity<Dummy> invalidEntity{DefaultId + 1};

    invalidEntity = std::move(movedEntity);

    ASSERT_THROW(invalidEntity = std::move(movedEntity), UniqueEntity<Dummy>::InvalidIdError);
}

TEST(UniqueEntityTests, CreateEntityWithMovedConstructedId)
{
    {
        UniqueEntity<Dummy> movedEntity{DefaultId};
        UniqueEntity<Dummy> entity{std::move(movedEntity)};
    }

    UniqueEntity<Dummy> entity{DefaultId};

    ASSERT_EQ(entity.id(), DefaultId);
}

TEST(UniqueEntityTests, CreateEntityWithMovedAssignedId)
{
    {
        UniqueEntity<Dummy> movedEntity{DefaultId};
        UniqueEntity<Dummy> entity{DefaultId + 1};

        entity = std::move(movedEntity);
    }

    UniqueEntity<Dummy> entity{DefaultId + 1};

    ASSERT_EQ(entity.id(), DefaultId + 1);
}

TEST(UniqueEntityTests, ReuseMovedEntity)
{
    UniqueEntity<Dummy> reusedMovedEntity{DefaultId};
    UniqueEntity<Dummy> movedEntity{std::move(reusedMovedEntity)};

    reusedMovedEntity = std::move(movedEntity);

    ASSERT_EQ(reusedMovedEntity.id(), DefaultId);
    ASSERT_EQ(movedEntity.id(), InvalidId);
}
