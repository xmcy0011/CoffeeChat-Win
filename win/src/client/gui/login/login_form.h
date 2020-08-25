/** @file login_form.h
  * @brief login_form
  * @author fei.xu
  * @date 2020/8/24
  */

#ifndef _LOGIN_FORM_E3A91E7D_0AAA_4DB0_9E03_872787E96D1A_
#define _LOGIN_FORM_E3A91E7D_0AAA_4DB0_9E03_872787E96D1A_

#include "duilib/UIlib.h"

class LoginForm : public ui::WindowImplBase {
  public:
    LoginForm();
    ~LoginForm();

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
};


#endif//_LOGIN_FORM_E3A91E7D_0AAA_4DB0_9E03_872787E96D1A_