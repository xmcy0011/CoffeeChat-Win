#include "pch.h"
#include "sqlite3_helper.h"

#include "cim/cim.h"
#include "cim/base/Log.h"

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

#define INSERT_DATA_USER_CONFIG_IP			"insert into im_user_config(key,value) values('serverIp','127.0.0.1')"
#define INSERT_DATA_USER_CONFIG_MSG_PORT	"insert into im_user_config(key,value) values('msgPort','8000')"
#define INSERT_DATA_USER_CONFIG_HTTP_PORT	"insert into im_user_config(key,value) values('httpPort','18080')"

        const std::string kTableNameUserConfig = "im_user_config";

        SqliteHelper* SqliteHelper::getInstance() {
            static SqliteHelper instance;
            return &instance;
        }

        SqliteHelper::SqliteHelper() {

        }

        SqliteHelper::~SqliteHelper() {

        }

        void insertDefaultData(const std::unique_ptr<SQLite::Database>& db) noexcept {
            try {
                db->exec(INSERT_DATA_USER_CONFIG_IP);
                db->exec(INSERT_DATA_USER_CONFIG_MSG_PORT);
                db->exec(INSERT_DATA_USER_CONFIG_HTTP_PORT);

            } catch (const std::exception& e) {
                LogWarn("init default data error:{}", e.what());
            }
        }

        bool createConfigTable(const std::unique_ptr<SQLite::Database>& db) noexcept {
            if (db->tableExists(kTableNameUserConfig)) {
                LogInfo("table {} already exist", kTableNameUserConfig);

            } else {
                std::string sql = CREATE_SQL_USER_CONFIG;

                try {
                    db->exec(sql);
                    LogInfo("create table {} success", kTableNameUserConfig);

                    db->exec(CREATE_SQL_INDEX_USER_CONFIG);
                    LogInfo("create table index {} success", kTableNameUserConfig);

                } catch (const std::exception& e) {
                    LogWarn("sql error:{}", e.what());
                    return false;
                }

                insertDefaultData(db);
            }

            return true;
        }

        bool SqliteHelper::init() {
            // check db file exist

            std::wstring filename = cim::getChatKitConfig().appConfig.app_data_dir + L"\\" + kDefaultAppDataFilename;

            if (cim::getChatKitConfig().appConfig.app_data_dir.empty()) {
                filename = kDefaultAppDataFilename;
            }

            std::unique_ptr<SQLite::Database> db = nullptr;

            try {
                std::string tempName = nbase::UTF16ToUTF8(filename);

                if (!nbase::FilePathIsExist(filename, false)) {
                    db = std::make_unique<SQLite::Database>(tempName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

                } else {
                    db = std::make_unique<SQLite::Database>(tempName, SQLite::OPEN_READWRITE);
                }

            } catch (const std::exception& e) {
                LogWarn("open sqlite error:{}", e.what());
                return false;
            }

            if (!createConfigTable(db)) {
                return false;
            }

            return true;
        }
    }
}

