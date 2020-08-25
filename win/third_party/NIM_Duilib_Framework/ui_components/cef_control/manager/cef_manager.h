/** @file cef_manager.h
 * @brief ����Cef����ĳ�ʼ�������١���Ϣѭ��
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2016/7/19
 */
#pragma once
#include "include/cef_app.h"

namespace nim_comp
{ 
/** @class CefMessageLoopDispatcher
 * @brief ��multi_threaded_message_loopΪfalseʱ����Ҫ�������Լ�����Ϣѭ������������Cef����Ϣѭ���ӿ�
 *		 ��Ŀ�ײ����ʹ��base���UI��Ϣѭ�����Ӷ��޷�ʹ��cef�Դ���CefRunMessageLoop������Ϣѭ������
 *		 CefMessageLoopDispatcher�̳�base�����Ϣ���Ƚӿڣ����ɵĵ���cef��CefDoMessageLoopWork����������
 *		 ����������base�����cef����Ϣѭ��
 *		 ��multi_threaded_message_loopΪtrueʱ������Ҫʹ�ñ���
 */
class CefMessageLoopDispatcher : public nbase::Dispatcher
{
public:
	virtual bool Dispatch(const MSG &message) override;

private:
	// �жϵ�ǰҪ���ȵ���Ϣ�Ƿ�Ϊ������Ϣ��CefDoMessageLoopWork�����ڿ���ʱ������
	static BOOL IsIdleMessage(const MSG* pMsg);
};


/** @class CefManager
 * @brief Cef�����ʼ��������
 */
class CefManager : public nbase::SupportWeakCallback
{
public:
	SINGLETON_DEFINE(CefManager);
public:
	CefManager();
	~CefManager(){};

	/**
	* ��cef dll�ļ���λ����ӵ������"path"����������,�������԰�dll�ļ��ŵ�bin�����Ŀ¼�����Ҳ���Ҫ�ֶ�Ƶ���л�dll�ļ�
	* @return void	�޷���ֵ
	*/
	void AddCefDllToPath();

	/**
	* ��ʼ��cef���
	* @param[in] app_data_dir Ӧ��·������
	* @param[in] settings Cefȫ������
	* @param[in] is_enable_offset_render �Ƿ���������Ⱦ
	* @return bool true �������У�false Ӧ�ý�������
	*/
	bool Initialize(const std::wstring& app_data_dir, CefSettings &settings, bool is_enable_offset_render = true);

	/**
	* ����cef���
	* @return void	�޷���ֵ
	*/
	void UnInitialize();

	/**
	* �Ƿ���������Ⱦ
	* @return bool true ������false ������
	*/
	bool IsEnableOffsetRender() const;

	/**
	* ��ȡ����Cef����Ϣѭ��������
	* @return nbase::Dispatcher* ��Ϣѭ��������
	*/
	nbase::Dispatcher* GetMessageDispatcher();

	// ��¼��������������
	void AddBrowserCount();
	void SubBrowserCount();
	int	GetBrowserCount();

	// ��Cef������������ٺ���WM_QUIT��Ϣ
	void PostQuitMessage(int nExitCode);

private:
	/**
	* ����cef������Ϣ
	* @param[in] app_data_dir Ӧ��·�����ƣ���nim::Client::Init��˵��
	* @param[out] settings cef������
	* @return void	�޷���ֵ
	*/
	void GetCefSetting(const std::wstring& app_data_dir, CefSettings &settings);

private:
	CefMessageLoopDispatcher message_dispatcher_;
	int browser_count_;
	bool is_enable_offset_render_;
};
}