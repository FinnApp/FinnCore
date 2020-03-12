#pragma once

#include "Id.hpp"

#include <cassert>
#include <set>

#include <iostream>

/*!
 * \brief Unique entity that's identified by unique ID. It cannot be copied but only moved.
 *
 * To use this class you need to inherit from it and specify the class you want to be unique.
 * Internally it tracks that all instances have unique IDs and no ambiguity happens.
 */
template <typename T>
class UniqueEntity
{
    static inline std::set<Id> ids_;

public:
    /*!
     * \brief Exception is thrown if entity with some ID already exists
     */
    struct SameIdError : std::runtime_error
    {
        /*!
         * \param existingId is used in exception message
         */
        SameIdError(Id existingId) : std::runtime_error{"Entity with " + std::to_string(existingId) + " already exists"}
        {
        }
    };

    /*!
     * \brief Exception is thrown if entity is created with invalid ID
     */
    struct InvalidIdError : std::runtime_error
    {
        InvalidIdError() : std::runtime_error{"ID should be non-negative"} {}
    };

    /*!
     * \brief Creates entity with unique ID
     * \exception SameIdError is thrown if entity with \p id already exists
     * \exception InvalidIdError is thrown if \p id is invalid
     */
    UniqueEntity(Id id) : id_{std::move(id)}
    {
        if (entityExists(id_)) throw SameIdError{id};
        if (!id_.valid()) throw InvalidIdError{};

        addEntityBy(id_);
    }

    /*!
     * \brief Destructor
     *
     * If ID is invalid it will do nothing
     */
    ~UniqueEntity()
    {
        if (id_.valid())
        {
            assert(entityExists(id_));

            removeEntityBy(id_);
        }
    }

    /*!
     * \brief Deleted copy constructor
     */
    UniqueEntity(const UniqueEntity&) = delete;

    /*!
     * \brief Deleted copy assignment
     */
    UniqueEntity& operator=(const UniqueEntity&) = delete;

    /*!
     * \brief Move constructor
     * \exception InvalidIdError is thrown if \p other.id() is invaid
     */
    UniqueEntity(UniqueEntity&& other) : id_{std::move(other.id_)}
    {
        if (!id_.valid()) throw InvalidIdError{};
    }

    /*!
     *
     * \brief Move assignment
     * \exception InvalidIdError is thrown if \p other.id() is invaid
     */
    UniqueEntity& operator=(UniqueEntity&& other)
    {
        if (!other.id_.valid()) throw InvalidIdError{};

        removeEntityBy(id_);

        id_ = std::move(other.id_);
    }

    /*!
     * Identifies the particular entity can be used to distinguish it. ID can be retrieved and stored for future use
     * until UniqueEntity deleted. Operations with deleted UniqueEnity ID are undefined
     *
     * \return UniqueEntity ID
     */
    Id id() const
    {
        return id_;
    }

private:
    bool entityExists(Id id)
    {
        return ids_.count(id) > 0;
    }

    void addEntityBy(Id id)
    {
        ids_.emplace(id);
    }

    void removeEntityBy(Id id)
    {
        ids_.erase(id);
    }

private:
    Id id_;
};
