#include "pch.h"
#include "sqlite3_helper.h"

#include "cim/cim.h"
#include "base/file/file_util.h"
#include "base/util/string_util.h"

#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>

namespace cim {
    namespace db {

#define CREATE_SQL_USER_CONFIG "CREATE TABLE [im_user_config](" \
			"[id] INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"\
			"[key] VARCHAR(64) NOT NULL,"\
			"[value] VARCHAR(128) NOT NULL,"\
			"[reserved1] VARCHAR(32),"\
			"[reserved2] VARCHAR(32));"\

#define CREATE_SQL_INDEX_USER_CONFIG "CREATE UNIQUE INDEX[im_index_key]"\
										"ON[im_user_config]("\
										"[key]);"\

        const std::string kTableNameUserConfig = "im_user_config";

        SqliteHelper* SqliteHelper::getInstance() {
            static SqliteHelper instance;
            return &instance;
        }

        SqliteHelper::SqliteHelper() {

        }

        SqliteHelper::~SqliteHelper() {

        }

        bool createConfigTable(const std::unique_ptr<SQLite::Database>& db);

        bool SqliteHelper::init() {
            // check db file exist

            std::wstring filename = cim::getChatKitConfig().appConfig.app_data_dir  + L"\\" + kDefaultAppDataFilename;
            std::unique_ptr<SQLite::Database> db = nullptr;

            if (!nbase::FilePathIsExist(filename, false)) {
                db = std::make_unique<SQLite::Database>(nbase::UTF16ToUTF8(filename), SQLite::OPEN_CREATE);

            } else {
                db = std::make_unique<SQLite::Database>(nbase::UTF16ToUTF8(filename), SQLite::OPEN_READONLY);
            }

            if (!createConfigTable(db)) {
                return false;
            }

            return true;
        }

        bool createConfigTable(const std::unique_ptr<SQLite::Database>& db) {
            if (!db->tableExists(kTableNameUserConfig)) {
                std::string sql = CREATE_SQL_USER_CONFIG;

                if (db->exec(sql) > 0) {

                }


            }

            return false;
        }
    }
}

