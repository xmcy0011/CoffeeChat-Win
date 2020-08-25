/** @file cef_control_base.h
 * @brief ��װCef���������Ϊduilib�ؼ�����
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2019/3/20
 */
#pragma once
#include "include/cef_base.h"
#include "cef_control_event.h"
#include "cef_control/app/cef_js_bridge.h"
#include "cef_control/handler/browser_handler.h"

namespace nim_comp {

using namespace ui;

class CefControlBase : public Control, public nim_comp::BrowserHandler::HandlerDelegate
{
public:
	CefControlBase(void);
	virtual ~CefControlBase(void);	

public:
	/**
	* @brief ����һ����ַ
	* @param[in] url ��վ��ַ
	* @return ��
	*/
	void LoadURL(const CefString& url);

	/**
	* @brief ��ָ����ַ���һ���ַ�����Դ
	* @param[in] stringW �ַ�����Դ
	* @param[in] url ��ַ
	* @return ��
	*/
	void LoadString(const CefString& stringW, const CefString& url);

	/**
	* @brief ����
	* @return ��
	*/
	void GoBack();

	/**
	* @brief ǰ��
	* @return ��
	*/
	void GoForward();

	/**
	* @brief �ж��Ƿ���Ժ���
	* @return ���� true ��ʾ���ԣ�false ��ʾ������
	*/
	bool CanGoBack();

	/**
	* @brief �ж��Ƿ����ǰ��
	* @return ���� true ��ʾ���ԣ�false ��ʾ������
	*/
	bool CanGoForward();

	/**
	* @brief ˢ��
	* @return ��
	*/
	void Refresh();

	/**
	* @brief ֹͣ����
	* @return ��
	*/
	void StopLoad();

	/**
	* @brief �Ƿ������
	* @return ���� true ��ʾ�����У�����Ϊ false
	*/
	bool IsLoading();

	/**
	* @brief ��ʼһ����������
	* @param[in] url Ҫ���ص��ļ���ַ
	* @return ��
	*/
	void StartDownload(const CefString& url);

	/**
	* @brief ����ҳ�����ű���
	* @param[in] zoom_level ����ֵ
	* @return ��
	*/
	void SetZoomLevel(float zoom_level);

	/**
	* @brief ��ȡ��������������Ĵ�����
	* @return ���ھ��
	*/
	HWND GetCefHandle() const;

	/**
	* @brief ��ȡҳ�� URL
	* @return ���� URL ��ַ
	*/
	CefString GetURL();

	/**
	* @brief ��ȡ UTF8 ��ʽ URL
	* @return ���� URL ��ַ
	*/
	std::string GetUTF8URL();

	/**
	* @brief ��ȡ��ַ # ��ǰ�ĵ�ַ
	* @param[in] url Ҫ��ȡ��������ַ
	* @return ���ؽ�ȡ��ĵ�ַ
	*/
	CefString GetMainURL(const CefString& url);

	/**
	* @brief ע��һ�� C++ �����ṩǰ�˵���
	* @param[in] function_name ��������
	* @param[in] function ����������
	* @param[in] global_function �Ƿ���һ��ȫ�ַ���
	* @return ���� true ��ʾע��ɹ���false �����Ѿ�ע��
	*/
	bool RegisterCppFunc(const std::wstring& function_name, nim_comp::CppFunction function, bool global_function = false);

	/**
	* @brief ��ע��һ�� C++ ����
	* @param[in] function_name ��������
	* @return ��
	*/
	void UnRegisterCppFunc(const std::wstring& function_name);

	/**
	* @brief ����һ��ǰ���Ѿ�ע��õķ���
	* @param[in] js_function_name ǰ���ṩ�ķ�����
	* @param[in] params ���� JSON �ַ�����ʽ�Ĳ���
	* @param[in] callback ǰ��ִ����ɺ�Ļص�����
	* @param[in] frame_name Ҫ�����ĸ����� frame �µķ�����Ĭ��ʹ���� frame
	* @return ���� true ��ʾ�ɹ����ã�false ��ʾ����ʧ�ܣ��������ܲ�����
	*/
	bool CallJSFunction(const std::wstring& js_function_name, const std::wstring& params, nim_comp::CallJsFunctionCallback callback, const std::wstring& frame_name = L"");

