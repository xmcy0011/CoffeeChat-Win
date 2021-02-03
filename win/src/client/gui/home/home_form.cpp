#include "stdafx.h"
#include "home_form.h"

#include "stdafx.h"
#include "msgbox/msgbox.h"
#include "cim/cim.h"

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

    /*edit_user_name_ = static_cast<ui::RichEdit*>(FindControl(L"re_username"));
    edit_pwd_ = static_cast<ui::RichEdit*>(FindControl(L"re_userpwd"));

    assert(edit_user_name_);
    assert(edit_pwd_);*/
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
