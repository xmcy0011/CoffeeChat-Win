#pragma once

// �� ui::ListContainerElement �м̳����п��ù���
class Item : public ui::ListContainerElement
{
public:
	Item();
	~Item();

	// �ṩ�ⲿ��������ʼ�� item ����
	void InitSubControls(const std::wstring& img, const std::wstring& title);
	
private:
	bool OnRemove(ui::EventArgs* args);

private:
	ui::ListBox*	list_box_;

	ui::Control*	control_img_;
	ui::Label*		label_title_;
	ui::Progress*	progress_;
	ui::Button*		btn_del_;
};

