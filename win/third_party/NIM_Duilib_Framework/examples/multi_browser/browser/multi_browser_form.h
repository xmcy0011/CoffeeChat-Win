/** @file multi_browser_form.h
* @brief ����ģʽCef���ǩ���������
* @copyright (c) 2016, NetEase Inc. All rights reserved
* @author Redrain
* @date 2019/3/20
*/
#pragma once
#include "taskbar/taskbar_manager.h"
#include "ShObjidl.h"

interface IDropTargetHelper;

class BrowserBox;
class BrowserTabItem;
class MultiBrowserForm : public nim_comp::ShadowWndBase, public IDropTarget, public TaskbarManager::ITaskbarDelegate
{
public:
	MultiBrowserForm();
	~MultiBrowserForm() { };
	
	//�����麯��
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual UINT GetClassStyle() const override;
	

	/**
	* ���ڳ�ʼ������
	* @return void	�޷���ֵ
	*/
	virtual void InitWindow() override;

	/**
	* ���ݿؼ����������Զ���ؼ�
	* @param[in] pstrClass �ؼ�����
	* @return Control* �����Ŀؼ���ָ��
	*/
	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;

	/**
	* ���ز�����ײ㴰����Ϣ
	* @param[in] uMsg ��Ϣ����
	* @param[in] wParam ���Ӳ���
	* @param[in] lParam ���Ӳ���
	* @param[in out] bHandled �Ƿ�������Ϣ����������˲�����������Ϣ
	* @return LRESULT ������
	*/
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/**
	* ���ز�����WM_CLOSE��Ϣ
	* @param[in] uMsg ��Ϣ����
	* @param[in] wParam ���Ӳ���
	* @param[in] lParam ���Ӳ���
	* @param[in] lParam ���Ӳ���
	* @param[in] bHandled �Ƿ�������Ϣ����������˲�����������Ϣ
	* @return LRESULT ������
	*/
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	/**
	* ������������Ϣ
	* @return void	�޷���ֵ
	*/
	virtual void OnFinalMessage(HWND hWnd) override;

private:
	void OnWndSizeMax(bool max);
	bool OnClicked(ui::EventArgs* arg);
	bool OnReturn(ui::EventArgs* arg);

public:
	/**
	* �ڱ������ڴ���һ�������������
	* @param[in] browser_id �����id
	* @param[in] url ��ʼ��URL
	* @return BrowserBox* ���������
	*/
	BrowserBox* CreateBox(const std::string &browser_id, std::wstring url);

	/**
	* �رձ������ڵ�һ�����������
	* @param[in] browser_id �����id
	* @return void	�޷���ֵ
	*/
	void CloseBox(const std::string &browser_id);

	/**
	* ��һ�����������ڵ���������Ӹ��ӵ���������
	* @param[in] browser_box ���������
	* @return bool true �ɹ���false ʧ��
	*/
	bool AttachBox(BrowserBox *browser_box);

	/**
	* �ѱ������ڵ�һ��������������봰��
	* @param[in] browser_box ���������
	* @return bool true �ɹ���false ʧ��
	*/
	bool DetachBox(BrowserBox *browser_box);

	/**
	* ��ȡ��ǰ��ʾ�����������
	* @return BrowserBox* ���������
	*/
	BrowserBox* GetSelectedBox();

	/**
	* ����л���ĳ�����������(ͬʱ����������ڼ���)
	* @param[in] browser_id �����id
	* @return void �޷���ֵ
	*/
	void SetActiveBox(const std::string &browser_id);

	/**
	* �ж�����������Ƿ��ڼ���״̬(ͬʱ�ж�����������Ƿ񱻼���)
	* @param[in] browser_box ���������
	* @return bool true �ǣ�false ��
	*/
	bool IsActiveBox(const BrowserBox *browser_box);

	/**
	* �ж�����������Ƿ��ڼ���״̬(ͬʱ�ж�����������Ƿ񱻼���)
	* @param[in] browser_id �����id
	* @return bool true �ǣ�false ��
	*/
	bool IsActiveBox(const std::wstring &browser_id);

	/**
	* ��ȡ����������������ӵ�����
	* @return int	����
	*/
	int GetBoxCount() const;

	/**
	* ��ִ����ק����ǰ���������ק��������������ڱ����ڣ���֪ͨ������
	* @param[in] browser_id �����id
	* @return void	�޷���ֵ
	*/
	void OnBeforeDragBoxCallback(const std::wstring &browser_id);

	/**
	* ��ִ����ק�������������ק��������������ڱ����ڣ���֪ͨ�����ڲ������
	* @param[in] drop_succeed ����������Ƿ���ק�����ⲿ
	* @return void	�޷���ֵ
	*/
	void OnAfterDragBoxCallback(bool drop_succeed);

private:

