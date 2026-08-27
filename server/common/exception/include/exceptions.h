#pragma once

#include <iostream>

namespace common {
namespace exception {

/**
 * @brief Base exception indicating that a method/function is not yet
 * implemented but is planned in future releases.
 *
 */
class InDevelopment : public std::runtime_error {
   public:
    explicit InDevelopment(char const* const message)
        : std::runtime_error{message} {};
};

}  // namespace exception
}  // namespace common