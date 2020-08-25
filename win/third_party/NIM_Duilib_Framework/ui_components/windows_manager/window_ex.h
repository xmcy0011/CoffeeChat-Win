#pragma once
#include "duilib/UIlib.h"

namespace nim_comp
{
/** @class WindowEx
 * @brief ���д���Ļ���
 * @copyright (c) 2015, NetEase Inc. All rights reserved
 * @date 2015/9/16
 */
class WindowEx : public ui::WindowImplBase
{
public:
	WindowEx();
	virtual ~WindowEx();

	/**
	 * ��������
	 * @param[in] hwndParent �����ھ��
	 * @param[in] pstrName ��������
	 * @param[in] dwStyle ������ʽ
	 * @param[in] dwExStyle ������չ��ʽ
	 * @param[in] isLayeredWindow �Ƿ񴴽��ֲ㴰��
	 * @param[in] rc ����λ��
	 * @return HWND ���ھ��
	 */
	virtual HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle,
		bool isLayeredWindow = true, const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

	/**
	 * �����ڱ����ٵ���Ϣ
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ����
	 * @param[in] lParam ����
	 * @param[out] bHandled ��Ϣ�Ƿ񱻴���
	 * @return LRESULT ������
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	 * ����ESC����������Ϣ
	 * @param[out] bHandled ��Ϣ�Ƿ񱻴���
	 * @return void �޷���ֵ
	 */
	virtual void OnEsc(BOOL &bHandled);

	/**
	 * ��ȡ���������Ľӿ�
	 * @return wstring ��������
	 */
	virtual std::wstring GetWindowClassName(void) const = 0;

	/**
	 * ��ȡ����id�Ľӿ�
	 * @return wstring ����id
	 */
	virtual std::wstring GetWindowId(void) const = 0;

	/**
	 * ��������Ϣ
	 * @param[in] uMsg ��Ϣ
	 * @param[in] wParam ����
	 * @param[in] lParam ����
	 * @return LRESULT ������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	/**
	 * ��WindowManager��ע���Լ�
	 * @return bool true ע��ɹ���false ע��ʧ��
	 */
	bool RegisterWnd();

	/**
	 * ��WindowManager�з�ע���Լ�
	 * @return void �޷���ֵ
	 */
	void UnRegisterWnd();
};

/**
* ��ȡ�������ڿ�����ʾ�����½�λ�õ�����
* @return POINT ��������
*/
POINT GetPopupWindowPos(WindowEx* window);

}