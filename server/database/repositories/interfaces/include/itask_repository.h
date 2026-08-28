#pragma once

#include <chrono>
#include <string>

namespace database {
namespace repo {

enum class TaskStatus {
    Completed,   ///< Выполнено
    InProgress,  ///< Ещё не выполнено
    Canceled     ///< Отменено
};

struct Task {
    int id_;
    int owner_id_;
    std::string title_;
    std::string description_;
    TaskStatus status_;
    std::chrono::system_clock::time_point created_at_;
};

class ITaskRepository {};

}  // namespace repo
}  // namespace database