	/**
	* @brief ����һ��ǰ���Ѿ�ע��õķ���
	* @param[in] js_function_name ǰ���ṩ�ķ�����
	* @param[in] params ���� JSON �ַ�����ʽ�Ĳ���
	* @param[in] callback ǰ��ִ����ɺ�Ļص�����
	* @param[in] frame_id Ҫ�����ĸ� ID frame �µķ�����Ĭ��ʹ���� frame
	* @return ���� true ��ʾ�ɹ����ã�false ��ʾ����ʧ�ܣ��������ܲ�����
	*/
	bool CallJSFunction(const std::wstring& js_function_name, const std::wstring& params, nim_comp::CallJsFunctionCallback callback, int frame_id);

	/**
	* @brief �޸������
	* @return ��
	*/
	virtual void RepairBrowser();

	/**
	* @brief �򿪿����߹���
	* @param[in] view һ�� CefControl �ؼ�ʵ��(����CefControl������Ҫ����)
	* @return �ɹ����� true��ʧ�ܷ��� false
	*/
	virtual bool AttachDevTools(Control* view) = 0;

	/**
	* @brief �رտ����߹���
	* @return ��
	*/
	virtual void DettachDevTools();

	/**
	* @brief �ж��Ƿ�򿪿����߹���
	* @return ���� true ��ʾ�Ѿ��󶨣�false Ϊδ��
	*/
	virtual bool IsAttachedDevTools() const { return devtool_attached_; }

protected:
	virtual void ReCreateBrowser() = 0;

public:
	/**
	* @brief ��һ���ص��������ڼ����Ҽ��˵�����
	* @param[in] callback һ���ص��������ο� OnBeforeMenuEvent ����
	* @return ��
	*/
	void AttachBeforeContextMenu(const OnBeforeMenuEvent& callback){ cb_before_menu_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ѡ�����ĸ��Ҽ��˵�
	* @param[in] callback һ���ص��������ο� OnMenuCommandEvent ����
	* @return ��
	*/
	void AttachMenuCommand(const OnMenuCommandEvent& callback){ cb_menu_command_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ�� Title �ı�
	* @param[in] callback һ���ص��������ο� OnTitleChangeEvent ����
	* @return ��
	*/
	void AttachTitleChange(const OnTitleChangeEvent& callback){ cb_title_change_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ���� frame URL ��ַ�ı�
	* @param[in] callback һ���ص��������ο� OnUrlChangeEvent ����
	* @return ��
	*/
	void AttachUrlChange(const OnUrlChangeEvent& callback){ cb_url_change_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ�����ҳ�� URL ��ַ�ı�
	* @param[in] callback һ���ص��������ο� OnMainURLChengeEvent ����
	* @return ��
	*/
	void AttachMainURLChange(OnMainURLChengeEvent cb){ cb_main_url_change_ = cb; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ����Դȫ���������
	* @param[in] callback һ���ص��������ο� OnBeforeResourceLoadEvent ����
	* @return ��
	*/
	void AttachBeforeNavigate(const OnBeforeResourceLoadEvent& callback){ cb_before_resource_load_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ���������ڵ�����֪ͨ
	* @param[in] callback һ���ص��������ο� OnLinkClickEvent ����
	* @return ��
	*/
	void AttachLinkClick(const OnLinkClickEvent& callback){ cb_link_click_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ�����״̬�ı�
	* @param[in] callback һ���ص��������ο� OnLoadingStateChangeEvent ����
	* @return ��
	*/
	void AttachLoadingStateChange(const OnLoadingStateChangeEvent& callback){ cb_loadstate_change_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ�濪ʼ����֪ͨ
	* @param[in] callback һ���ص��������ο� OnLoadStartEvent ����
	* @return ��
	*/
	void AttachLoadStart(const OnLoadStartEvent& callback){ cb_load_start_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���ҳ��������֪ͨ
	* @param[in] callback һ���ص��������ο� OnLoadEndEvent ����
	* @return ��
	*/
	void AttachLoadEnd(const OnLoadEndEvent& callback){ cb_load_end_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���������ش���֪ͨ
	* @param[in] callback һ���ص��������ο� OnLoadErrorEvent ����
	* @return ��
	*/
	void AttachLoadError(const OnLoadErrorEvent& callback){ cb_load_error_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ��������߹���״̬�ı�֪ͨ
	* @param[in] callback һ���ص��������ο� OnDevToolAttachedStateChangeEvent ����
	* @return ��
	*/
	void AttachDevToolAttachedStateChange(const OnDevToolAttachedStateChangeEvent& callback){ cb_devtool_visible_change_ = callback; };

	/**
	* @brief ��һ���ص��������ڼ���һ���µ������ʵ���������֪ͨ
	* @param[in] callback һ���ص��������ο� OnAfterCreatedEvent ����
	* @return ��
	*/
	void AttachAfterCreated(const OnAfterCreatedEvent& callback){ cb_after_created_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ�������ʵ���ر�ǰ��֪ͨ
	* @param[in] callback һ���ص��������ο� OnBeforeCloseEvent ����
	* @return ��
	*/
	void AttachBeforeCLose(const OnBeforeCloseEvent& callback) { cb_before_close_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ�������ʵ������֪ͨ
	* @param[in] callback һ���ص��������ο� OnBeforeBrowserEvent ����
	* @return ��
	*/
	void AttachBeforeBrowser(const OnBeforeBrowserEvent& callback) { cb_before_browser_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ��δ֪�� Protocol
	* @param[in] callback һ���ص��������ο� OnProtocolExecutionEvent ����
	* @return ��
	*/
	void AttachProtocolExecution(const OnProtocolExecutionEvent& callback) { cb_protocol_execution_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ����������ʼ֮ǰ��֪ͨ
	* @param[in] callback һ���ص��������ο� OnBeforeDownloadEvent ����
	* @return ��
	*/
	void AttachBeforeDownload(const OnBeforeDownloadEvent& callback) { cb_before_download_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ������ع����������״̬�ı�֪ͨ
	* @param[in] callback һ���ص��������ο� OnDownloadUpdatedEvent ����
	* @return ��
	*/
	void AttachDownloadUpdated(const OnDownloadUpdatedEvent& callback) { cb_download_updated_ = callback; }

	/**
	* @brief ��һ���ص��������ڼ���һ���ӶԻ����д��ļ���֪ͨ
	* @param[in] callback һ���ص��������ο� OnFileDialogEvent ����
	* @return ��
	*/
	void AttachFileDialog(const OnFileDialogEvent& callback) { cb_file_dialog_ = callback; }

private:
	// ����BrowserHandler��HandlerDelegateί�нӿ�
	// ���������Ⱦ���ݱ仯ʱ���ᴥ���˽ӿڣ���ʱ����Ⱦ���ݱ��浽�ڴ�dc
	// ����֪ͨ����ˢ�¿ؼ����ڿؼ���Paint��������ڴ�dc��λͼ����������
	// �ɴ�ʵ��������Ⱦ���ݻ���������
	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		CefRenderHandler::PaintElementType type,
		const CefRenderHandler::RectList& dirtyRects,
		const std::string* buffer,
		int width,
		int height) OVERRIDE;

	virtual void OnPopupShow(CefRefPtr<CefBrowser> browser, bool show) OVERRIDE;

	virtual void OnPopupSize(CefRefPtr<CefBrowser> browser, const CefRect& rect) OVERRIDE;

	virtual void UpdateWindowPos() OVERRIDE;

	virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefContextMenuParams> params, CefRefPtr<CefMenuModel> model) OVERRIDE;

	virtual bool OnContextMenuCommand(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefContextMenuParams> params,
		int command_id,
		CefContextMenuHandler::EventFlags event_flags) OVERRIDE;

	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& url) OVERRIDE;

	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

	virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) OVERRIDE;

	virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame) OVERRIDE;

	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;

	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefLoadHandler::ErrorCode errorCode,
		const CefString& errorText,
		const CefString& failedUrl) OVERRIDE;

	// �ڷ�UI�߳��б�����
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		CefLifeSpanHandler::WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access) OVERRIDE;

	virtual bool OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;

	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	// �ڷ�UI�߳��б�����
	virtual bool OnBeforeBrowse(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_redirect) OVERRIDE;

	virtual void OnProtocolExecution(CefRefPtr<CefBrowser> browser, const CefString& url, bool& allow_os_execution) OVERRIDE;

	// �ڷ�UI�߳��б�����
	virtual CefRequestHandler::ReturnValue OnBeforeResourceLoad(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request,
		CefRefPtr<CefRequestCallback> callback) OVERRIDE;

	virtual void OnRenderProcessTerminated(CefRefPtr<CefBrowser> browser, CefRequestHandler::TerminationStatus status) OVERRIDE;

	// �����ļ����
	virtual void OnBeforeDownload(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		const CefString& suggested_name,
		CefRefPtr<CefBeforeDownloadCallback> callback) OVERRIDE;

	virtual void OnDownloadUpdated(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDownloadItem> download_item,
		CefRefPtr<CefDownloadItemCallback> callback) OVERRIDE;

	// ���ļ����
	virtual bool OnFileDialog(
		CefRefPtr<CefBrowser> browser,
		CefDialogHandler::FileDialogMode mode,
		const CefString& title,
		const CefString& default_file_path,
		const std::vector<CefString>& accept_filters,
		int selected_accept_filter,
		CefRefPtr<CefFileDialogCallback> callback) OVERRIDE;

	virtual bool OnExecuteCppFunc(const CefString& function_name, const CefString& params, int js_callback_id, CefRefPtr<CefBrowser> browser) OVERRIDE;

	virtual bool OnExecuteCppCallbackFunc(int cpp_callback_id, const CefString& json_string) OVERRIDE;

protected:
	CefRefPtr<nim_comp::BrowserHandler> browser_handler_ = nullptr;
	std::shared_ptr<nim_comp::CefJSBridge> js_bridge_;
	CefString url_;
	bool devtool_attached_;

	OnBeforeMenuEvent			cb_before_menu_ = nullptr;
	OnMenuCommandEvent			cb_menu_command_ = nullptr;
	OnTitleChangeEvent			cb_title_change_ = nullptr;
	OnBeforeResourceLoadEvent	cb_before_resource_load_ = nullptr;
	OnUrlChangeEvent			cb_url_change_ = nullptr;
	OnMainURLChengeEvent		cb_main_url_change_ = nullptr;
	OnLinkClickEvent			cb_link_click_ = nullptr;
	OnLoadingStateChangeEvent	cb_loadstate_change_ = nullptr;
	OnLoadStartEvent			cb_load_start_ = nullptr;
	OnLoadEndEvent				cb_load_end_ = nullptr;
	OnLoadErrorEvent			cb_load_error_ = nullptr;
	OnAfterCreatedEvent			cb_after_created_ = nullptr;
	OnBeforeCloseEvent			cb_before_close_ = nullptr;
	OnBeforeBrowserEvent		cb_before_browser_ = nullptr;
	OnProtocolExecutionEvent	cb_protocol_execution_ = nullptr;
	OnBeforeDownloadEvent		cb_before_download_ = nullptr;
	OnDownloadUpdatedEvent		cb_download_updated_ = nullptr;
	OnFileDialogEvent			cb_file_dialog_ = nullptr;
	OnDevToolAttachedStateChangeEvent cb_devtool_visible_change_ = nullptr;
	int							js_callback_thread_id_ = -1; // ������յ� JS ���� CPP �����Ĵ��������̣߳��Ժ󴥷� JS �ص�ʱ�ѻص�ת���Ǹ��߳�
};
}