	/**
	* �����ǩ�ؼ���ѡ����Ϣ
	* @param[in] param ��Ϣ�������Ϣ
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnTabItemSelected(ui::EventArgs* param);

	/**
	* �����ǩ�ؼ��Ĺرհ�ť�ĵ�����Ϣ
	* @param[in] param ��Ϣ�������Ϣ
	* @param[in] browser_id �б����Ӧ�������id
	* @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	*/
	bool OnTabItemClose(ui::EventArgs* param, const std::string& browser_id);

	/**
	* �ڱ������ڲ������������
	* @param[in] browser_id �����id
	* @return BrowserBox* ���������
	*/
	BrowserBox* FindBox(const std::wstring &browser_id);

	/**
	* �ڱ������ڲ��ұ�ǩ�ؼ�
	* @param[in] browser_id �����id
	* @return BrowserBox* ���������
	*/
	BrowserTabItem* FindTabItem(const std::wstring &browser_id);

	/**
	* �л�ĳ�����������Ϊ��ʾ״̬
	* @param[in] browser_id �����id
	* @return bool true �ɹ���false ʧ��
	*/
	bool ChangeToBox(const std::wstring &browser_id);

public:
	/**
	* ��ȡ������
	* @return HWND	������
	*/
	virtual HWND GetHandle() const override { return this->GetHWND(); };

	/**
	* ��ȡ��Ⱦ������
	* @return IRenderContext*	��Ⱦ������
	*/
	virtual HDC GetRenderDC() const override { return this->GetRenderContext()->GetDC(); };

	/**
	* �ر�һ����������
	* @param[in] id ��������id
	* @return void	�޷���ֵ
	*/
	virtual void CloseTaskbarItem(const std::string &id) override { CloseBox(id); }

	/**
	* ����л���һ����������
	* @param[in] id ��������id
	* @return void �޷���ֵ
	*/
	virtual void SetActiveTaskbarItem(const std::string &id) override { SetActiveBox(id); }

	/**
	* ����ĳ���������Ӧ�ı�ǩ�ؼ��ı���
	* @param[in] browser_id �����id
	* @param[in] name ����
	* @return void	�޷���ֵ
	*/
	void SetTabItemName(const std::wstring &browser_id, const std::wstring &name);

	/**
	* ����ĳ���������Ӧ�ı�ǩ�ؼ���URL
	* @param[in] browser_id �����id
	* @param[in] url URL
	* @return void	�޷���ֵ
	*/
	void SetURL(const std::string &browser_id, const std::wstring &url);

public:

	/**
	* ��ʼ�������ϷŹ���
	* @return void	�޷���ֵ
	*/
	bool InitDragDrop();

	/**
	* ����ʼ�������ϷŹ���
	* @return void	�޷���ֵ
	*/
	void UnInitDragDrop();

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	HRESULT STDMETHODCALLTYPE DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragLeave(void);
	HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect);

private:
	/**
	* �ж��Ƿ�Ҫ��ק���������
	* @param[in] param ����������������Ự�ϲ��б���͵��¼�
	* @return bool ����ֵtrue: �������ݿؼ���Ϣ�� false: ֹͣ���ݿؼ���Ϣ
	*/
	bool OnProcessTabItemDrag(ui::EventArgs* param);

	/**
	* ���ɵ�ǰ������ĳ�������Ӧ��λͼ������������Ⱦģʽ
	* @param[in] src_rect Ŀ��λͼ��λ��
	* @return HBITMAP ���ɵ�λͼ
	*/
	HBITMAP GenerateBoxOffsetRenderBitmap(const ui::UiRect &src_rect);

	/**
	* ���ɵ�ǰ�������������ӵ�λͼ�������д�ģʽ
	* @param[in] src_rect Ŀ��λͼ��λ��
	* @return HBITMAP ���ɵ�λͼ
	*/
	HBITMAP GenerateBoxWindowBitmap();

public:
	static const LPCTSTR kClassName;

private:
	ui::Label		*lbl_title_;
	ui::Button		*btn_max_restore_;
	ui::RichEdit	*edit_url_;

	ui::ListBox			*tab_list_;
	ui::TabBox			*borwser_box_tab_;
	BrowserBox			*active_browser_box_;

	// ��������������Ϸ��¼�
	IDropTargetHelper	*drop_helper_;

	// ���������������ק�¼�
	bool				is_drag_state_;
	POINT				old_drag_point_;
	std::wstring		draging_browser_id_;

	// ����������ͼ������
	TaskbarManager		taskbar_manager_;
};