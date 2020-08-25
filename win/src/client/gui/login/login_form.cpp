#include "stdafx.h"
#include "login_form.h"

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
    //窗体图标（在缩略窗口和任务管理器显示）
    //SetIcon(IDI_BASIC);
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    PostQuitMessage(0L);
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
