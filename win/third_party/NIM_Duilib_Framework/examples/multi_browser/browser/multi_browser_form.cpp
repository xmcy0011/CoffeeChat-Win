#include "multi_browser_form.h"
#include "browser/browser_box.h"
#include "browser/multi_browser_manager.h"
#include "control/browser_tab_item.h"
#include "custom_layout.h"

using namespace ui;
using namespace std;
using namespace nim_comp;

namespace
{
	// ע�������Ϣ���յ������Ϣ���ʾ���ڶ�Ӧ����������ť��ϵͳ��������ʱ���ʼ��ITaskbarList4�ӿ�
	UINT WM_TASKBARBUTTONCREATED = ::RegisterWindowMessage(TEXT("TaskbarButtonCreated"));

	// �����յ�WM_CLOSE��Ϣ��ԭ��
	enum CloseReason
	{
		kDefaultClose = 0,		// ���������һ��رմ��ڣ���Alt+F4�ȳ���ԭ��
		kBrowserBoxClose = 1	// �ر������һ����������ӵ��´��ڹر�
	};
}

const LPCTSTR MultiBrowserForm::kClassName = L"MultiBrowserForm";

MultiBrowserForm::MultiBrowserForm()
{
	btn_max_restore_ = nullptr;

	drop_helper_ = NULL;

	tab_list_ = NULL;
	borwser_box_tab_ = NULL;
	active_browser_box_ = NULL;

	is_drag_state_ = false;
	old_drag_point_.x = old_drag_point_.y = 0;
}

std::wstring MultiBrowserForm::GetSkinFolder()
{
	return L"multi_browser";
}

std::wstring MultiBrowserForm::GetSkinFile()
{
	return L"multi_browser.xml";
}

std::wstring MultiBrowserForm::GetWindowClassName() const
{
	return kClassName;
}

UINT MultiBrowserForm::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

ui::Control* MultiBrowserForm::CreateControl(const std::wstring& pstrClass)
{
	if (pstrClass == _T("CustomTabBox"))
	{
		if ((GetWindowExStyle(this->GetHWND()) & WS_EX_LAYERED) != 0)
			return new TabBox(new CustomLayout);
		else
			return new TabBox(new Layout);
	}

	return NULL;
}

void MultiBrowserForm::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&MultiBrowserForm::OnClicked, this, std::placeholders::_1));
	btn_max_restore_ = static_cast<Button*>(FindControl(L"btn_max_restore"));

	edit_url_ = static_cast<RichEdit*>(FindControl(L"edit_url"));
	lbl_title_ = static_cast<Label*>(FindControl(L"title"));
	edit_url_->AttachReturn(nbase::Bind(&MultiBrowserForm::OnReturn, this, std::placeholders::_1));

	tab_list_ = static_cast<ListBox*>(FindControl(L"tab_list"));
	borwser_box_tab_ = static_cast<TabBox*>(FindControl(L"browser_box_tab"));

	tab_list_->AttachSelect(nbase::Bind(&MultiBrowserForm::OnTabItemSelected, this, std::placeholders::_1));

	InitDragDrop();
}

