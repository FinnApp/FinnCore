#pragma once

#include <stdexcept>
#include <string>

/*!
 * \brief Represents the named entity to reuse it in several places
 */
class NamedEntity
{
public:
    /*!
     * \brief Exception is thrown if name is empty
     */
    struct EmptyNameError : std::runtime_error
    {
        EmptyNameError();
    };

    /*!
     * \brief Constructor
     */
    NamedEntity(const std::string& name);

    /*!
     * \return Unicode Account name
     */
    const std::string& name() const;

    /*!
     * \param name Non-empty unicode string
     * \exception EmptyNameError is thrown if \p name is empty
     */
    void setName(const std::string& name);

private:
    std::string name_;
};
