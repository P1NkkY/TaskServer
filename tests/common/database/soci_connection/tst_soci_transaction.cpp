#include <gtest/gtest.h>
#include <soci/sqlite3/soci-sqlite3.h>

#include <filesystem>

#include "soci_transaction.h"
#include "utils/test_setup.h"

using namespace common::database;

class SociTransactionTest : public ::testing::Test {
   protected:
    void SetUp() override {
        connection_string_ = utils::GetFullTestName() + ".db";
        sql_.open(soci::sqlite3, connection_string_);
        sql_ << "CREATE TABLE test_table (id INTEGER PRIMARY KEY, value TEXT)";
    }

    void TearDown() override {
        sql_.close();
        if (std::filesystem::exists(connection_string_)) {
            std::filesystem::remove(connection_string_);
        }
    }

    bool RecordExists(int id) {
        int count = 0;
        sql_ << "SELECT COUNT(*) FROM test_table WHERE id = :id",
            soci::into(count), soci::use(id);

        return count > 0;
    }

   protected:
    std::string connection_string_;
    soci::session sql_;
};

TEST_F(SociTransactionTest, RecordShouldExistsAfterCommit) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    sql_ << "INSERT INTO test_table (id, value) VALUES (1, 'test')";
    transaction->Commit();

    EXPECT_TRUE(RecordExists(1));
}

TEST_F(SociTransactionTest, RecordShouldNotExistsAfterRollback) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    sql_ << "INSERT INTO test_table (id, value) VALUES (1, 'test')";
    transaction->Rollback();

    EXPECT_FALSE(RecordExists(1));
}

TEST_F(SociTransactionTest, ShouldAutoRollbackOnDestructorIfNotCommited) {
    {
        auto transaction = std::make_unique<SociTransaction>(sql_);
        sql_ << "INSERT INTO test_table (id, value) VALUES (1, 'test')";
    }

    EXPECT_FALSE(RecordExists(1));
}

TEST_F(SociTransactionTest, ShouldThrowWhenDoubleCommit) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    transaction->Commit();

    EXPECT_THROW(transaction->Commit(), soci::soci_error);
}

TEST_F(SociTransactionTest, ShouldThrowWhenDoubleRollback) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    transaction->Rollback();

    EXPECT_THROW(transaction->Rollback(), soci::soci_error);
}

TEST_F(SociTransactionTest, ShouldThrowWhenCommitAfterRollback) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    transaction->Rollback();

    EXPECT_THROW(transaction->Commit(), soci::soci_error);
}

TEST_F(SociTransactionTest, ShouldThrowWhenRollbackAfterCommit) {
    auto transaction = std::make_unique<SociTransaction>(sql_);
    transaction->Commit();

    EXPECT_THROW(transaction->Rollback(), soci::soci_error);
}
