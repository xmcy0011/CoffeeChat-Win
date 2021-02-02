#include "stdafx.h"
#include "msgbox/msgbox.h"
#include "login_setting_form.h"
#include "cim/cim.h"

const std::wstring LoginSettingForm::kClassName = L"LoginSettingForm";

LoginSettingForm::LoginSettingForm() : edit_ip_(nullptr), edit_gate_port_(nullptr), edit_http_port_(nullptr) {
}

LoginSettingForm::~LoginSettingForm() {
}

std::wstring LoginSettingForm::GetSkinFolder() {
    return L"login_form";
}

std::wstring LoginSettingForm::GetSkinFile() {
    return L"login_setting_form.xml";
}

std::wstring LoginSettingForm::GetWindowClassName() const {
    return kClassName;
}

void LoginSettingForm::InitWindow() {
    auto callback = std::bind(&LoginSettingForm::onLoginClick, this, std::placeholders::_1);
    ((ui::Button*)FindControl(L"btn_test"))->AttachClick(callback);
    ((ui::Button*)FindControl(L"btn_save"))->AttachClick(callback);

    edit_ip_ = static_cast<ui::RichEdit*>(FindControl(L"re_ip"));
    edit_gate_port_ = static_cast<ui::RichEdit*>(FindControl(L"re_gate_port"));
    edit_http_port_ = static_cast<ui::RichEdit*>(FindControl(L"re_http_port"));

    assert(edit_ip_);
    assert(edit_gate_port_);
    assert(edit_http_port_);

    cim::ConfigServerInfo config;

    if (cim::db::ConfigDao::getInstance()->query(config)) {
        edit_ip_->SetText(nbase::UTF8ToUTF16(config.ip));
        edit_gate_port_->SetText(nbase::UTF8ToUTF16(std::to_string(config.gatePort)));
        edit_http_port_->SetText(nbase::UTF8ToUTF16(std::to_string(config.httpPort)));
    }
}

LRESULT LoginSettingForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool LoginSettingForm::onLoginClick(ui::EventArgs* msg) {
    if (msg->pSender->GetName() == L"btn_save") {
        cim::db::ConfigDao::getInstance()->updateServerIp(nbase::UTF16ToUTF8(edit_ip_->GetText()));
        cim::db::ConfigDao::getInstance()->updateMsgPort(std::atoi(nbase::UTF16ToUTF8(edit_gate_port_->GetText()).c_str()));
        cim::db::ConfigDao::getInstance()->updateHttpPort(std::atoi(nbase::UTF16ToUTF8(edit_http_port_->GetText()).c_str()));

        nim_comp::ShowMsgBox(GetHWND(), [this](nim_comp::MsgBoxRet) {
            this->Close();
        }, L"save success!", false);
    }

    return true;
}

void ShowLoginSettingForm() {
    LoginSettingForm* form = new LoginSettingForm();
    form->Create(NULL, LoginSettingForm::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
    form->CenterWindow();
    form->ShowWindow(true);
}