LRESULT MultiBrowserForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_SIZE)
	{
		if (wParam == SIZE_RESTORED)
			OnWndSizeMax(false);
		else if (wParam == SIZE_MAXIMIZED)
			OnWndSizeMax(true);
	}
	else if (uMsg == WM_KEYDOWN)
	{
		// ����Ctrl+Tab��ݼ�
		if (wParam == VK_TAB && ::GetKeyState(VK_CONTROL) < 0)
		{
			int next = tab_list_->GetCurSel();
			next = (next + 1) % GetBoxCount();
			tab_list_->SelectItem(next);
			return 0;
		}
		// ����ESC��ݼ�
		else if (wParam == VK_ESCAPE)
		{
			BOOL bHandled = FALSE;
			if (!MultiBrowserManager::GetInstance()->IsDragingBorwserBox() && NULL != active_browser_box_)
			{
				this->CloseBox(active_browser_box_->GetId());
			}

			return 0;
		}
	}
	else if (uMsg == WM_TASKBARBUTTONCREATED)
	{
		taskbar_manager_.Init(this);

		// ��Ϊ���ڸմ���ʱ������������Ѿ�����������ʱ��û���յ�WM_TASKBARBUTTONCREATED��Ϣ������RegisterTab����û�б����ã������յ���Ϣ�����±���һ��û�б�ע���Tab
		for (int i = 0; i < borwser_box_tab_->GetCount(); i++)
		{
			Control *box_item = borwser_box_tab_->GetItemAt(i);
			ASSERT(NULL != box_item);
			if (NULL == box_item)
				continue;

			BrowserBox* browser_box = dynamic_cast<BrowserBox*>(box_item);
			if (NULL == browser_box)
				continue;

			TaskbarTabItem* taskbar_item = browser_box->GetTaskbarItem();
			if (NULL == taskbar_item)
				continue;

			taskbar_manager_.RegisterTab(*taskbar_item);
		}

		return TRUE;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT MultiBrowserForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CloseReason closeReason = (CloseReason)wParam;

	// �������Ϊ������������Ӷ��ر��˵��´��ڹرգ�����������
	if (kBrowserBoxClose == closeReason)
	{
		return __super::OnClose(uMsg, wParam, lParam, bHandled);
	}
	// ���������ԭ�򴥷���WM_CLOSE
	else
	{
		int browser_count = GetBoxCount();
		if (browser_count > 0 && NULL != active_browser_box_)
		{
			// ���ֻ��һ����������ӣ���ֱ�ӹر�
			if (1 == browser_count)
			{
				CloseBox(active_browser_box_->GetId());
			}
			// ������������������ӣ���ѯ���û�
			else
			{
				MsgboxCallback cb = ToWeakCallback([this](MsgBoxRet ret)
				{
					if (ret == MB_YES)
					{
						while (GetBoxCount() > 0)
						{
							Control *tab_item = tab_list_->GetItemAt(0);
							ASSERT(NULL != tab_item);
							if (NULL == tab_item)
								break;

							CloseBox(tab_item->GetUTF8Name());
						}
					}
				});
				ShowMsgBox(this->GetHWND(), cb, L"STRID_CEF_BROWSER_CLOSING", true, L"STRING_TIPS", true, L"STRING_OK", true, L"STRING_NO", true);
			}

			bHandled = TRUE;
			return 0;
		}
	}

	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void MultiBrowserForm::OnFinalMessage(HWND hWnd)
{
	// ʹ��tab_list_���ж����������������browser_box_tab_��ȡ��������׼ȷ
	int browser_box_count = GetBoxCount();
	for (int i = 0; i < browser_box_count; i++)
	{
		Control *box_item = borwser_box_tab_->GetItemAt(i);
		ASSERT(NULL != box_item);
		if (NULL == box_item)
			continue;;

		BrowserBox* browser_box = dynamic_cast<BrowserBox*>(box_item);
		if (NULL != browser_box)
			browser_box->UninitBrowserBox();
	}

	UnInitDragDrop();

	__super::OnFinalMessage(hWnd);
}

void MultiBrowserForm::OnWndSizeMax(bool max)
{
	if (btn_max_restore_)
		btn_max_restore_->SetClass(max ? L"btn_wnd_restore" : L"btn_wnd_max");
}

bool MultiBrowserForm::OnClicked( ui::EventArgs* arg )
{
	std::wstring name = arg->pSender->GetName();
	if (name == L"btn_max_restore")
	{
		DWORD style = GetWindowLong(GetHWND(), GWL_STYLE);
		if (style & WS_MAXIMIZE)
			::ShowWindow(GetHWND(), SW_RESTORE);
		else
			::ShowWindow(GetHWND(), SW_MAXIMIZE);
	}
	else if (name == L"btn_close")
	{
		if (NULL == active_browser_box_)
		{
			ASSERT(0);
			return true;
		}

		CloseBox(active_browser_box_->GetId());
	}
	else if (name == L"btn_min")
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
	}
	else if (name == L"btn_add")
	{
		nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
		std::string timeStamp = nbase::StringPrintf("%I64u", time_delta.ToMilliseconds());
		MultiBrowserManager::GetInstance()->CreateBorwserBox(this, timeStamp, L"");
	}
	else if (active_browser_box_)
	{
		auto cef_control = active_browser_box_->GetCefControl();
		if (!cef_control)
			return true;

		if (name == L"btn_back")
		{
			cef_control->GoBack();
		}
		else if (name == L"btn_forward")
		{
			cef_control->GoForward();
		}
		else if (name == L"btn_refresh")
		{
			cef_control->Refresh();
		}
	}

	return true;
}

