#include "stdafx.h"
#include "home_form.h"

#include "stdafx.h"
#include "msgbox/msgbox.h"
#include "cim/cim.h"

#include "gui/session/session_item.h"

const std::wstring HomeForm::kClassName = L"HomeForm";

HomeForm::HomeForm() {
}

HomeForm::~HomeForm() {
}

std::wstring HomeForm::GetSkinFolder() {
    return L"home_form";
}

std::wstring HomeForm::GetSkinFile() {
    return L"home_form.xml";
}

std::wstring HomeForm::GetWindowClassName() const {
    return kClassName;
}

void HomeForm::InitWindow() {
    /*auto callback = std::bind(&HomeForm::onLoginClick, this, std::placeholders::_1);
    ((ui::Button*)FindControl(L"btn_login"))->AttachClick(callback);
    ((ui::Button*)FindControl(L"btn_setting"))->AttachClick(callback);*/

    lb_session_ = static_cast<ui::ListBox*>(FindControl(L"list_session"));
    box_default_tips_ = static_cast<ui::Box*>(FindControl(L"box_default_tips"));
    tab_session_box_ = static_cast<ui::TabBox*>(FindControl(L"tab_session_box"));
    assert(lb_session_);
    assert(box_default_tips_);
    assert(tab_session_box_);

    lb_session_->AttachSelect(std::bind(&HomeForm::onSelectSessionItem, this, std::placeholders::_1));

    srand(time(nullptr));

    for (int i = 0; i < 15; i++) {
        gui::session::SessionItem* item = new gui::session::SessionItem();
        ui::GlobalManager::FillBoxWithCache(item, L"home_form/session_item.xml", nullptr);
        item->InitControl("session_" + std::to_string(i + 1), false);
        item->SetTitle(L"testchannel" + nbase::UTF8ToUTF16(std::to_string(i + 1)));
        item->SetLatestMsg(L"[1条]xmcy0011：hello world hello world hello world hello world hello world");
        item->SetUnread(rand() % 100);
        item->SetDisturb(rand() % 2 == 0);
        item->SetLatestTime(time(nullptr) - (rand() % (60 * 60)) * (i + 1) - i * 1000000);
        lb_session_->Add(item);
    }
}

LRESULT HomeForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    PostQuitMessage(0L);
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

// 选中某一个会话，显示历史消息
bool HomeForm::onSelectSessionItem(ui::EventArgs* e) {
    box_default_tips_->SetVisible(false);
    tab_session_box_->SetVisible(true);

    gui::session::SessionItem* item = dynamic_cast<gui::session::SessionItem*>(lb_session_->GetItemAt(e->wParam));

    if (item) {
        std::string sessionId = item->GetSessionId();


        gui::session::SessionBox* box = nullptr;

        // 新的会话，直接创建控件
        if (map_sessions_.find(sessionId) == map_sessions_.end()) {
            box = new gui::session::SessionBox();
            ui::GlobalManager::FillBoxWithCache(box, L"session/session_box.xml", nullptr);
            box->InitControl(sessionId, item->GetTitle());
            map_sessions_[sessionId] = box;
            tab_session_box_->Add(box);

        } else {
            box = map_sessions_[sessionId];
        }

#if 1
        // 添加测试消息
        cim::MessageModel m = {};
        m.msg_type = kCIM_MSG_TYPE_TEXT;
        m.msg_data = "hello world";
        m.from_user_id = cim::core::Client::getInstance()->GetUserId() + 1;
        box->AddMsg(m);

        m.msg_type = kCIM_MSG_TYPE_TEXT;
        m.msg_data = "hello world";
        m.from_user_id = cim::core::Client::getInstance()->GetUserId();
        box->AddMsg(m);
#endif

        tab_session_box_->SelectItem(box);
    }

    return true;
}

//bool HomeForm::onLoginClick(ui::EventArgs* msg) {
//
//    return true;
//}

void ShowHomeForm() {
    HomeForm* window = new HomeForm();

    window->Create(NULL, HomeForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
    window->CenterWindow();
    window->ShowWindow();
}
