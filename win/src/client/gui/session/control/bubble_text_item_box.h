#ifndef _BUBBLE_TEXT_ITEM_BOX_92B27AB0_3C61_4E2D_9760_BC274AB4199E_
#define _BUBBLE_TEXT_ITEM_BOX_92B27AB0_3C61_4E2D_9760_BC274AB4199E_

#include "duilib/UIlib.h"
#include "bubble_item.h"

namespace gui {
    namespace session {
        namespace control {

            /** @class BubbleTextItemBox
              * @brief 文本消息内容控件
              * @author xmcy0011@sina.com
              * @date 2021/4/27
              */
            class BubbleTextItemBox : public BubbleItem {
              public:
                BubbleTextItemBox();
                ~BubbleTextItemBox();
                BubbleTextItemBox(const BubbleTextItemBox&) = delete;
                void operator=(const BubbleTextItemBox&) = delete;

              public:
                void SetText(const std::wstring& strText) override;

              protected:
                void onInitItem(ui::Box* bubbleBox, const cim::MessageModel& msg) override;

              private:
                //ui::Box* sub_box_;
                ui::RichEdit* rich_edit_;
            };
        }
    }
}

#endif//_BUBBLE_TEXT_ITEM_BOX_92B27AB0_3C61_4E2D_9760_BC274AB4199E_