#pragma once

#include "itransaction.h"
#include "soci/transaction.h"

namespace common {
namespace database {

class SociTransaction : public ITransaction {
   public:
    explicit SociTransaction(soci::session& sql);

    void Commit() override;

    void Rollback() override;

   private:
    soci::transaction transaction_;
};

}  // namespace database

}  // namespace common
