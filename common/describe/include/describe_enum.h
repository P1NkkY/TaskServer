#pragma once

#include <boost/describe.hpp>
#include <boost/mp11.hpp>

namespace common {
namespace describe {

/**
 * @brief Returns an enumerator value as name. If the value does not correspond
 * to a named value, the function returns "Unknown"
 */
template <typename E>
constexpr char const* EnumToString(E e) {
    char const* r = "Unknown";

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E> >(
        [&](auto D) {
            if (e == D.value) {
                r = D.name;
            }
        });

    return r;
}

}  // namespace describe
}  // namespace common
