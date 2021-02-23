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
    assert(lb_session_);

    gui::session::SessionItem* item = new gui::session::SessionItem();
    ui::GlobalManager::FillBoxWithCache(item, L"home_form/session_item.xml", nullptr);
    item->InitControl("", false);
    item->SetTitle(L"testchannel");
    item->SetLatestMsg(L"[1Ìõ]xmcy0011£ºhello world");
    lb_session_->Add(item);
}

LRESULT HomeForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    PostQuitMessage(0L);
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
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
