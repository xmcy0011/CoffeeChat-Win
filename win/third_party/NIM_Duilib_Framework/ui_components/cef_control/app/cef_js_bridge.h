#pragma once
#include "include/cef_app.h"
#include "base/memory/singleton.h"

namespace nim_comp
{

typedef std::function<void(bool has_error, const std::string& result)> ReportResultFunction;

typedef std::function<void(const std::string& result)> CallJsFunctionCallback;
typedef std::function<void(const std::string& params, ReportResultFunction callback)> CppFunction;

typedef std::map<int/* js_callback_id*/, std::pair<CefRefPtr<CefV8Context>/* context*/, CefRefPtr<CefV8Value>/* callback*/>> RenderCallbackMap;
typedef std::map<int/* cpp_callback_id*/, CallJsFunctionCallback/* callback*/> BrowserCallbackMap;

typedef std::map<std::pair<CefString/* function_name*/, int64_t/* frame_id*/>, CefRefPtr<CefV8Value>/* function*/> RenderRegisteredFunction;
typedef std::map<std::pair<CefString/* function_name*/, int64_t/* browser_id*/>, CppFunction/* function*/> BrowserRegisteredFunction;

class CefJSBridge
{
public:
	CefJSBridge();
	~CefJSBridge();

// in render process
public:
	/**
	 * ִ���Ѿ�ע��õ� C++ ����
	 * param[in] function_name	Ҫ���õĺ�������
	 * param[in] params			���øú������ݵ� json ��ʽ����
	 * param[in] callback		ִ����ɺ�Ľ���ص�����
	 * return ���� true ��ʾ����ִ������ɹ�����������һ��ִ�гɹ������忴�ص��������� false ������ע��Ļص����� ID �Ѿ�����
	 */
	bool CallCppFunction(const CefString& function_name, const CefString& params, CefRefPtr<CefV8Value> callback);

	/**
	 * ͨ���ж������Ļ����Ƴ�ָ���ص�������ҳ��ˢ�»ᴥ���÷�����
	 * param[in] frame		��ǰ���п��
	 */
	void RemoveCallbackFuncWithFrame(CefRefPtr<CefFrame> frame);

	/**
	 * ���� ID ִ��ָ���ص�����
	 * param[in] js_callback_id	�ص������� ID
	 * param[in] has_error		�Ƿ��д��󣬶�Ӧ�ص�������һ������
	 * param[in] json_string	���û�д����򷵻�ָ���� json string ��ʽ�����ݣ���Ӧ�ص������ڶ�������
	 * return ���� true ��ʾ�ɹ�ִ���˻ص����������� false �п��ܻص����������ڻ��߻ص����������ִ�������Ļ����Ѿ�������
	 */
	bool ExecuteJSCallbackFunc(int js_callback_id, bool has_error, const CefString& json_result);

	/**
	 * ע��һ���־õ� JS �����ṩ C++ ����
	 * param[in] function_name	�������ƣ��ַ�����ʽ�ṩ C++ ֱ�ӵ��ã����Ʋ����ظ�
	 * param[in] context		������ִ�������Ļ���
	 * param[in] function		������
	 * param[in] replace		���Ѿ����ڸ����Ƶĺ����Ƿ��滻��Ĭ�Ϸ�
	 * return replace Ϊ true ������£����� true ���滻�ɹ������� false Ϊ����Ԥ����Ϊ��replace Ϊ false ������·��� true ��ʾע��ɹ������� false ��ͬ�������Ѿ�ע����ˡ�
	 */
	bool RegisterJSFunc(const CefString& function_name, CefRefPtr<CefV8Value> function, bool replace = false);

	/**
	 * ��ע��һ���־õ� JS ����
	 * param[in] function_name	��������
	 * param[in] frame			Ҫȡ��ע���ĸ�����µ���غ���
	 */
	void UnRegisterJSFunc(const CefString& function_name, CefRefPtr<CefFrame> frame);

	/**
	* ����ִ�������ķ�ע��һ�������־õ� JS ����
	* param[in] frame			��ǰ�����������
	*/
	void UnRegisterJSFuncWithFrame(CefRefPtr<CefFrame> frame);

