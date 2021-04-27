#ifndef _BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_
#define _BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_

#include "duilib/UIlib.h"
#include "cim/cim.h"

namespace gui {
    namespace session {
        namespace control {

            /** @class BubbleItem
              * @brief ��ʷ��Ϣ�б�VListBoxԪ�صķ�װ���Զ�������Ϣ���ͼ��ظ�����Ϣ�ؼ�
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
                  * @brief ��ʼ���ؼ�
                  * @param msg��Ҫ��ʾ����Ϣ
                  * @return
                  */
                void initItem(const cim::MessageModel& msg);

              protected:
                /** @fn onInitItem
                  * @brief �ӿؼ���������г�ʼ��
                  * @param bubbleBox�����ݷ�������
                  * @param msg����Ϣ
                  * @return
                  */
                virtual void onInitItem(ui::Box* bubbleBox, const cim::MessageModel& msg);

                cim::MessageModel msg_;
                ui::Box* bubble_box_;			// ������������ݣ������ද̬����
                ui::RichEdit* rd_send_name_;	// ������
                ui::Button* btn_head_image_;    // ������ͷ��
            };

        }
    }
}

#endif//_BUBBLE_ITEM_DE384CE3_6F18_4588_BA74_C5961121AA0E_