#pragma once

namespace common {
namespace database {

/**
 * @brief Базовый интерфейс транзакции базы данных.
 *
 */
class ITransaction {
   public:
    virtual ~ITransaction() = default;

    /**
     * @brief Фиксирует все изменения, сделанные в рамках транзакции
     *
     */
    virtual void Commit() = 0;

    /**
     * @brief Отменяет все изменения, сделанные в рамках транзакции с момента её
     * начала.
     *
     */
    virtual void Rollback() = 0;
};

}  // namespace database
}  // namespace common