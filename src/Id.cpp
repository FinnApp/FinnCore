#include "Id.hpp"

#include <type_traits>

Id::Id(int value) : value_{value} {}

Id::Id(Id&& other)
{
    std::swap(value_, other.value_);
}

Id& Id::operator=(Id&& other)
{
    value_ = Invalid;
    std::swap(value_, other.value_);

    return *this;
}

bool Id::valid() const
{
    return value_ >= 0;
}

Id::operator int() const
{
    return value_;
}
