/** @file browser_box.h
* @brief ��ǩҳ����
* @copyright (c) 2016, NetEase Inc. All rights reserved
* @author Redrain
* @date 2019/3/20
*/
#pragma once

class TaskbarTabItem;
class MultiBrowserForm;
class BrowserBox : public ui::VBox
{
public:
	friend class MultiBrowserForm;

	/**
	* ���캯��
	* @param[in] id	��������ӵ�Ψһ��ʶ���������ֲ�ͬ�ı�ǩҳ
	*/
	BrowserBox(std::string id);
	~BrowserBox() { };

	/**
	* ��ȡid
	* @return string ��ʶid
	*/
	std::string GetId() const { return browser_id_; }

	/**
	* ��ȡ��������������������������ָ��
	* @return MultiBrowserForm* ���������
	*/
	MultiBrowserForm* GetBrowserForm() const;

	/**
	* ��ȡCef�ؼ�ָ��
	* @return ui::CefControlBase* Cef�ؼ�
	*/
	nim_comp::CefControlBase* GetCefControl();

	/**
	* ��ȡ��ҳ����
	* @return std::wstring& ��ҳ����
	*/
	std::wstring& GetTitle();

	/**
	* ��ʼ�����������
	* @param[in] url ��ʼ��URL
	* @return void	�޷���ֵ
	*/
	virtual void InitBrowserBox(const std::wstring &url);

	/**
	* ����ʼ�����������
	* @return void	�޷���ֵ
	*/
	virtual void UninitBrowserBox();

	/**
	* ���ݿؼ����������Զ���ؼ�
	* @param[in] pstrClass �ؼ�����
	* @return Control* �����Ŀؼ���ָ��
	*/
	ui::Control* CreateControl(const std::wstring& pstrClass);

	//////////////////////////////////////////////////////////////////////////
	//���ںϲ�������صĲ���
public:
	/**
	* ��ȡ�뱾��������Ӱ󶨵�Tabָ��
	* @return TaskbarItem*	Tabָ��
	*/
	TaskbarTabItem* GetTaskbarItem();

	/**
	* ���Ǹ����麯��������ָ�����ؼ��������弰���ؼ���Ϣ
	* @param[in] pManager ��������ָ��
	* @param[in] pParent ���ؼ�ָ��
	* @param[in] bInit �Ƿ�Ҫ��ʼ�����ؼ�
	* @return void	�޷���ֵ
	*/
	virtual void SetWindow(ui::Window* pManager, ui::Box* pParent, bool bInit) override;

	/**
	* ���ǻ����麯����Ϊ������������ʾ����ͼ��Ԥ��ͼ����д�������ӿؼ�SetInternVisible���Ե��߼�
	* @param[in] bVisible �Ƿ���ʾ
	* @return void	�޷���ֵ
	*/
	virtual void SetInternVisible(bool bVisible = true) override;

	/**
	* ���ǻ����麯����Ϊ�����ػ���������ʾ������ͼ
	* @return void	�޷���ֵ
	*/
	virtual void Invalidate() override;

	/**
	* ���ǻ����麯����Ϊ�����ػ���������ʾ������ͼ
	* @param[in] rc Ҫ���õĿؼ���λ��
	* @return void	�޷���ֵ
	*/
	virtual void SetPos(ui::UiRect rc) override;

private:
	void OnBeforeMenu(CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model);
	bool OnMenuCommand(CefRefPtr<CefContextMenuParams> params, int command_id, CefContextMenuHandler::EventFlags event_flags);
	void OnTitleChange(const std::wstring& title);
	void OnUrlChange(const std::wstring& url);
	bool OnLinkClick(const std::wstring& url);
	CefRequestHandler::ReturnValue OnBeforeNavigate(CefRefPtr<CefRequest> request, bool is_redirect);
	void OnLoadingStateChange(bool isLoading, bool canGoBack, bool canGoForward);
	void OnLoadStart();
	void OnLoadEnd(int httpStatusCode);
	void OnLoadError(CefLoadHandler::ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl);

private:
	nim_comp::CefControlBase	*cef_control_;

	// ����������ͼ����
	TaskbarTabItem		*taskbar_item_;
	MultiBrowserForm	*browser_form_;
	std::string			browser_id_;
	std::wstring		url_;
	std::wstring		title_;
};