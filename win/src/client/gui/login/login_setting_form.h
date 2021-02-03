#ifndef _LOGIN_SETTING_FORM_31CB87C8_9343_4D9E_A478_3C8207A134DB_
#define _LOGIN_SETTING_FORM_31CB87C8_9343_4D9E_A478_3C8207A134DB_


#include "duilib/UIlib.h"

void ShowLoginSettingForm();

class LoginSettingForm : public ui::WindowImplBase {
  public:
    LoginSettingForm();
    ~LoginSettingForm();

    /**
     * 一下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
     * GetSkinFolder		接口设置你要绘制的窗口皮肤资源路径
     * GetSkinFile			接口设置你要绘制的窗口的 xml 描述文件
     * GetWindowClassName	接口设置窗口唯一的类名称
     */
    virtual std::wstring GetSkinFolder() override;
    virtual std::wstring GetSkinFile() override;
    virtual std::wstring GetWindowClassName() const override;

    /**
     * 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
     */
    virtual void InitWindow() override;

    /**
     * 收到 WM_CLOSE 消息时该函数会被调用
     */
    virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    static const std::wstring kClassName;

  private:
    bool onLoginClick(ui::EventArgs* msg);

  private:
    ui::RichEdit* edit_ip_;
    ui::RichEdit* edit_gate_port_;
    ui::RichEdit* edit_http_port_;
};


#endif//_LOGIN_SETTING_FORM_31CB87C8_9343_4D9E_A478_3C8207A134DB_