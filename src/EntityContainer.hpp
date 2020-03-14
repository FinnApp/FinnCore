#pragma once

#include "Id.hpp"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

/*!
 * \brief The EntityNotFound struct
 */
struct EntityNotFound : std::runtime_error
{
    /*!
     * \brief EntityNotFound
     * \param id
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
     * \brief Simplifies entity search in the container with UniqueEntity
     */
    class IdPredicate
    {
    public:
        /*!
         * \brief Constructs predicate with target \p id
         */
        IdPredicate(Id id) : id_(id) {}

        /*!
         *  \brief Compares \p uniqueEntity id with target id
         */
        template <typename Entity>
        bool operator()(const Entity& uniqueEntity)
        {
            return uniqueEntity.id() == id_;
        }

        /*!
         *  \brief Compares \p uniqueEntity shared pointer id with target id
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
     * \brief Moves entity to container
     */
    void add(T&& entity)
    {
        entities_.emplace_back(std::move(entity));
    }

    /*!
     * \brief begin
     * \return
     */
    typename std::vector<T>::iterator begin()
    {
        return entities_.begin();
    }

    /*!
     * \brief end
     * \return
     */
    typename std::vector<T>::iterator end()
    {
        return entities_.end();
    }

    /*!
     * \brief cbegin
     * \return
     */
    typename std::vector<T>::const_iterator begin() const
    {
        return entities_.begin();
    }

    /*!
     * \brief cend
     * \return
     */
    typename std::vector<T>::const_iterator end() const
    {
        return entities_.end();
    }

    /*!
     * \brief Copies entity to container
     */
    void add(const T& entity)
    {
        entities_.emplace_back(entity);
    }

    /*!
     * \brief Removes entity with \p id from container
     */
    void removeBy(Id id)
    {
        entities_.erase(std::remove_if(entities_.begin(), entities_.end(), IdPredicate{id}), entities_.end());
    }

    /*!
     * \brief Retrives the entity with \p id from container
     * \return Reference to existing entity
     * \exception NotFound is thrown if entity with \p id isn't found in the container
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
