#include "soci_transaction.h"

namespace common::database {

SociTransaction::SociTransaction(soci::session& sql) : transaction_(sql) {}

void SociTransaction::Commit() { transaction_.commit(); }

void SociTransaction::Rollback() { transaction_.rollback(); }

}  // namespace common::database