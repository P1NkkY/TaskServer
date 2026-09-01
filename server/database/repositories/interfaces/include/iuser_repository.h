#pragma once

#include <chrono>
#include <optional>
#include <string>

namespace database {
namespace repo {

struct User {
    int id_;
    std::string username_;
    std::chrono::system_clock::time_point created_at_;
};

class IUserRepository {
   public:
    virtual ~IUserRepository() = default;

    /**
     * @brief Создать пользователя.
     *
     * @param user
     */
    virtual void Create(const User& user) = 0;

    /**
     * @brief Получить текущего юзера по id.
     *
     * @param user_id
     *
     * @return std::optional<User>
     */
    virtual std::optional<User> Get(int user_id) const = 0;

    /**
     * @brief Обновить информацию о юзере.
     *
     * @param user
     */
    virtual void Update(const User& user) = 0;

    /**
     * @brief Удалить юзера по id.
     *
     * @param user_id
     */
    virtual void Remove(int user_id) = 0;
};

}  // namespace repo
}  // namespace database