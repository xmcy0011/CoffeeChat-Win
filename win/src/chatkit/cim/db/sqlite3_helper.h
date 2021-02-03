#ifndef _SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_
#define _SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_

#include <atomic>

#include "cim/base/noncopyable.h"
#include "cim/cim_dll.h"

#include <SQLiteCpp/SQLiteCpp.h>

namespace cim {
    namespace db {
        /** @class SqliteHelper
          * @brief sqlite3辅助类，主要用于初始化表结构等
          * @author fei.xu
          * @date 2021/2/2
          */
        class SqliteHelper: noncopyable {
          public:
            static SqliteHelper* getInstance();

            bool init();
            void cleanup();

            std::shared_ptr<SQLite::Database> getConn() const;

          private:
            SqliteHelper();
            ~SqliteHelper();

            std::shared_ptr<SQLite::Database> db_;
            std::atomic_bool db_is_open_;
        };
    }
}

#endif//_SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_