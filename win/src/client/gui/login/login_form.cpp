#include "stdafx.h"
#include "login_form.h"
#include "msgbox/msgbox.h"

const std::wstring LoginForm::kClassName = L"CoffeeChat";

LoginForm::LoginForm() {
}


LoginForm::~LoginForm() {
}

std::wstring LoginForm::GetSkinFolder() {
    return L"login_form";
}

std::wstring LoginForm::GetSkinFile() {
    return L"login_form.xml";
}

std::wstring LoginForm::GetWindowClassName() const {
    return kClassName;
}

void LoginForm::InitWindow() {
    auto callback = std::bind(&LoginForm::onLoginClick, this, std::placeholders::_1);
    ((ui::Button*)FindControl(L"btn_login"))->AttachClick(callback);
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    PostQuitMessage(0L);
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool LoginForm::onLoginClick(ui::EventArgs* msg) {
    nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"click login", false);
    return true;
}