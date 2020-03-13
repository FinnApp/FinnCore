#include "NamedEntity.hpp"

NamedEntity::EmptyNameError::EmptyNameError() : std::runtime_error{"Account name shouldn't be empty"} {}

NamedEntity::NamedEntity(const std::string& name)
{
    setName(name);
}

const std::string& NamedEntity::name() const
{
    return name_;
}

void NamedEntity::setName(const std::string& name)
{
    if (name.empty()) throw EmptyNameError{};

    name_ = name;
}