bool MultiBrowserForm::OnReturn(ui::EventArgs* arg)
{
	std::wstring name = arg->pSender->GetName();
	if (name == L"edit_url")
	{
#if 0
 		// �ڵ�ǰҳ����ת
 		auto cef_control = active_browser_box_->GetCefControl();
 		if (cef_control)
 			cef_control->LoadURL(edit_url_->GetText());
#endif
		nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
		std::string timeStamp = nbase::StringPrintf("%I64u", time_delta.ToMilliseconds());
		// �½���ǩҳ
		MultiBrowserManager::GetInstance()->CreateBorwserBox(this, timeStamp, edit_url_->GetText());
	}

	return false;
}

BrowserBox* MultiBrowserForm::CreateBox(const std::string &browser_id, std::wstring url)
{
	std::wstring id = nbase::UTF8ToUTF16(browser_id);
	if (NULL != FindTabItem(id))
	{
		ASSERT(0);
		return NULL;
	}
	if (NULL != FindBox(id))
	{
		ASSERT(0);
		return NULL;
	}

	BrowserTabItem *tab_item = new BrowserTabItem;
	GlobalManager::FillBoxWithCache(tab_item, L"multi_browser/tab_item.xml");
	tab_list_->AddAt(tab_item, GetBoxCount());
	tab_item->AttachAllEvents(nbase::Bind(&MultiBrowserForm::OnProcessTabItemDrag, this, std::placeholders::_1));
	tab_item->AttachButtonDown(nbase::Bind(&MultiBrowserForm::OnTabItemSelected, this, std::placeholders::_1));
	tab_item->InitControl(browser_id);
	Button *btn_item_close = (Button*)tab_item->FindSubControl(L"tab_item_close");
	btn_item_close->AttachClick(nbase::Bind(&MultiBrowserForm::OnTabItemClose, this, std::placeholders::_1, browser_id));

	BrowserBox* browser_box = new BrowserBox(browser_id);
	borwser_box_tab_->Add(browser_box);
	GlobalManager::FillBoxWithCache(browser_box, L"multi_browser/browser_box.xml", nbase::Bind(&BrowserBox::CreateControl, browser_box, std::placeholders::_1));
	browser_box->SetName(id);
	browser_box->InitBrowserBox(url);
	auto taskbar_item = browser_box->GetTaskbarItem();
	if (taskbar_item)
		taskbar_manager_.RegisterTab(*taskbar_item);

	if (GetBoxCount() <= 1)
		active_browser_box_ = browser_box;

	// �л����µ����������
	// ���tab_item��������״̬�����޷�˳������ѡ���¼�����������ֱ���л���Ŀ�����������
	tab_item->Selected(true, false);
	ChangeToBox(id);

	return browser_box;
}

