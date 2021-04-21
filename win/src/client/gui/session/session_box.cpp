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
            if (msg.msg_type != kCIM_MSG_TYPE_TEXT) {
                LogInfo("unknown msg type");
                return;
            }

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

            if (box != nullptr) {
                switch (msg.msg_type) {
                case kCIM_MSG_TYPE_TEXT: {
                    ui::Box* subBox = new ui::Box();
                    ui::GlobalManager::FillBoxWithCache(subBox, msg.IsMyMsg() ? L"session/text_right.xml" : L"session/text_left.xml");
                    auto richEdit = dynamic_cast<ui::RichEdit*>(subBox->FindSubControl(L"text"));
                    assert(richEdit != nullptr);

                    if (richEdit != nullptr) {
                        richEdit->SetText(nbase::UTF8ToUTF16(msg.msg_data));
                    }

                    box->Add(subBox);
                }
                break;

                default:
                    break;
                }
            }

            this->listbox_msg->Add(element);
        }
    }
}