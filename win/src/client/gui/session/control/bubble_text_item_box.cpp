#include "stdafx.h"
#include "bubble_text_item_box.h"

namespace gui {
    namespace session {
        namespace control {
            BubbleTextItemBox::BubbleTextItemBox(): /*sub_box_(nullptr),*/ rich_edit_(NULL) {
            }

            void BubbleTextItemBox::SetText(const std::wstring& strText) {
                if (rich_edit_ != nullptr) {
                    rich_edit_->SetText(strText);
                }
            }

            BubbleTextItemBox::~BubbleTextItemBox() {
            }

            void BubbleTextItemBox::onInitItem(ui::Box* bubbleBox, const cim::MessageModel& msg) {
                //sub_box_ = new ui::Box();
                ui::GlobalManager::FillBoxWithCache(bubbleBox, msg.IsMyMsg() ? L"session/text_right.xml" : L"session/text_left.xml");

                rich_edit_ = dynamic_cast<ui::RichEdit*>(bubbleBox->FindSubControl(L"text"));
                assert(rich_edit_ != nullptr);

                if (rich_edit_ != nullptr) {
                    rich_edit_->SetText(nbase::UTF8ToUTF16(msg.msg_data));
                }
            }
        }
    }
}


