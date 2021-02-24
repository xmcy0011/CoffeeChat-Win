#include "stdafx.h"
#include "session_item.h"
#include "cim/cim.h"

namespace gui {
    namespace session {
        SessionItem::SessionItem() {
        }
        SessionItem::~SessionItem() {
        }
        void SessionItem::InitControl(std::string sessionId, bool isGroup) {
            lab_title_ = static_cast<ui::Label*>(FindSubControl(L"item_name"));
            lab_latest_msg_ = static_cast<ui::Label*>(FindSubControl(L"item_msg"));
            lab_unreade_ = static_cast<ui::Label*>(FindSubControl(L"label_unread"));
            lab_time_ = static_cast<ui::Label*>(FindSubControl(L"item_time"));
            bk_dnot_disturb_ = static_cast<ui::Control*>(FindSubControl(L"bk_dnot_disturb"));
            assert(lab_title_);
            assert(lab_latest_msg_);
            assert(lab_time_);
            assert(lab_unreade_);

            session_id_ = sessionId;
        }
        void SessionItem::SetTitle(const std::wstring& title) {
            lab_title_->SetText(title);
        }
        void SessionItem::SetUnread(const uint32_t& count) {
            lab_unreade_->SetText(nbase::UTF8ToUTF16(std::to_string(count)));
        }
        void SessionItem::SetLatestMsg(const std::wstring msg) {
            lab_latest_msg_->SetText(msg);
        }
        void SessionItem::SetDisturb(const bool& yes) {
            bk_dnot_disturb_->SetVisible(yes);
        }
        void SessionItem::SetLatestTime(const int64_t& latestTimeStamp) {
            lab_time_->SetText(cim::core::ChatManager::FormatMsgTime(latestTimeStamp));
        }
        const std::string& SessionItem::GetSessionId() const {
            return session_id_;
        }

        std::wstring SessionItem::GetTitle() const {
            return lab_title_->GetText();
        }

    }
}