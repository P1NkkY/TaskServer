#pragma once

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <optional>

namespace common {
namespace describe {

/**
 * @brief Returns an enumerator value as name. If the value does not correspond
 * to a named value, the function returns "Unknown"
 */
template <typename E>
constexpr char const* EnumToString(E e) {
    char const* r = "Unknown";

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E>>(
        [&](auto D) {
            if (e == D.value) {
                r = D.name;
            }
        });

    return r;
}

/**
 * @brief Returns an enum from its string representation.
 */
template <typename E>
std::optional<E> EnumFromString(const std::string& s) {
    std::optional<E> result;

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E>>(
        [&](auto D) {
            if (s == D.name) {
                result = static_cast<E>(D.value);
            }
        });

    return result;
}

}  // namespace describe
}  // namespace common
