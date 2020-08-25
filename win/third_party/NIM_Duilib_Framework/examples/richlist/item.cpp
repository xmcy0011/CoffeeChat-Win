#include "stdafx.h"
#include "item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::InitSubControls(const std::wstring& img, const std::wstring& title)
{
	// ���� Item �µĿؼ�
	control_img_	= dynamic_cast<ui::Control*>(FindSubControl(L"control_img"));
	label_title_	= dynamic_cast<ui::Label*>(FindSubControl(L"label_title"));
	progress_		= dynamic_cast<ui::Progress*>(FindSubControl(L"progress"));
	btn_del_		= dynamic_cast<ui::Button*>(FindSubControl(L"btn_del"));

	// ģ�����������
	nbase::TimeDelta time_delta = nbase::TimeDelta::FromMicroseconds(nbase::Time::Now().ToInternalValue());
	progress_->SetValue((double)(time_delta.ToMilliseconds() % 100));

	// ����ͼ�����������
	control_img_->SetBkImage(img);
	label_title_->SetText(nbase::StringPrintf(L"%s %d%%", title.c_str(), time_delta.ToMilliseconds() % 100));

	// ��ɾ����������
	btn_del_->AttachClick(nbase::Bind(&Item::OnRemove, this, std::placeholders::_1));
}

bool Item::OnRemove(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent->Remove(this);
}
