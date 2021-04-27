#ifndef _BUBBLE_TIPS_ITEM_BOX_4D26E8BF_73BF_48E1_9503_2A84AEF3C512_
#define _BUBBLE_TIPS_ITEM_BOX_4D26E8BF_73BF_48E1_9503_2A84AEF3C512_

#include "duilib/UIlib.h"
#include "cim/cim.h"
#include "bubble_item.h"

namespace gui {
    namespace session {
        namespace control {
            /** @class BubbleTipsItemBox
              * @brief 通知提醒消息
              * @author xmcy0011@sina.com
              * @date 2021/4/27
              */
            class BubbleTipsItemBox : public ui::ListContainerElement {
              public:
                BubbleTipsItemBox();
                ~BubbleTipsItemBox();
                BubbleTipsItemBox(const BubbleTipsItemBox&) = delete;
                void operator=(const BubbleTipsItemBox&) = delete;

              public:
                void initItem(const cim::MessageModel& msg);

              private:
                ui::Box* bubble_box_;
                ui::Label* text_tips_;
            };
        }
    }
}

#endif//_BUBBLE_TIPS_ITEM_BOX_4D26E8BF_73BF_48E1_9503_2A84AEF3C512_