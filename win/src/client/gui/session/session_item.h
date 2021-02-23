#ifndef _SESSION_ITEM_37CE2128_3298_48D2_85D7_8F925B47EE49_
#define _SESSION_ITEM_37CE2128_3298_48D2_85D7_8F925B47EE49_

#include "duilib/UIlib.h"
#include <string>

namespace gui {
    namespace session {
        class SessionItem : public ui::ListContainerElement {
          public:
            SessionItem();
            ~SessionItem();

            void InitControl(std::string sessionId, bool isGroup = false);

            void SetTitle(const std::wstring& title);
            void SetUnread(const uint32_t& count);
            void SetLatestMsg(const std::wstring msg);

          private:
            ui::Label* lab_title_;
            ui::Label* lab_unreade_;
            ui::Label* lab_latest_msg_;
        };
    }
}

#endif//_SESSION_ITEM_37CE2128_3298_48D2_85D7_8F925B47EE49_