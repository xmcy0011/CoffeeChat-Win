#include "stdafx.h"
#include "client_app.h" 
#include <string>

#include "include/cef_cookie.h"
#include "include/cef_process_message.h"
#include "include/cef_task.h"
#include "include/cef_v8.h"
#include "cef_control/manager/cef_manager.h"
#include "cef_control/util/util.h"

namespace nim_comp
{

ClientApp::ClientApp() 
{
	last_node_is_editable_ = false;
}

//////////////////////////////////////////////////////////////////////////////////////////
// CefApp methods.
void ClientApp::OnBeforeCommandLineProcessing(const CefString& process_type, CefRefPtr<CefCommandLine> command_line)
{
	// Pass additional command-line flags to the browser process.
	if (process_type.empty()) 
	{
		command_line->AppendSwitchWithValue("ppapi-flash-version", "20.0.0.228");
		command_line->AppendSwitchWithValue("ppapi-flash-path", "PepperFlash\\pepflashplayer.dll");

		//ͬһ�����µ�ʹ��ͬһ����Ⱦ����
		command_line->AppendSwitch("process-per-site");
		command_line->AppendSwitch("disable-gpu");
		command_line->AppendSwitch("disable-gpu-compositing");
		//command_line->AppendSwitchWithValue("proxy-server", "SOCKS5://127.0.0.1:1080");	

		// ����������Ⱦ
		if (CefManager::GetInstance()->IsEnableOffsetRender())
		{
			command_line->AppendSwitch("disable-surfaces");
			command_line->AppendSwitch("enable-begin-frame-scheduling");
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void ClientApp::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar)
{
	// Default schemes that support cookies.
	cookieable_schemes_.push_back("http");
	cookieable_schemes_.push_back("https");
}

}