#include "pch.h"
#include "sqlite3_helper.h"

#include "cim/cim.h"
#include "cim/base/Log.h"

#include "base/file/file_util.h"
#include "base/util/string_util.h"

#include "cim/db/config_dao.h"

namespace cim {
    namespace db {
        SqliteHelper* SqliteHelper::getInstance() {
            static SqliteHelper instance;
            return &instance;
        }

        SqliteHelper::SqliteHelper() {

        }

        SqliteHelper::~SqliteHelper() {

        }

        bool SqliteHelper::init() {
            std::wstring filename = cim::getChatKitConfig().appConfig.app_data_dir + L"\\" + kDefaultAppDataFilename;

            if (cim::getChatKitConfig().appConfig.app_data_dir.empty()) {
                filename = kDefaultAppDataFilename;

            } else {
                if (!nbase::FilePathIsExist(cim::getChatKitConfig().appConfig.app_data_dir, true)) {
                    nbase::CreateDirectoryW(cim::getChatKitConfig().appConfig.app_data_dir);
                }
            }

            try {
                std::string tempName = nbase::UTF16ToUTF8(filename);

                // check db file exist
                if (!nbase::FilePathIsExist(filename, false)) {
                    db_ = std::make_shared<SQLite::Database>(tempName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

                } else {
                    db_ = std::make_shared<SQLite::Database>(tempName, SQLite::OPEN_READWRITE);
                }

            } catch (const std::exception& e) {
                LogWarn("open sqlite error:{}", e.what());
                return false;
            }

            if (!ConfigDao::getInstance()->createTable()) {
                return false;
            }

            db_is_open_ = true;
            return true;
        }

        void SqliteHelper::cleanup() {
            if (db_is_open_) {
                db_is_open_ = false;

                // auto close
                db_ = nullptr;
            }
        }

        std::shared_ptr<SQLite::Database> SqliteHelper::getConn() const {
            assert(db_ != nullptr);
            return db_;
        }
    }
}

