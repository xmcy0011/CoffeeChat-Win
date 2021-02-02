#ifndef _SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_
#define _SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_

#include "cim/base/noncopyable.h"

namespace cim {
    namespace db {

        class SqliteHelper: noncopyable {
          public:
            static SqliteHelper* getInstance();

            bool init();

          private:
            SqliteHelper();
            ~SqliteHelper();
        };
    }
}

#endif//_SQLITE3_HELPER_36486BE7_10CD_4F30_8244_1F8D4A485D4A_