void MultiBrowserForm::CloseBox(const std::string &browser_id)
{
	if (browser_id.empty())
		return;

	std::wstring id = nbase::UTF8ToUTF16(browser_id);

	// �����Ự�б����Ƴ���Ӧitem
	BrowserTabItem *tab_item = FindTabItem(id);
	if (NULL != tab_item)
	{
		tab_list_->Remove(tab_item);
	}

	// ��������б����ҵ���������Ӳ����Ƴ�����
	BrowserBox *browser_box = FindBox(id);
	ASSERT(NULL != browser_box);
	if (NULL != browser_box)
	{
		auto taskbar_item = browser_box->GetTaskbarItem();
		if (taskbar_item)
			taskbar_manager_.UnregisterTab(*taskbar_item);
		browser_box->UninitBrowserBox();
		// �����������ӵ���������1�������Ƴ����ӣ������Ƴ�
		// ������һ����������������������Ƴ����ڴ��ڹر�ʱ�������Ϊû�пؼ�����ɺ�ɫ
		// ���ڹر�ʱ�����Զ����Ƴ�������������
		if (borwser_box_tab_->GetCount() > 1)
			borwser_box_tab_->Remove(browser_box);
		else
			active_browser_box_ = NULL;
	}

	// ��������������ʱ���ر����������
	if (GetBoxCount() == 0)
	{
		this->Close(kBrowserBoxClose);
	}
}

bool MultiBrowserForm::AttachBox(BrowserBox *browser_box)
{
	if (NULL == browser_box)
		return false;

	std::wstring id = nbase::UTF8ToUTF16(browser_box->GetId());
	if (NULL != FindTabItem(id))
	{
		ASSERT(0);
		return false;
	}
	if (NULL != FindBox(id))
	{
		ASSERT(0);
		return false;
	}

	BrowserTabItem *tab_item = new BrowserTabItem;
	GlobalManager::FillBoxWithCache(tab_item, L"multi_browser/tab_item.xml");
	tab_list_->AddAt(tab_item, GetBoxCount());
	tab_item->AttachAllEvents(nbase::Bind(&MultiBrowserForm::OnProcessTabItemDrag, this, std::placeholders::_1));
	tab_item->AttachButtonDown(nbase::Bind(&MultiBrowserForm::OnTabItemSelected, this, std::placeholders::_1));
	tab_item->InitControl(browser_box->GetId());
	tab_item->SetTitle(browser_box->GetTitle());
	Button *btn_item_close = (Button*)tab_item->FindSubControl(L"tab_item_close");
	btn_item_close->AttachClick(nbase::Bind(&MultiBrowserForm::OnTabItemClose, this, std::placeholders::_1, browser_box->GetId()));

	// ����һ�����崴����browser_box��������ӿؼ���ӵ���һ�������ڵ������ؼ�ʱ
	// Add���������µ��޸�browser_box�������ӿؼ���m_pWindowΪ�µĴ���ָ��
	borwser_box_tab_->Add(browser_box);
	auto taskbar_item = browser_box->GetTaskbarItem();
	if (taskbar_item)
		taskbar_manager_.RegisterTab(*taskbar_item);

	if (GetBoxCount() <= 1)
		active_browser_box_ = browser_box;

	// �л����µ����������
	// ���tab_item��������״̬�����޷�˳������ѡ���¼�����������ֱ���л���Ŀ�����������
	tab_item->Selected(true, false);
	ChangeToBox(id);

	return true;
}

