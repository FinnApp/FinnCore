#pragma once

#include <stdexcept>

/*!
 * \brief Exception is thrown if nullptr entity used and it's considered invalid
 */
template <typename Entity>
struct NullEntityError : std::runtime_error
{
    /*!
     * \param message Exception message
     */
    NullEntityError(const std::string& message) : std::runtime_error{message} {}
};
