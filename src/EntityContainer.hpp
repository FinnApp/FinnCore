#pragma once

#include "Id.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

/*!
 * \brief Exception is thrown is entity in container is not found
 */
struct EntityNotFound : std::runtime_error
{
    /*!
     * \param id is used in exception message
     */
    EntityNotFound(Id id) : std::runtime_error{"Entity with ID " + std::to_string(id) + " not found"} {}
};

/*!
 * \brief EntityContainer
 */
template <typename T>
class EntityContainer
{
    /*!
     * Simplifies entity search in the container with UniqueEntity
     */
    class IdPredicate
    {
    public:
        /*!
         * Constructs predicate with target \p id
         */
        IdPredicate(Id id) : id_(id) {}

        /*!
         * Compares \p uniqueEntity id with target id
         */
        template <typename Entity>
        bool operator()(const Entity& uniqueEntity)
        {
            return uniqueEntity.id() == id_;
        }

        /*!
         * Compares \p uniqueEntity shared pointer id with target id
         */
        template <typename Entity>
        bool operator()(const std::shared_ptr<Entity>& uniqueEntity)
        {
            return uniqueEntity->id() == id_;
        }

    private:
        Id id_;
    };

public:
    /*!
     * Moves entity to container
     */
    void add(T&& entity)
    {
        entities_.emplace_back(std::move(entity));
    }

    /*!
     * \return Iterator to the beginning of the container
     */
    typename std::vector<T>::iterator begin()
    {
        return entities_.begin();
    }

    /*!
     * \return Iterator to the end of the container
     */
    typename std::vector<T>::iterator end()
    {
        return entities_.end();
    }

    /*!
     * \return Constant iterator to the beginning of the container
     */
    typename std::vector<T>::const_iterator begin() const
    {
        return entities_.begin();
    }

    /*!
     * \return Constant iterator to the end of the container
     */
    typename std::vector<T>::const_iterator end() const
    {
        return entities_.end();
    }

    /*!
     * Copies entity to container
     */
    void add(const T& entity)
    {
        entities_.emplace_back(entity);
    }

    /*!
     * Removes entity with \p id from container
     */
    void removeBy(Id id)
    {
        entities_.erase(std::remove_if(entities_.begin(), entities_.end(), IdPredicate{id}), entities_.end());
    }

    /*!
     * Retrives the entity with \p id from container
     *
     * \return Reference to existing entity
     * \exception EntityNotFound is thrown if entity with \p id isn't found in the container
     */
    T& entityBy(Id id)
    {
        auto it = std::find_if(entities_.begin(), entities_.end(), IdPredicate{id});

        if (it == entities_.end()) throw EntityNotFound{id};

        return *it;
    }

    /*!
     * \return Number of entites in the EntityContainer
     */
    size_t count() const
    {
        return entities_.size();
    }

private:
    std::vector<T> entities_;
};
