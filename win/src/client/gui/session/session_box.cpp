#include "stdafx.h"
#include "session_box.h"
#include "base/util/string_util.h"

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
            ui::ListContainerElement* element = new ui::ListContainerElement();

            if (msg.IsSystemMsg()) {
                ui::GlobalManager::FillBoxWithCache(element, L"session/bubble_row.xml", nullptr);

            } else {
                if (msg.IsMyMsg()) {
                    ui::GlobalManager::FillBoxWithCache(element, L"session/bubble_right.xml", nullptr);

                } else {
                    ui::GlobalManager::FillBoxWithCache(element, L"session/bubble_left.xml", nullptr);
                }
            }


            auto box = dynamic_cast<ui::Box*>(element->FindSubControl(L"BubbleBox"));
            assert(box != nullptr);

            ui::Box* subBox = new ui::Box();

            if (box != nullptr) {
                switch (msg.msg_type) {
                case kCIM_MSG_TYPE_TEXT: { // 文本消息
                    ui::GlobalManager::FillBoxWithCache(subBox, msg.IsMyMsg() ? L"session/text_right.xml" : L"session/text_left.xml");
                    auto richEdit = dynamic_cast<ui::RichEdit*>(subBox->FindSubControl(L"text"));
                    assert(richEdit != nullptr);

                    if (richEdit != nullptr) {
                        richEdit->SetText(nbase::UTF8ToUTF16(msg.msg_data));
                    }

                    break;
                }

                case kCIM_MSG_TYPE_TIPS:
                case kCIM_MSG_TYPE_NOTIFACATION: {// 通知消息
                    ui::GlobalManager::FillBoxWithCache(subBox, L"session/system_tips_row.xml");
                    auto richEdit = dynamic_cast<ui::Label*>(subBox->FindSubControl(L"text"));
                    assert(richEdit != nullptr);

                    if (richEdit != nullptr) {
                        richEdit->SetText(nbase::UTF8ToUTF16(msg.msg_data));
                    }

                    break;
                }

                default: { // 未知消息
                    ui::GlobalManager::FillBoxWithCache(subBox, msg.IsMyMsg() ? L"session/text_right.xml" : L"session/text_left.xml");
                    auto richEdit = dynamic_cast<ui::RichEdit*>(subBox->FindSubControl(L"text"));
                    assert(richEdit != nullptr);

                    if (richEdit != nullptr) {
                        richEdit->SetText(L"暂不支持的消息，请在手机上查看");
                    }

                    break;
                }
                }
            }

            box->Add(subBox);
            this->listbox_msg->Add(element);
        }
    }
}