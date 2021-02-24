#ifndef _HOME_FORM_F8DFE302_C7E2_4BE3_BD52_C8E98917FC35_
#define _HOME_FORM_F8DFE302_C7E2_4BE3_BD52_C8E98917FC35_

#include "duilib/UIlib.h"
#include "gui/session/session_box.h"
#include <unordered_map>

void ShowHomeForm();

class HomeForm : public ui::WindowImplBase {
  public:
    HomeForm();
    ~HomeForm();

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
    bool onSelectSessionItem(ui::EventArgs* e);

  private:
    ui::ListBox* lb_session_;
    ui::Box* box_default_tips_;
    ui::TabBox* tab_session_box_;

    std::unordered_map<std::string, gui::session::SessionBox*> map_sessions_;
};

#endif//_HOME_FORM_F8DFE302_C7E2_4BE3_BD52_C8E98917FC35_


