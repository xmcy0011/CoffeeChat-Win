#ifndef _BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_
#define _BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_

#include "duilib/UIlib.h"
#include "cim/cim.h"

namespace gui {
    namespace session {
        namespace control {

            /** @class BubbleItem
              * @brief 历史消息列表VListBox元素的封装，自动根据消息类型加载各种消息控件
              * @author xmcy0011@sina.com
              * @date 2021/4/27
              */
            class BubbleItem : public ui::ListContainerElement {
              public:
                BubbleItem();
                ~BubbleItem();
                BubbleItem(const BubbleItem&) = delete;
                void operator = (const BubbleItem&) = delete;

              public:
                /** @fn initItem
                  * @brief 初始化控件
                  * @param msg：要显示的消息
                  * @return
                  */
                void initItem(const cim::MessageModel& msg);

              protected:
                /** @fn onInitItem
                  * @brief 子控件在这里进行初始化
                  * @param bubbleBox：内容放在这里
                  * @param msg：消息
                  * @return
                  */
                virtual void onInitItem(ui::Box* bubbleBox, const cim::MessageModel& msg);

                cim::MessageModel msg_;
                ui::Box* bubble_box_;			// 气泡里面的内容，由子类动态创建
                ui::RichEdit* rd_send_name_;	// 发送人
                ui::Button* btn_head_image_;    // 发送人头像
            };

        }
    }
}

#endif//_BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_