#include "stdafx.h"
#include "login_form.h"
#include "login_setting_form.h"
#include "gui/home/home_form.h"
#include "msgbox/msgbox.h"
#include "main.h"
#include "cim/cim.h"
#include "helper/config.h"

const std::wstring LoginForm::kClassName = L"LoginForm";

LoginForm::LoginForm(): edit_pwd_(nullptr), edit_user_name_(nullptr) {
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
    ((ui::Button*)FindControl(L"btn_setting"))->AttachClick(callback);

    edit_user_name_ = static_cast<ui::RichEdit*>(FindControl(L"re_username"));
    edit_pwd_ = static_cast<ui::RichEdit*>(FindControl(L"re_userpwd"));

    assert(edit_user_name_);
    assert(edit_pwd_);

    Config::getInstace()->load();
    edit_user_name_->SetText(nbase::UTF8ToUTF16(Config::getInstace()->userName));
}

LRESULT LoginForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
    return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool LoginForm::onLoginClick(ui::EventArgs* msg) {
    if (msg->pSender->GetName() == L"btn_setting") {
        ShowLoginSettingForm();
        return true;
    }

    if (edit_user_name_->GetText().empty()) {
        nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"ÇëÊäÈëÕË»§£¡", false);
        return true;
    }

    if (edit_pwd_->GetText().empty()) {
        nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"ÇëÊäÈëÃÜÂë£¡", false);
        return true;
    }

    std::string tempU = nbase::UTF16ToUTF8(edit_user_name_->GetText());
    std::string tempP = nbase::UTF16ToUTF8(edit_pwd_->GetText());

    using namespace cim::core;

    auto client = Client::getInstance();
    client->setConnectionCallback([](const ConnectStatus & status) {
        LogInfo("connection status changed:{}", status);
    });
    client->login(tempU, tempP, [this, tempU](const CIM::Login::CIMAuthRsp & rsp) {
        LogInfo("login result={}", rsp.result_code() == CIM::Def::kCIM_ERR_SUCCSSE);

        if (rsp.result_code() != CIM::Def::kCIM_ERR_SUCCSSE) {
            Client::getInstance()->logout();
            nbase::ThreadManager::PostTask(kThreadUI, [this]() {
                nim_comp::ShowMsgBox(GetHWND(), nim_comp::MsgboxCallback(), L"ÓÃ»§Ãû»òÃÜÂë´íÎó£¡", false);
            });

        } else {
            // save userName
            Config::getInstace()->userName = tempU;
            Config::getInstace()->save();

            nbase::ThreadManager::PostTask(kThreadUI, [this]() {
                ShowHomeForm();
                this->Close();
            });
        }
    }, nullptr);

    return true;
}