bool MultiBrowserForm::DetachBox(BrowserBox *browser_box)
{
	if (NULL == browser_box)
		return false;

	std::wstring id = nbase::UTF8ToUTF16(browser_box->GetId());

	// �Ӷ�����ǩҳ�Ƴ���Ӧitem
	BrowserTabItem *tab_item = FindTabItem(id);
	if (NULL == tab_item)
		return false;

	tab_list_->Remove(tab_item);

	auto taskbar_item = browser_box->GetTaskbarItem();
	if (taskbar_item)
		taskbar_manager_.UnregisterTab(*taskbar_item);
	// ���Ҳ�Tab����������б����ҵ���������Ӳ����Ƴ�����
	// �����ﲻ��delete browser_box
	bool auto_destroy = borwser_box_tab_->IsAutoDestroy();
	borwser_box_tab_->SetAutoDestroy(false);
	if (!borwser_box_tab_->Remove(browser_box))
	{
		borwser_box_tab_->SetAutoDestroy(auto_destroy);
		return false;
	}
	borwser_box_tab_->SetAutoDestroy(auto_destroy);

	// ��������������ʱ���ر����������
	if (GetBoxCount() == 0)
	{
		this->Close(kBrowserBoxClose);
	}

	return true;
}

BrowserBox* MultiBrowserForm::GetSelectedBox()
{
	return active_browser_box_;
}

void MultiBrowserForm::SetActiveBox(const std::string &browser_id)
{
	if (browser_id.empty())
		return;

	ActiveWindow();

	// �Ӵ������Ự�б��ҵ�Ҫ����������������
	std::wstring id = nbase::UTF8ToUTF16(browser_id);
	BrowserTabItem *tab_item = FindTabItem(id);
	if (NULL == tab_item)
		return;

	// ���tab_item��������״̬�����޷�˳������ѡ���¼�����������ֱ���л���Ŀ�����������
	tab_item->Selected(true, false);
	ChangeToBox(id);
}

bool MultiBrowserForm::IsActiveBox(const BrowserBox *browser_box)
{
	ASSERT(NULL != browser_box);
	return (browser_box == active_browser_box_ && ::GetForegroundWindow() == GetHWND() && !::IsIconic(GetHWND()) && IsWindowVisible(GetHWND()));
}

bool MultiBrowserForm::IsActiveBox(const std::wstring &browser_id)
{
	ASSERT(!browser_id.empty());
	return (::GetForegroundWindow() == GetHWND() && !::IsIconic(GetHWND()) && IsWindowVisible(GetHWND()) && FindBox(browser_id) == active_browser_box_);
}

int MultiBrowserForm::GetBoxCount() const
{
	return tab_list_->GetCount() - 1; // ��ȥ�ұ��Ǹ��Ӻŵ�����
}

void MultiBrowserForm::OnBeforeDragBoxCallback(const std::wstring &browser_id)
{
	// �����ǰ����ק��������������������������ֻ��һ����������ӣ�������קʱ�������������
	int box_count = this->GetBoxCount();
	if (1 == box_count)
	{
		this->ShowWindow(false);
	}
	// �������ر���ק����������Ӻͱ�ǩ
	else
	{
		BrowserBox *browser_box = FindBox(browser_id);
		if (NULL != browser_box)
			browser_box->SetVisible(false);

		BrowserTabItem *tab_item = FindTabItem(browser_id);
		if (NULL != tab_item)
			tab_item->SetVisible(false);

		// �ҵ��µı���ʾ�����������
		int index = tab_item->GetIndex();
		if (index > 0)
			index--;
		else
			index++;
		BrowserTabItem *new_tab_item = static_cast<BrowserTabItem*>(tab_list_->GetItemAt(index));
		if (NULL != new_tab_item)
		{
			new_tab_item->Selected(true, false);
			ChangeToBox(new_tab_item->GetName());
		}

		draging_browser_id_ = browser_id;
	}
}

