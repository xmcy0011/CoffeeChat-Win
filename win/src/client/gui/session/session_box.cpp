#include "stdafx.h"
#include "session_box.h"
#include "base/util/string_util.h"

#include "control/bubble_tips_item_box.h"
#include "control/bubble_text_item_box.h"

namespace gui {
    namespace session {
        SessionBox::SessionBox() {
        }

        SessionBox::~SessionBox() {
        }

        void SessionBox::InitControl(std::string sessionId, const std::wstring& name, bool isGroup) {
            lab_session_name = static_cast<ui::Label*>(FindSubControl(L"lab_session_name"));
            listbox_msg = static_cast<ui::ListBox*>(FindSubControl(L"list_msg"));
            assert(lab_session_name);
            assert(listbox_msg);

            lab_session_name->SetText(name);
        }

        void SessionBox::AddMsg(const cim::MessageModel& msg) {
            ui::ListContainerElement* element = nullptr;

            switch (msg.msg_type) {
            case kCIM_MSG_TYPE_TEXT: { // 文本消息
                control::BubbleTextItemBox* text = new control::BubbleTextItemBox();
                text->initItem(msg);
                element = text;
                break;
            }

            case kCIM_MSG_TYPE_TIPS:
            case kCIM_MSG_TYPE_NOTIFACATION: {// 通知消息
                control::BubbleTipsItemBox* text = new control::BubbleTipsItemBox();
                text->initItem(msg);
                element = text;
                break;
            }

            default: { // 未知消息
                control::BubbleTextItemBox* text = new control::BubbleTextItemBox();
                text->initItem(msg);
                text->SetText(L"暂不支持的消息，请在手机上查看");
                element = text;
                break;
            }
            }

            this->listbox_msg->Add(element);
        }
    }
}