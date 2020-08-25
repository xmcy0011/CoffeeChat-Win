#ifndef UI_UTILS_ONSCREENKEYBOARDMANAGER_H_
#define UI_UTILS_ONSCREENKEYBOARDMANAGER_H_

#pragma once

namespace ui
{
/** @class OnScreenKeyboardManager
  * @brief D��?a?��?��1����������
  * @copyright (c) 2018, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2018/08/28
  */
class UILIB_API OnScreenKeyboardManager : public virtual nbase::SupportWeakCallback
{
public:
	static OnScreenKeyboardManager* GetInstance();

	/**
	  * D��?a?��?����?��??y?��??��?
	  * @return bool
	  */
	bool IsVisible();

	/**
	  * ??��?D��?a?��?��
	  * @param[in] show ��?��???��?
	  * @return void
	  */
	void ShowOSK(bool show);

private:
	OnScreenKeyboardManager();
	~OnScreenKeyboardManager() {};
	OnScreenKeyboardManager(const OnScreenKeyboardManager&) = delete;
	OnScreenKeyboardManager& operator = (const OnScreenKeyboardManager&) = delete;

	void TimerCallback();
	void StartTabTip();

private:
	bool m_bShow = false;
};
}
#endif //UI_UTILS_ONSCREENKEYBOARDMANAGER_H_