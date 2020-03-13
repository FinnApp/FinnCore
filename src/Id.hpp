#pragma once

#include <stdexcept>

/*!
 * \brief Represents the identifier which can be used throughout the program.
 * ID is considered to be valid if its value is non-negative
 */
class Id
{
    static inline const int Invalid{-1};

public:
    /*!
     * \brief Default constructor
     *
     * Constructs default ID object which is invalid
     */
    Id() = default;

    /*!
     * \brief Constructor
     *
     * Non-explicit constructor which creates ID from integer
     */
    Id(int value);

    /*!
     * \brief Copy constructor
     */
    Id(const Id&) = default;

    /*!
     * \brief Copy assignment
     */
    Id& operator=(const Id&) = default;

    /*!
     * \brief Move constructor
     *
     * \p other entity becomes invalid after being moved
     */
    Id(Id&& other);

    /*!
     * \brief Move assignment
     *
     * \p other entity becomes invalid after being moved
     */
    Id& operator=(Id&& other);

    /*!
     * \return \b true if ID is non-negative
     */
    bool valid() const;

    /*!
     * \brief implicit conversion to integer
     */
    operator int() const;

private:
    int value_ = Invalid;
};

const Id InvalidId{-1};
