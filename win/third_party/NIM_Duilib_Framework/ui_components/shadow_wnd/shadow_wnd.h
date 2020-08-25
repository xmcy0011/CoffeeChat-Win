#ifndef __SHADOW_WND_H__
#define __SHADOW_WND_H__

#pragma once

#include "windows_manager/window_ex.h"

namespace nim_comp {

using namespace ui;

/** @class ShadowWnd
 * @brief һ�����ӵ�����������Χ�Ĵ��ڣ����� WS_EX_LAYERED ������ʵ����Ӱ
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @date 2019-03-22
 */
class ShadowWnd : public WindowImplBase
{
public:
	ShadowWnd();

	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	virtual HWND Create(Window* window);
private:
	Window*	window_ = nullptr;
};

/** @class ShadowWnd
 * @brief ʹ�ø�����Ӱ���ڵĻ��࣬ʵ���˴������ڲ����ӵĹ��ܣ��ṩû�� WS_EX_LAYERED ���ԵĴ��ڼ̳�
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @date 2019-03-22
 */
class ShadowWndBase : public WindowImplBase
{
public:
	ShadowWndBase();

	virtual HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, 
		bool isLayeredWindow = false, const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

private:
	ShadowWnd* shadow_wnd_;
};
} // namespace ui

#endif // __SHADOW_WND_H__
