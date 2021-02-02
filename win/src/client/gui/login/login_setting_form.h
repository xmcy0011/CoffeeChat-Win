#ifndef _LOGIN_SETTING_FORM_31CB87C8_9343_4D9E_A478_3C8207A134DB_
#define _LOGIN_SETTING_FORM_31CB87C8_9343_4D9E_A478_3C8207A134DB_


#include "duilib/UIlib.h"

void ShowLoginSettingForm();

class LoginSettingForm : public ui::WindowImplBase {
  public:
    LoginSettingForm();
    ~LoginSettingForm();

    /**
     * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
     * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
     * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
     * GetWindowClassName	�ӿ����ô���Ψһ��������
     */
    virtual std::wstring GetSkinFolder() override;
    virtual std::wstring GetSkinFile() override;
    virtual std::wstring GetWindowClassName() const override;

    /**
     * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
     */
    virtual void InitWindow() override;

    /**
     * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
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