#pragma once
#include "window_ex.h"

namespace nim_comp
{
//map<����������map<����id������ָ��>>, ���ͬһ��ֻ��һ�����ڣ�ʹ��������Ϊid
typedef std::map<std::wstring, std::map<std::wstring, WindowEx*>> WindowsMap;
typedef std::list<WindowEx *> WindowList;

/** @class WindowsManager
 * @brief ���д���Ŀ��ƽ�
 * @copyright (c) 2015, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2015/9/16
 */
class WindowsManager
{
public:
	SINGLETON_DEFINE(WindowsManager);
	WindowsManager();
	virtual ~WindowsManager();

	/**
	 * ���ݴ���������idע�ᴰ��
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return bool true �ɹ���false ʧ��
	 */
	bool RegisterWindow(const std::wstring wnd_class_name, const std::wstring wnd_id, WindowEx *wnd);

	/**
	 * ���ݴ���������idע������
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @param[in] wnd ����ָ��
	 * @return void �޷���ֵ
	 */
	void UnRegisterWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id, WindowEx *wnd);

	/**
	 * ���ݴ���������id��ȡ����
	 * @param[in] wnd_class_name ��������
	 * @param[in] wnd_id ����id
	 * @return WindowEx* ����ָ��
	 */
	WindowEx* GetWindow(const std::wstring &wnd_class_name, const std::wstring &wnd_id);

	/**
	 * ��ȡ���д��ڻ�ȡ����
	 * @return WindowList �����б�
	 */
	WindowList GetAllWindows();

	/**
	 * ���ݴ���������ȡ��Ӧ�����д���
	 * @param[in] classname ��������
	 * @return WindowList �����б�
	 */
	WindowList GetWindowsByClassName(LPCTSTR classname);

	/**
	 * �������д���
	 * @return void �޷���ֵ
	 */
	void DestroyAllWindows();

	/**
	 * ���ý�ֹ���ڴ���
	 * @param[in] stop �Ƿ��ֹ���ڴ���
	 * @return void �޷���ֵ
	 */
	void SetStopRegister(bool stop = true) { stop_register_ = stop; }

	/**
	 * �Ƿ��ֹ���ڴ���
	 * @return bool true ��ֹ��false ����ֹ
	 */
	bool IsStopRegister() { return stop_register_; }

	/**
	 * ���ݴ���id����һ��Ψһ���ڵĴ���
	 * @param[in] window_id ����id
	 * @return WindowType* ����ָ��
	 */
	template<typename WindowType, typename... TInstanceParams>
	static WindowType* SingletonShow(const std::wstring& window_id, const TInstanceParams&... params)
	{
		WindowType *window = (WindowType*)(WindowsManager::GetInstance()->GetWindow(WindowType::kClassName, window_id));
		if (!window)
		{
			window = new WindowType(params...);
			window->Create(NULL, WindowType::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
			window->CenterWindow();
			window->ShowWindow();
		}
		else
		{
			window->ActiveWindow();
		}

		return window;
	}

private:
	WindowsMap					windows_map_;	//���д���
	std::string					user_id_;
	bool						stop_register_;	//��ֹ���ڴ���
};
}