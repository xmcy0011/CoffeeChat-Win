#include "pch.h"
#include "chat_manager.h"
#include "base/util/string_util.h"
#include "base/time/time.h"
#include <time.h>

namespace cim {
    namespace core {
        const int kTimeSpanHalfHour = 60 * 60;
        const int kTimeSpanMin = 10 * 60;

        ChatManager& ChatManager::getInstance() {
            static ChatManager instance;
            return instance;
        }

        std::wstring ChatManager::FormatMsgTime(const int64_t& msgTimeStamp) {
            time_t curTime = time(nullptr);
            tm curDay = *localtime(&curTime);

            time_t msgTime = (time_t)msgTimeStamp;
            tm msgDay = *localtime(&msgTime);

            auto timeSpan = ::abs(msgTimeStamp - (int64_t)curTime);

            if (timeSpan <= kTimeSpanMin) {// 10�����ڣ���ʾ�ո�
                return L"�ո�";

            } else if (timeSpan <= kTimeSpanHalfHour) { // 1Сʱ�ڣ���ʾxx����ǰ
                return nbase::UTF8ToUTF16(std::to_string(timeSpan / 60)) + L"����ǰ";

            } else if (curDay.tm_year == msgDay.tm_year) {
                if (curDay.tm_mday == msgDay.tm_mday) {// �����ڣ���ʾʱ��
                    char buffer[20] = { 0 };
                    strftime(buffer, sizeof(buffer), "%H:%M", &msgDay);

                    return nbase::UTF8ToUTF16(buffer);

                } else if (curDay.tm_mday / 7 == msgDay.tm_mday / 7) { // ͬһ�ܣ���ʾ���ڼ�
                    std::wstring weekStr = L"һ";

                    switch (msgDay.tm_wday) {
                    case 0:
                        weekStr = L"��";
                        break;

                    case 2:
                        weekStr = L"��";
                        break;

                    case 3:
                        weekStr = L"��";
                        break;

                    case 4:
                        weekStr = L"��";
                        break;

                    case 5:
                        weekStr = L"��";
                        break;

                    case 6:
                        weekStr = L"��";
                        break;
                    }

                    return L"����" + weekStr;

                }

                // ͬһ�ꣿ��ʾ��/��
                char buffer[20] = { 0 };
                strftime(buffer, sizeof(buffer), "%m/%d", &msgDay);
                return nbase::UTF8ToUTF16(buffer);

            } else if (::abs(msgDay.tm_year - curDay.tm_year) <= 1) { // һ���ڣ���/��
                char buffer[20] = { 0 };
                strftime(buffer, sizeof(buffer), "%Y/%m", &msgDay);
                return nbase::UTF8ToUTF16(buffer);
            }

            return L"�ܾ���ǰ";
        }

        ChatManager::ChatManager() {

        }

        ChatManager::~ChatManager() {
        }

#if 0
        void testFormatMsgTime() {
            // ����
            int64_t msgTime = time(nullptr) - rand() % 10 * 60;
            std::wstring minMsg = ChatManager::FormatMsgTime(time(nullptr) - (rand() % 10) * 60);
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(minMsg));

            // Сʱ
            msgTime = time(nullptr) - (rand() % 8 + 1) * 60 * 60;
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(ChatManager::FormatMsgTime(msgTime)));

            // ����
            msgTime = time(nullptr) - (rand() % 4 + 1) * 24 * 60 * 60;
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(ChatManager::FormatMsgTime(msgTime)));

            // ��/��
            msgTime = time(nullptr) - ((rand() % 4 + 1) * 24 * 60 * 60 + 7 * 86400);
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(ChatManager::FormatMsgTime(msgTime)));

            // ��/��
            msgTime = time(nullptr) - ((rand() % 100 + 1) * 24 * 60 * 60 + 360 * 86400);
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(ChatManager::FormatMsgTime(msgTime)));

            // �ܾ���ǰ
            msgTime = time(nullptr) - 2 * 360 * 86400;
            LogInfo("{} {}", msgTime, nbase::UTF16ToUTF8(ChatManager::FormatMsgTime(msgTime)));
        }
#endif

    }
}



