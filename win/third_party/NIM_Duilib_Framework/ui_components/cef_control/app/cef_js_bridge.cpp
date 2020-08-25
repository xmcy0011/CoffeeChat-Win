#include "stdafx.h"
#include "cef_js_bridge.h"
#include "ipc_string_define.h"

namespace nim_comp {

CefJSBridge::CefJSBridge()
{

}

CefJSBridge::~CefJSBridge()
{

}

bool CefJSBridge::CallCppFunction(const CefString& function_name, const CefString& params, CefRefPtr<CefV8Value> callback)
{
	auto it = render_callback_.find(js_callback_id_);
	if (it == render_callback_.cend())
	{
		CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(kCallCppFunctionMessage);

		message->GetArgumentList()->SetString(0, function_name);
		message->GetArgumentList()->SetString(1, params);
		message->GetArgumentList()->SetInt(2, js_callback_id_);

		render_callback_.emplace(js_callback_id_++, std::make_pair(context, callback));

		// ������Ϣ�� browser ����
		CefRefPtr<CefBrowser> browser = context->GetBrowser();
		browser->SendProcessMessage(PID_BROWSER, message);

		return true;
	}

	return false;
}

void CefJSBridge::RemoveCallbackFuncWithFrame(CefRefPtr<CefFrame> frame)
{
	if (!render_callback_.empty())
	{
		for (auto it = render_callback_.begin(); it != render_callback_.end();)
		{
			if (it->second.first->IsSame(frame->GetV8Context()))
			{
				it = render_callback_.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

bool CefJSBridge::ExecuteJSCallbackFunc(int js_callback_id, bool has_error, const CefString& json_result)
{
	auto it = render_callback_.find(js_callback_id);
	if (it != render_callback_.cend())
	{
		auto context = it->second.first;
		auto callback = it->second.second;

		if (context.get() && callback.get())
		{
			context->Enter();

			CefV8ValueList arguments;

			// ��һ��������Ǻ���ִ�н���Ƿ�ɹ�
			arguments.push_back(CefV8Value::CreateBool(has_error));

			// �ڶ�������Я������ִ�к󷵻ص�����
			CefV8ValueList json_parse_args;
			json_parse_args.push_back(CefV8Value::CreateString(json_result));
			CefRefPtr<CefV8Value> json_parse = context->GetGlobal()->GetValue("JSON")->GetValue("parse");
			CefRefPtr<CefV8Value> json_object = json_parse->ExecuteFunction(NULL, json_parse_args);
			arguments.push_back(json_object);

			// ִ�� JS ����
			CefRefPtr<CefV8Value> retval = callback->ExecuteFunction(NULL, arguments);
			if (retval.get())
			{
				if (retval->IsBool())
				{
					retval->GetBoolValue();
				}
			}

			context->Exit();

			// ���б����Ƴ� callback ����
			render_callback_.erase(js_callback_id);

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool CefJSBridge::RegisterJSFunc(const CefString& function_name, CefRefPtr<CefV8Value> function, bool replace/* = false*/)
{
	CefRefPtr<CefV8Context> context = CefV8Context::GetCurrentContext();
	CefRefPtr<CefFrame> frame = context->GetFrame();

	if (replace)
	{
		render_registered_function_.emplace(std::make_pair(function_name, frame->GetIdentifier()), function);
		return true;
	}
	else
	{
		auto it = render_registered_function_.find(std::make_pair(function_name, frame->GetIdentifier()));
		if (it == render_registered_function_.cend())
		{
			render_registered_function_.emplace(std::make_pair(function_name, frame->GetIdentifier()), function);
			return true;
		}

		return false;
	}
	
	return false;
}

void CefJSBridge::UnRegisterJSFunc(const CefString& function_name, CefRefPtr<CefFrame> frame)
{
	render_registered_function_.erase(std::make_pair(function_name, frame->GetIdentifier()));
}

void CefJSBridge::UnRegisterJSFuncWithFrame(CefRefPtr<CefFrame> frame)
{
	// ���ڱ�����ÿһ�� render �� browser ���̶�����һ��ʵ���������ǵ���ģʽ
	// ���������ȡ�� browser ����ȫ��Ψһ�ģ����Ը������ browser ��ȡ���� frame �� context
	auto browser = frame->GetBrowser();

	if (!render_registered_function_.empty())
	{
		for (auto it = render_registered_function_.begin(); it != render_registered_function_.end();)
		{
			auto child_frame = browser->GetFrame(it->first.second);
			if (child_frame.get() && child_frame->GetV8Context()->IsSame(frame->GetV8Context()))
			{
				it = render_registered_function_.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}

bool CefJSBridge::ExecuteJSFunc(const CefString& function_name, const CefString& json_params, CefRefPtr<CefFrame> frame, int cpp_callback_id)
{
	auto it = render_registered_function_.find(std::make_pair(function_name, frame->GetIdentifier()));
	if (it != render_registered_function_.cend())
	{

		auto context = frame->GetV8Context();
		auto function = it->second;

		if (context.get() && function.get())
		{
			context->Enter();

			CefV8ValueList arguments;

			// �� C++ ���ݹ����� JSON ת���� Object
			CefV8ValueList json_parse_args;
			json_parse_args.push_back(CefV8Value::CreateString(json_params));
			CefRefPtr<CefV8Value> json_object = context->GetGlobal()->GetValue("JSON");
			CefRefPtr<CefV8Value> json_parse = json_object->GetValue("parse");
			CefRefPtr<CefV8Value> json_stringify = json_object->GetValue("stringify");
			CefRefPtr<CefV8Value> json_object_args = json_parse->ExecuteFunction(NULL, json_parse_args);
			arguments.push_back(json_object_args);

			// ִ�лص�����
			CefRefPtr<CefV8Value> retval = function->ExecuteFunction(NULL, arguments);
			if (retval.get() && retval->IsObject())
			{
				// �ظ����� JS ��ķ���ֵ
				CefV8ValueList json_stringify_args;
				json_stringify_args.push_back(retval);
				CefRefPtr<CefV8Value> json_string = json_stringify->ExecuteFunction(NULL, json_stringify_args);
				CefString str = json_string->GetStringValue();

				CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(kExecuteCppCallbackMessage);
				CefRefPtr<CefListValue> args = message->GetArgumentList();
				args->SetString(0, json_string->GetStringValue());
				args->SetInt(1, cpp_callback_id);
				context->GetBrowser()->SendProcessMessage(PID_BROWSER, message);
			}

			context->Exit();

			return true;
		}

		return false;
	}

	return false;
}

bool CefJSBridge::CallJSFunction(const CefString& js_function_name, const CefString& params, CefRefPtr<CefFrame> frame, CallJsFunctionCallback callback)
{
	if (!frame.get())
	{
		return false;
	}

	auto it = browser_callback_.find(cpp_callback_id_);
	if (it == browser_callback_.cend())
	{
		browser_callback_.emplace(cpp_callback_id_, callback);
		// ������Ϣ�� render Ҫ��ִ��һ�� js function
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(kCallJsFunctionMessage);
		CefRefPtr<CefListValue> args = message->GetArgumentList();
		args->SetString(0, js_function_name);
		args->SetString(1, params);
		args->SetInt(2, cpp_callback_id_++);
		args->SetInt(3, (int)(frame->GetIdentifier()));

		frame->GetBrowser()->SendProcessMessage(PID_RENDERER, message);

		return true;
	}

	return false;
}

bool CefJSBridge::ExecuteCppCallbackFunc(int cpp_callback_id, const CefString& json_string)
{
	auto it = browser_callback_.find(cpp_callback_id);
	if (it != browser_callback_.cend())
	{
		auto callback = it->second;
		if (callback)
		{
			nbase::ThreadManager::PostTask(kThreadUI, [=]() { callback(json_string); });
		}
		
		// ִ����ɺ�ӻ������Ƴ�
		browser_callback_.erase(cpp_callback_id);
	}

	return false;
}

bool CefJSBridge::RegisterCppFunc(const CefString& function_name, CppFunction function, CefRefPtr<CefBrowser> browser, bool replace /*= false*/)
{
	if (replace)
	{
		browser_registered_function_.emplace(std::make_pair(function_name, browser ? browser->GetIdentifier() : -1), function);// = ;
		return true;
	}
	else
	{
		auto it = browser_registered_function_.find(std::make_pair(function_name, browser ? browser->GetIdentifier() : -1));
		if (it == browser_registered_function_.cend())
		{
			browser_registered_function_.emplace(std::make_pair(function_name, browser ? browser->GetIdentifier() : -1), function);
			return true;
		}

		return false;
	}

	return false;
}

void CefJSBridge::UnRegisterCppFunc(const CefString& function_name, CefRefPtr<CefBrowser> browser)
{
	browser_registered_function_.erase(std::make_pair(function_name, browser ? browser->GetIdentifier() : -1));
}

bool CefJSBridge::ExecuteCppFunc(const CefString& function_name, const CefString& params, int js_callback_id, CefRefPtr<CefBrowser> browser)
{
	CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(kExecuteJsCallbackMessage);
	CefRefPtr<CefListValue> args = message->GetArgumentList();

	auto it = browser_registered_function_.find(std::make_pair(function_name, browser->GetIdentifier()));
	if (it != browser_registered_function_.cend())
	{
		auto function = it->second;
		nbase::ThreadManager::PostTask(kThreadUI, [=]() {
			function(params, [=](bool has_error, const std::string& json_result) {
				// ���Դ��룬��Ҫ��װ����������
				args->SetInt(0, js_callback_id);
				args->SetBool(1, has_error);
				args->SetString(2, json_result);
				browser->SendProcessMessage(PID_RENDERER, message);
			});
		});
		return true;
	}

	it = browser_registered_function_.find(std::make_pair(function_name, -1));
	if (it != browser_registered_function_.cend())
	{
		auto function = it->second;
		nbase::ThreadManager::PostTask(kThreadUI, [=]() {
			function(params, [=](bool has_error, const std::string& json_result) {
				// ���Դ��룬��Ҫ��װ����������
				args->SetInt(0, js_callback_id);
				args->SetBool(1, has_error);
				args->SetString(2, json_result);
				browser->SendProcessMessage(PID_RENDERER, message);
			});
		});
		return true;
	}
	else
	{
		args->SetInt(0, js_callback_id);
		args->SetBool(1, true);
		args->SetString(2, R"({"message":"Function does not exist."})");
		browser->SendProcessMessage(PID_RENDERER, message);
		return false;
	}
}

}
