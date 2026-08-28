#pragma once

#include <chrono>
#include <string>

namespace database {
namespace repo {

struct User {
    int id_;
    std::string username_;
    std::chrono::system_clock::time_point created_at_;
};

class IUserRepository {};

}  // namespace repo
}  // namespace database