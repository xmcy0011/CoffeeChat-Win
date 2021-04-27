#include "stdafx.h"
#include "bubble_tips_item_box.h"

namespace gui {
    namespace session {
        namespace control {

            BubbleTipsItemBox::BubbleTipsItemBox(): text_tips_(nullptr) {

            }

            BubbleTipsItemBox::~BubbleTipsItemBox() {
            }

            void BubbleTipsItemBox::initItem(const cim::MessageModel& msg) {
                ui::GlobalManager::FillBoxWithCache(this, L"session/system_tips_row.xml");
                this->text_tips_ = dynamic_cast<ui::Label*>(FindSubControl(L"text"));
                assert(this->text_tips_ != nullptr);

                if (this->text_tips_ != nullptr) {
                    this->text_tips_->SetText(nbase::UTF8ToUTF16(msg.msg_data));
                }
            }
        }
    }
}

