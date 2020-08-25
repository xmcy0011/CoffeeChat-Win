#include "stdafx.h"
#include "toast.h"

using namespace ui;

namespace nim_comp {

const LPCTSTR Toast::kClassName = L"Toast";

void Toast::ShowToast(const std::wstring &content, int duration, HWND parent)
{
	Toast *toast = new Toast;
	HWND hWnd = toast->Create(parent, L"", WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	if (hWnd == NULL)
		return;

	toast->SetContent(content);
	toast->SetDuration(duration);
	toast->CenterWindow();
	toast->ShowWindow(true);
}

std::wstring Toast::GetSkinFolder()
{
	return L"toast";
}

std::wstring Toast::GetSkinFile()
{
	return L"toast.xml";
}

std::wstring Toast::GetWindowClassName() const
{
	return kClassName;
}

std::wstring Toast::GetWindowId() const
{
	return kClassName;
}

UINT Toast::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

LRESULT Toast::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_ESCAPE)
	{
		this->Close();
	}
	// ����toast���涼�ڱ�����������Ҫ����WM_NC��Ϣ
	else if (uMsg == WM_NCLBUTTONDBLCLK || uMsg == WM_LBUTTONDBLCLK)
	{
		this->Close();
	}
	// duilib��WM_MOUSELEAVE��Ϣ�лᷢ��һ��lparamΪ-1��WM_MOUSEMOVE��Ϣ
	else if ((uMsg == WM_NCMOUSEMOVE || uMsg == WM_MOUSEMOVE) && lParam != -1)
	{
		if (NULL != close_button_ && !close_button_->IsVisible())
			close_button_->SetVisible(true);
	}
	else if (uMsg == WM_NCMOUSELEAVE || uMsg == WM_MOUSELEAVE)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(m_hWnd, &pt);
		UiRect client_rect;
		::GetClientRect(m_hWnd, &client_rect);
		// leave��Ϣ����ʱ����ȡ����������п��ܻ���client_rect��Χ�ڣ���ƫ��1���أ���������1����
		client_rect.Deflate(UiRect(1, 1, 1, 1));
		if (NULL != close_button_ && !client_rect.IsPointIn(pt))
			close_button_->SetVisible(false);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Toast::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&Toast::OnClicked, this, std::placeholders::_1));

	content_ = static_cast<RichEdit*>(FindControl(L"content"));
	close_button_ = static_cast<Button*>(FindControl(L"close_btn"));
}

void Toast::SetDuration(int duration)
{
	if (duration <= 0)
		return;

	nbase::ThreadManager::PostDelayedTask(kThreadUI, ToWeakCallback([this]()
	{
		this->Close();
	}), nbase::TimeDelta::FromMilliseconds(duration));
}

bool Toast::OnClicked(ui::EventArgs* msg)
{
	std::wstring name = msg->pSender->GetName();
	if (name == L"close_btn")
	{
		this->Close();
	}

	return true;
}

void Toast::SetContent(const std::wstring &str)
{
	content_->SetText(str);

	int width = content_->GetFixedWidth();

	ui::CSize sz = content_->GetNaturalSize(width, 0);
	content_->SetFixedHeight(sz.cy);
}
}