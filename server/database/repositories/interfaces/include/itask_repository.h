#pragma once

#include <boost/describe.hpp>
#include <chrono>
#include <optional>
#include <string>
#include <vector>

namespace database {
namespace repo {

/**
 * @brief Статус задачи.
 *
 */
enum class TaskStatus {
    Completed,   ///< Выполнено
    InProgress,  ///< Ещё не выполнено
    Canceled     ///< Отменено
};

BOOST_DESCRIBE_ENUM(TaskStatus, Completed, InProgress, Canceled)

/**
 * @brief Информация о задаче.
 *
 */
struct Task {
    int id_;
    int user_id_;
    std::string title_;
    std::string description_;
    TaskStatus status_;
    std::chrono::system_clock::time_point created_at_;
};

/**
 * @brief CRUD
 *
 */
class ITaskRepository {
   public:
    virtual ~ITaskRepository() = default;

    /**
     * @brief Создать задачу.
     *
     * @param task
     */
    virtual void Create(const Task& task) = 0;

    /**
     * @brief Получить текущую задачу по id.
     *
     * @param task_id
     *
     * @return std::optional<Task>
     */
    virtual std::optional<Task> Get(int task_id) const = 0;

    /**
     * @brief Получить все задачи текущего пользователя
     *
     * @param user_id
     *
     * @return std::optional<std::vector<Task>>
     */
    virtual std::optional<std::vector<Task>> GetAll(int user_id) const = 0;

    /**
     * @brief Обновить информацию о задаче.
     *
     * @param task
     */
    virtual void Update(const Task& task) = 0;

    /**
     * @brief Удалить задачу по id.
     *
     * @param task_id
     */
    virtual void Remove(int task_id) = 0;

    /**
     * @brief Удалить все задачи пользователя.
     *
     * @param user_id
     */
    virtual void RemoveAll(int user_id) = 0;
};

}  // namespace repo
}  // namespace database