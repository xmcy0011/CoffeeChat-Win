#include "stdafx.h"
#include "cef_manager.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/base/cef_bind.h"

#include "cef_control/app/client_app.h"
#include "cef_control/handler/browser_handler.h"

namespace nim_comp
{

BOOL CefMessageLoopDispatcher::IsIdleMessage(const MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
	case WM_PAINT:
		return FALSE;
	}

	return TRUE;
}

bool CefMessageLoopDispatcher::Dispatch(const MSG &msg)
{
	static BOOL bDoIdle = TRUE;

	TranslateMessage(&msg);
	DispatchMessage(&msg);

	if (IsIdleMessage(&msg))
	{
		bDoIdle = TRUE;
	}

	while (bDoIdle && !::PeekMessage(const_cast<MSG*>(&msg), NULL, 0, 0, PM_NOREMOVE))
	{
		CefDoMessageLoopWork();
		bDoIdle = FALSE;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////

// ����һ���ǳ������bug��������Ⱦ+���߳���Ϣѭ��ģʽ�£���������������һ������˵������޷������رյ�
// ��cefԴ����ֲ˵�����TrackPopupMenu���������ģ���MSDN�����ϲ鿴���ֵ���TrackPopupMenuǰ
// ��Ҫ���丸���ڵ���SetForegroundWindow��������cefԴ����û�е���
// ���շ�cefԴ���õ��Ľ����������cef��UI�̴߳���һ�����ڣ��������ĸ����ڱ�������������UI�̴߳�����
// ��������֮��Ͳ�����ֲ˵��޷��رյ�bug�ˣ���Ȼ��֪��Ϊʲô����bug�����
void FixContextMenuBug(HWND hwnd)
{
	CreateWindow(L"Static", L"", WS_CHILD, 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
	PostMessage(hwnd, WM_CLOSE, 0, 0);
}

///////////////////////////////////////////////////////////////////////////////////
CefManager::CefManager()
{
	browser_count_ = 0;
	is_enable_offset_render_ = true;
}

void CefManager::AddCefDllToPath()
{
#if !defined(SUPPORT_CEF)
	return;
#endif

	TCHAR path_envirom[4096] = { 0 };
	GetEnvironmentVariable(L"path", path_envirom, 4096);
	
	std::wstring cef_path = nbase::win32::GetCurrentModuleDirectory();
#ifdef _DEBUG
	//cef_path += L"cef_debug"; // ���ڼ�ʹ��debugģʽ��Ҳʹ��cef release�汾��dll��Ϊ�����ε�cef�˳�ʱ���жϣ��������Ҫ����cef�Ĺ��ܲ���Ҫʹ��debug�汾��dll
	cef_path += L"cef";
#else
	cef_path += L"cef";
#endif
	if (!nbase::FilePathIsExist(cef_path, true))
	{
		MessageBox(NULL, L"���ѹCef.rarѹ����", L"��ʾ", MB_OK);
		exit(0);
	}
	std::wstring new_envirom(cef_path);
	new_envirom.append(L";").append(path_envirom);
	SetEnvironmentVariable(L"path", new_envirom.c_str());

	// �������flash�����ڿ������
	// https://blog.csdn.net/zhuhongshu/article/details/77482985
	std::wstring cmd_path = cef_path + L"\\dummy_cmd.exe";
	SetEnvironmentVariable(L"ComSpec", cmd_path.c_str());
}

// Cef�ĳ�ʼ���ӿڣ�ͬʱ��ע��ʹ�ø����汾��Cefʱ�����ĸ��ֿ�
// Cef1916�汾���ȶ�����������ʹ������������ĳЩ��debugģʽ��ҳ��ʱ����жϾ��棨�������Ǵ��󣩣���������Ϊ����html��׼֧�ֲ�����������releaseģʽ������ʹ��
// Cef2357�汾�޷�ʹ�ã����������ض�����Ϣ�������¼���ҳ�����Ⱦ���̻����
// Cef2526��2623�汾�Ը�����ҳ�涼֧�֣�Ψһ�ĿӾ���debugģʽ�ڶ��߳���Ϣѭ�������£������˳�ʱ���жϣ�����releaseģʽ������
//		(PS:��������߲�ʹ�ø���Cef���ܵĿ����������л���releaseģʽ��cef dll�ļ���������ʹ��deubg��Ҳ���ᱨ���޸�AddCefDllToPath��������л���releaseĿ¼)
bool CefManager::Initialize(const std::wstring& app_data_dir, CefSettings &settings, bool is_enable_offset_render /*= true*/)
{
#if !defined(SUPPORT_CEF)
	return true;
#endif
	is_enable_offset_render_ = is_enable_offset_render;

	CefMainArgs main_args(GetModuleHandle(NULL));
	CefRefPtr<ClientApp> app(new ClientApp);
	
	// ��������ӽ����е��ã������ֱ���ӽ����˳�������exit_code���ش��ڵ���0
	// �����Browser�����е��ã�����������-1
	int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
	if (exit_code >= 0)
		return false;

	GetCefSetting(app_data_dir, settings);

	bool bRet = CefInitialize(main_args, settings, app.get(), NULL);
	
	if (is_enable_offset_render_)
	{
		HWND hwnd = CreateWindow(L"Static", L"", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
		CefPostTask(TID_UI, base::Bind(&FixContextMenuBug, hwnd));
	}

	return bRet;
}

void CefManager::UnInitialize()
{
#if !defined(SUPPORT_CEF)
	return;
#endif
	CefShutdown();
}

bool CefManager::IsEnableOffsetRender() const
{
	return is_enable_offset_render_;
}

nbase::Dispatcher* CefManager::GetMessageDispatcher()
{
	return &message_dispatcher_;
}

void CefManager::AddBrowserCount()
{
	browser_count_++;
}

void CefManager::SubBrowserCount()
{
	browser_count_--;
	ASSERT(browser_count_ >= 0);
}

int CefManager::GetBrowserCount()
{
	return browser_count_;
}

void CefManager::PostQuitMessage(int nExitCode)
{
#if !defined(SUPPORT_CEF)
	::PostQuitMessage(nExitCode);
	return;
#endif

	// ��������Ҫ��������ʱ��ǧ��Ҫֱ�ӵ���::PostQuitMessage�����ǿ��ܻ������������û������
	// Ӧ�õ�����������������ٺ��ٵ���::PostQuitMessage
	if (browser_count_ == 0)
	{
		nbase::ThreadManager::PostTask(kThreadUI, [nExitCode]()
	 	{
			::PostQuitMessage(nExitCode);
		});
	}
	else
	{
		auto cb = [nExitCode]()
		{
			CefManager::GetInstance()->PostQuitMessage(nExitCode);
		};

		nbase::ThreadManager::PostDelayedTask(kThreadUI, cb, nbase::TimeDelta::FromMilliseconds(500));
	}
}

void CefManager::GetCefSetting(const std::wstring& app_data_dir, CefSettings &settings)
{
	if (false == nbase::FilePathIsExist(app_data_dir, true))
		nbase::CreateDirectory(app_data_dir);

	settings.no_sandbox = true;

	// ����localstorage����Ҫ��·��ĩβ��"\\"����������ʱ�ᱨ��
	CefString(&settings.cache_path) = app_data_dir + L"CefLocalStorage";

	// ����debug log�ļ�λ��
	CefString(&settings.log_file) = app_data_dir + L"cef.log";

	// ����ģ����ʹ�õ����̣�����ǧ��Ҫ��release�����汾��ʹ�ã��ٷ��Ѿ����Ƽ�ʹ�õ�����ģʽ
	// cef1916�汾debugģʽ:�ڵ�����ģʽ�³����˳�ʱ�ᴥ���ж�
#ifdef _DEBUG
	settings.single_process = true;
#else
	settings.single_process = false;
#endif

	// cef2623��2526�汾debugģʽ:��ʹ��multi_threaded_message_loopʱ�˳�����ᴥ���ж�
	// ����disable-extensions���������޸�������⣬���ǻᵼ��һЩҳ���ʱ����
	// ����Cef���߳���Ϣѭ��������nbase����Ϣѭ��
	settings.multi_threaded_message_loop = true;

	// ����������Ⱦ
	settings.windowless_rendering_enabled = is_enable_offset_render_;
}

}