#include "stdafx.h"
#include "bubble_item.h"

gui::session::control::BubbleItem::BubbleItem(): bubble_box_(nullptr), rd_send_name_(nullptr), btn_head_image_(nullptr) {
}

gui::session::control::BubbleItem::~BubbleItem() {
}

void gui::session::control::BubbleItem::initItem(const cim::MessageModel& msg) {
    if (msg.IsSystemMsg()) {
        ui::GlobalManager::FillBoxWithCache(this, L"session/bubble_row.xml", nullptr);

    } else {
        if (msg.IsMyMsg()) {
            ui::GlobalManager::FillBoxWithCache(this, L"session/bubble_right.xml", nullptr);

        } else {
            ui::GlobalManager::FillBoxWithCache(this, L"session/bubble_left.xml", nullptr);
        }
    }

    this->bubble_box_ = dynamic_cast<ui::Box*>(FindSubControl(L"BubbleBox"));
    assert(this->bubble_box_ != nullptr);

    this->btn_head_image_ = dynamic_cast<ui::Button*>(FindSubControl(L"head_image_mask"));
    assert(this->btn_head_image_ != nullptr);

    this->rd_send_name_ = dynamic_cast<ui::RichEdit*>(FindSubControl(L"sender_name"));
    assert(this->rd_send_name_ != nullptr);

    onInitItem(this->bubble_box_, msg);
}

void gui::session::control::BubbleItem::onInitItem(ui::Box* bubbleBox, const cim::MessageModel& msg) {

}
