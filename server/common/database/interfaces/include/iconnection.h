#pragma once

#include <memory>

#include "itransaction.h"

namespace common {
namespace database {

class IConnection {
   public:
    virtual ~IConnection() = default;

    /**
     * @brief Закрывает соединение с базой данных.
     *
     */
    virtual void Close() = 0;

    /**
     * @brief Проверяет активность соединения с базой данных.
     */
    virtual bool IsConnected() const = 0;

    /**
     * @brief Создаёт класс-обёртку для работы с транзакциями.
     *
     * @return std::unique_ptr<ITransaction>
     */
    virtual std::unique_ptr<ITransaction> BeginTransaction() = 0;
};

}  // namespace database
}  // namespace common