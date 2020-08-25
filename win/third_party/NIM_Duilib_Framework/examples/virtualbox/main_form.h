#pragma once
#include "VirtualTileBox.h"
#include "provider.h"

class MainForm : public ui::WindowImplBase
{
public:
	MainForm();
	~MainForm();

	/**
	* һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	* GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	* GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	* GetWindowClassName	�ӿ����ô���Ψһ��������
	*/
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	* �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	*/
	virtual void InitWindow() override;

	/**
	* �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	static const std::wstring kClassName;

private:
	bool OnClicked(ui::EventArgs* args);

private:
	VirtualTileBox*	m_pTileList;
	Provider* m_DataProvider;

private:
	ui::RichEdit* m_EditColumn;
	ui::CheckBox* m_CheckBoxItemCenter; 
	ui::RichEdit* m_EditTotal;
	ui::Option* m_OptionColumnFix;
	ui::RichEdit* m_EditUpdate;
	ui::RichEdit* m_EditTaskName;
	ui::RichEdit* m_EditDelete;
	ui::RichEdit* m_EditChildMargin;
};