	/**
	 * ��������ִ��ĳ������� JS ����
	 * param[in] function_name	��������
	 * param[in] json_params	Ҫ���ݵ� json ��ʽ�Ĳ���
	 * param[in] frame			ִ���ĸ�����µ� JS ����
	 * param[in] cpp_callback_id	ִ����ɺ�Ҫ�ص��� C++ �ص����� ID
	 * return ���� true ��ʾ�ɹ�ִ��ĳ�� JS ���������� false �п���Ҫִ�еĺ��������ڻ��߸ú����������������Ѿ���Ч
	 */
	bool ExecuteJSFunc(const CefString& function_name, const CefString& json_params, CefRefPtr<CefFrame> frame, int cpp_callback_id);

// in browser process
public:
	/**
	 * ִ���Ѿ�ע��õ� JS ����
	 * param[in] js_function_name Ҫ���õ� JS ��������
	 * param[in] params			���� JS �������ݵ� json ��ʽ����
	 * param[in] frame			�����ĸ�����µ� JS ����
	 * param[in] callback		���� JS �����󷵻����ݵĻص�����
	 * return ���� ture ��ʶ����ִ�� JS ��������ɹ������� false ����ͬ�� callback id �Ѿ�����
	 */
	bool CallJSFunction(const CefString& js_function_name, const CefString& params, CefRefPtr<CefFrame> frame, CallJsFunctionCallback callback);

	/**
	 * ���� ID ִ��ָ���ص�����
	 * param[in] cpp_callback_id callback ������ id
	 * param[in] json_string	���ص� json ��ʽ����
	 * return ���� true ִ�гɹ���false Ϊִ��ʧ�ܣ����ܻص�������
	 */
	bool ExecuteCppCallbackFunc(int cpp_callback_id, const CefString& json_string);

	/**
	 * ע��һ���־õ� C++ �����ṩ JS �˵���
	 * param[in] function_name	Ҫ�ṩ JS ���õĺ�������
	 * param[in] function		������
	 * param[in] replace		�Ƿ��滻��ͬ���Ƶĺ����壬Ĭ�ϲ��滻
	 * return replace Ϊ true ������£����� true ��ʾע������滻�ɹ���false �ǲ���Ԥ֪��Ϊ��replace Ϊ false ������·��� true ��ʾע��ɹ������� false ��ʾ�������Ѿ�ע��
	 */
	bool RegisterCppFunc(const CefString& function_name, CppFunction function, CefRefPtr<CefBrowser> browser, bool  replace = false);

	/**
	 * ��ע��һ���־õ� C++ ����
	 * param[in] function_name	Ҫ��ע��ĺ�������
	 */
	void UnRegisterCppFunc(const CefString& function_name, CefRefPtr<CefBrowser> browser);

	/**
	 * ִ��һ���Ѿ�ע��õ� C++ ���������ܵ� JS ��ִ������ʱ�����ã�
	 * param[in] function_name	Ҫִ�еĺ�������
	 * param[in] params			Я���Ĳ���
	 * param[in] js_callback_id	�ص� JS ������Ļص����� ID
	 * param[in] browser		browser ʵ�����
	 * return ���� true ��ʾִ�гɹ������� false ��ʾִ��ʧ�ܣ����������ܲ�����
	 */
	bool ExecuteCppFunc(const CefString& function_name, const CefString& params, int js_callback_id, CefRefPtr<CefBrowser> browser);

private:
	uint32						js_callback_id_ = 0;			// JS �˻ص���������������
	uint32						cpp_callback_id_ = 0;			// C++ �˻ص���������������

	RenderCallbackMap			render_callback_;				// JS �˻ص������Ķ�Ӧ�б�
	BrowserCallbackMap			browser_callback_;				// C++ �˻ص������Ķ�Ӧ�б�

	RenderRegisteredFunction	render_registered_function_;	// ���� JS ���Ѿ�ע��õĳ־ú����б�
	BrowserRegisteredFunction	browser_registered_function_;	// ���� C++ ���Ѿ�ע��õĳ־ú����б�
};

}