void MultiBrowserForm::OnAfterDragBoxCallback(bool drop_succeed)
{
	is_drag_state_ = false;

	if (drop_succeed)
	{
		int box_count = this->GetBoxCount();
		// �����ǰ����ק��������������������������ֻ��һ����������ӣ�������ק���µ����������������������ھͻ�ر�
		if (1 == box_count)
		{

		}
		else
		{

		}
	}
	else
	{
		int box_count = this->GetBoxCount();
		// �����ǰ����ק��������������������������ֻ��һ����������ӣ�����û����ק���µ������������
		// ����ʾ���������
		if (1 == box_count)
		{
			this->ShowWindow(true);
		}
		// �����ǰ����ק���������������������������ж����������ӣ�����û����ק���µ������������
		// ����ʾ֮ǰ�����ص���������Ӻͱ�ǩ
		else
		{
			BrowserBox *browser_box = FindBox(draging_browser_id_);
			if (NULL != browser_box)
				browser_box->SetVisible(true);

			BrowserTabItem *tab_item = FindTabItem(draging_browser_id_);
			if (NULL != tab_item)
			{
				tab_item->SetVisible(true);
				tab_item->Selected(true, false);
				ChangeToBox(draging_browser_id_);
			}

			draging_browser_id_.clear();
		}
	}
}

bool MultiBrowserForm::OnTabItemSelected(ui::EventArgs* param)
{
	if (kEventSelect == param->Type)
	{
		std::wstring name = param->pSender->GetName();

		if (name == L"tab_list")
		{
			// ��������˶����ı�ǩ�����ҵ��·�Tab���Ӧ����������Ӳ�ѡ��
			Control *select_item = tab_list_->GetItemAt(tab_list_->GetCurSel());
			ASSERT(NULL != select_item);
			if (NULL == select_item)
				return true;

			std::wstring session_id = select_item->GetName();
			ChangeToBox(session_id);
		}
	}
	else if (kEventMouseButtonDown == param->Type)
	{
		BrowserTabItem *tab_item = dynamic_cast<BrowserTabItem*>(param->pSender);
		if (tab_item)
		{
			std::wstring browser_id = tab_item->GetName();
			ChangeToBox(browser_id);
		}
	}
	return false;
}

bool MultiBrowserForm::OnTabItemClose(ui::EventArgs* param, const std::string& browser_id)
{
	if (param->pSender->GetName() == L"tab_item_close")
	{
		CloseBox(browser_id);
	}

	return false;
}

BrowserBox* MultiBrowserForm::FindBox(const std::wstring &browser_id)
{
	for (int i = 0; i < borwser_box_tab_->GetCount(); i++)
	{
		Control *box_item = borwser_box_tab_->GetItemAt(i);
		ASSERT(NULL != box_item);
		if (NULL == box_item)
			return NULL;

		if (box_item->GetName() == browser_id)
			return dynamic_cast<BrowserBox*>(box_item);
	}

	return NULL;
}

BrowserTabItem* MultiBrowserForm::FindTabItem(const std::wstring &browser_id)
{
	for (int i = 0; i < GetBoxCount(); i++)
	{
		Control *tab_item = tab_list_->GetItemAt(i);
		ASSERT(NULL != tab_item);
		if (NULL == tab_item)
			return NULL;

		if (tab_item->GetName() == browser_id)
			return static_cast<BrowserTabItem*>(tab_item);
	}

	return NULL;
}

void MultiBrowserForm::SetTabItemName(const std::wstring &browser_id, const std::wstring &name)
{
	BrowserTabItem *tab_item = FindTabItem(browser_id);
	if (NULL != tab_item)
	{
		tab_item->SetTitle(name);
	}
}

void MultiBrowserForm::SetURL(const std::string &browser_id, const std::wstring &url)
{
	if (active_browser_box_ && active_browser_box_->GetId() == browser_id)
		edit_url_->SetText(url);
}

bool MultiBrowserForm::ChangeToBox(const std::wstring &browser_id)
{
	if (browser_id.empty())
		return false;

	BrowserBox *box_item = FindBox(browser_id);
	if (NULL == box_item)
		return false;

	borwser_box_tab_->SelectItem(box_item);

	box_item->SetFocus();
	active_browser_box_ = box_item;
	edit_url_->SetText(active_browser_box_->GetCefControl()->GetURL());
	// ���ݵ�ǰ�������������ӣ�������������ͼ��ͱ���

	return true;
}