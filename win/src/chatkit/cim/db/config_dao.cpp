#include "pch.h"
#include "cim/db/config_dao.h"
#include "cim/db/sqlite3_helper.h"
#include "cim/base/Log.h"

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
#define INSERT_DATA_USER_CONFIG_MSG_PORT	"insert into im_user_config(key,value) values('gatePort','8000')"
#define INSERT_DATA_USER_CONFIG_HTTP_PORT	"insert into im_user_config(key,value) values('httpPort','18080')"

        const std::string kTableNameUserConfig = "im_user_config";

#define SELECT_USER_CONFIG_SQL ("select id,key,value from " + kTableNameUserConfig)
#define SELECT_USER_CONFIG_SQL_SINGLE ("select id,key,value from " + kTableNameUserConfig + " where key=?")
#define UPDATE_USER_CONFIG_SQL_IP ("update "+ kTableNameUserConfig + " set value=? where key=?")
#define INSERT_USER_CONFIG_SQL "insert into " + kTableNameUserConfig + "(key,value) values(?,?)"

        ConfigDao* ConfigDao::getInstance() {
            static ConfigDao instance;
            return &instance;
        }

        bool ConfigDao::createTable() noexcept {
            auto db = SqliteHelper::getInstance()->getConn();

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

                insertDefaultData();
            }

            return true;
        }

        void ConfigDao::insertDefaultData() {
            auto conn = SqliteHelper::getInstance()->getConn();

            try {
                conn->exec(INSERT_DATA_USER_CONFIG_IP);
                conn->exec(INSERT_DATA_USER_CONFIG_MSG_PORT);
                conn->exec(INSERT_DATA_USER_CONFIG_HTTP_PORT);
                LogInfo("table {} init data success", kTableNameUserConfig);

            } catch (const std::exception& e) {
                LogWarn("init default data error:{}", e.what());
            }
        }

        void ConfigDao::updateKey(const std::string& key, const std::string& newValue) noexcept {
            auto conn = SqliteHelper::getInstance()->getConn();

            std::string outV;

            if (queryKey(key, outV)) { // update
                try {
                    SQLite::Statement st(*conn, UPDATE_USER_CONFIG_SQL_IP);
                    st.bind(1, newValue);
                    st.bind(2, key);

                    if (st.exec() <= 0) {
                        LogWarn("update {}={} error", key, newValue);
                    }

                } catch (const std::exception& e) {
                    LogWarn("error:{}", e.what());
                }

            } else { // insert
                try {
                    SQLite::Statement st(*conn, INSERT_USER_CONFIG_SQL);
                    st.bind(1, key);
                    st.bind(2, newValue);

                    if (st.exec() <= 0) {
                        LogWarn("insert {}={} error", key, newValue);
                    }

                } catch (const std::exception& e) {
                    LogWarn("error:{}", e.what());
                }
            }
        }

        bool ConfigDao::queryKey(const std::string& key, std::string& outValue) noexcept {
            auto conn = SqliteHelper::getInstance()->getConn();

            try {
                SQLite::Statement st(*conn, SELECT_USER_CONFIG_SQL_SINGLE);
                st.bind(1, key);

                if (st.executeStep()) {
                    outValue = st.getColumn(2).getString();
                    return true;
                }

            } catch (const std::exception& e) {
                LogWarn("error:{}", e.what());
            }

            return false;
        }

        bool ConfigDao::query(ConfigServerInfo& out) noexcept {
            auto conn = SqliteHelper::getInstance()->getConn();

            try {
                SQLite::Statement query(*conn, SELECT_USER_CONFIG_SQL);

                if (query.getColumnCount() != 3) {
                    LogWarn("maybe miss config");
                    return false;
                }

                while (query.executeStep()) {
                    const std::string key = query.getColumn(1);
                    const std::string value = query.getColumn(2);

                    if (key == "serverIp") {
                        out.ip = value;

                    } else if (key == "gatePort") {
                        out.gatePort = std::atoi(value.c_str());

                    } else if (key == "httpPort") {
                        out.httpPort = std::atoi(value.c_str());
                    }
                }

            } catch (const std::exception& e) {
                LogWarn("error:{}", e.what());
                return false;
            }

            return true;
        }

        void ConfigDao::updateServerIp(const std::string& ip) noexcept {
            updateKey("serverIp", ip);
        }

        void ConfigDao::updateMsgPort(const uint16_t& msgPort) noexcept {
            updateKey("gatePort", std::to_string(msgPort));
        }

        void ConfigDao::updateHttpPort(const uint16_t& httpPort) noexcept {
            updateKey("httpPort", std::to_string(httpPort));
        }

        ConfigDao::ConfigDao() {
        }

        ConfigDao::~ConfigDao() {
        }
    }
}