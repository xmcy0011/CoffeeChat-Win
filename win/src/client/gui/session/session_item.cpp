#include "stdafx.h"
#include "session_item.h"

namespace gui {
    namespace session {
        SessionItem::SessionItem() {
        }
        SessionItem::~SessionItem() {
        }
        void SessionItem::InitControl(std::string sessionId, bool isGroup) {
            lab_title_ = static_cast<ui::Label*>(FindSubControl(L"item_name"));
            lab_latest_msg_ = static_cast<ui::Label*>(FindSubControl(L"item_msg"));
            assert(lab_title_);
            assert(lab_latest_msg_);
        }
        void SessionItem::SetTitle(const std::wstring& title) {
            lab_title_->SetText(title);
        }
        void SessionItem::SetUnread(const uint32_t& count) {

        }
        void SessionItem::SetLatestMsg(const std::wstring msg) {
            lab_latest_msg_->SetText(msg);
        }
    }
}