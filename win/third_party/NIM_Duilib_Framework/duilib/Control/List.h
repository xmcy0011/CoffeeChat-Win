#ifndef UI_CONTROL_LIST_H_
#define UI_CONTROL_LIST_H_

#pragma once

#include "Label.h"
#include "Box/VBox.h"
#include "Box/HBox.h"
#include "Button.h"
#include "CheckBox.h"
#include "Option.h"

namespace ui 
{

typedef int (CALLBACK *PULVCompareFunc)(UINT_PTR, UINT_PTR, UINT_PTR);

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API IListOwner
{
public:
	virtual int GetCurSel() const = 0;
	virtual bool SelectItem(int iIndex, bool bTakeFocus = false, bool bTrigger = true) = 0;
	virtual void HandleMessageTemplate(EventArgs& event) = 0;
	virtual void EnsureVisible(const UiRect& rcItem) = 0;
	virtual void StopScroll() {}
};


/////////////////////////////////////////////////////////////////////////////////////
//

/// �б�����������չʾһ������ʹ��
class UILIB_API ListBox : public ScrollableBox, public IListOwner
{
public:
	ListBox(Layout* pLayout = new VLayout);
	ListBox(const ListBox& r) = delete;
	ListBox& operator=(const ListBox& r) = delete;

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void HandleMessage(EventArgs& event) override;	
	virtual void HandleMessageTemplate(EventArgs& event) override;
	virtual int GetCurSel() const override;
	virtual bool SelectItem(int iIndex, bool bTakeFocus = false, bool bTrigger = true) override;
	virtual void EnsureVisible(const UiRect& rcItem) override;
	virtual void StopScroll() override;
	virtual bool ButtonDown(EventArgs& msg) override;

	/**
	 * @brief ������ָ������λ��
	 * @param[in] strItemName ��������
	 * @return �ɹ����� true������Ϊ false�����ܿؼ�������
	 */
	virtual bool ScrollItemToTop(const std::wstring& strItemName);

	/**
	 * @brief ��ȡ��ǰλ�õ�һ������
	 * @return ���ص�һ������ָ��
	 */
	virtual Control* GetTopItem();
	
	/**
	 * @brief ���������λ������
	 * @param[in] pControl ����ָ��
	 * @param[in] iIndex ������
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool SetItemIndex(Control* pControl, std::size_t iIndex);

	/**
	 * @brief ѡ����һ��
	 * @return ��
	 */
	void Previous();

	/**
	 * @brief ѡ����һ��
	 * @return ��
	 */
	void Next();

	/**
	 * @brief ����ѡ�����˫���¼�
	 * @return ��
	 */
	void ActiveItem();

	/**
	 * @brief ׷��һ�����ĩβ
	 * @param[in] pControl ����ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool Add(Control* pControl);

	/**
	 * @brief ��ָ��λ��֮�����һ������
	 * @param[in] pControl ����ָ��
	 * @param[in] iIndex Ҫ�����λ������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool AddAt(Control* pControl, int iIndex);

	/**
	 * @brief ��������ָ��
	 * @param[in] pControl ����ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool Remove(Control* pControl);

	/**
	 * @brief ���������Ƴ�һ������
	 * @param[in] iIndex ��������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
    bool RemoveAt(int iIndex);

	/**
	 * @brief �Ƴ���������
	 * @return ��
	 */
    void RemoveAll();

	/**
	 * @brief ��������
	 * @param[in] pfnCompare �Զ���������
	 * @param[in] dwData ��������Ա�ʱ������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool SortItems(PULVCompareFunc pfnCompare, UINT_PTR dwData);

	/**
	 * @brief Ĭ�ϵ�����Աȷ���
	 * @param[in] pvlocale ���� List ָ��
	 * @param[in] item1 ����1
	 * @param[in] item2 ����2
	 * @return ���ضԱȽ��
	 */
	static int __cdecl ItemComareFunc(void *pvlocale, const void *item1, const void *item2);
	int __cdecl ItemComareFunc(const void *item1, const void *item2);

	/**
	 * @brief ��ȡ�Ƿ�������ı�ѡ��������
	 * @return ���� true ��ʾ����������ı�ѡ�������Ϊ false
	 */
	bool GetScrollSelect();

	/**
	 * @brief �����Ƿ�������ı�ѡ��������
	 * @param[in] bScrollSelect Ϊ true ��Ϊ����������ı�ѡ���false Ϊ������
	 * @return ��
	 */
	void SetScrollSelect(bool bScrollSelect);

	/**
	 * @brief ����ѡ��������¼�
	 * @param[in] callback ѡ������ʱ�Ļص�����
	 * @return ��
	 */
	void AttachSelect(const EventCallback& callback) { OnEvent[kEventSelect] += callback; }

	/**
	 * @brief ���Ƴ�һ��������Զ�ѡ����һ��
	 * @param[in] bSelectNextItem Ϊ true ʱ�Զ�ѡ����һ�false Ϊ���Զ�ѡ��
	 * @return ��
	 */
	void SelectNextWhenActiveRemoved(bool bSelectNextItem);
private:
	bool m_bScrollSelect;
    int m_iCurSel;
	bool m_bSelNextWhenRemoveActive;
	PULVCompareFunc m_pCompareFunc;
	UINT_PTR m_pCompareData;
};

/////////////////////////////////////////////////////////////////////////////////////
//


/// �б���������б���չʾ���ݵ�����
class UILIB_API ListContainerElement : public OptionTemplate<Box>
{
public:
	ListContainerElement();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void SetVisible(bool bVisible = true) override;
	virtual void Selected(bool bSelect, bool trigger) override;
	virtual void HandleMessage(EventArgs& event) override;

	/**
	 * @brief ��ȡ������
	 * @return ���ظ�����ָ��
	 */
	IListOwner* GetOwner();

	/**
	 * @brief ���ø�����
	 * @param[in] pOwner ������ָ��
	 * @return ��
	 */
	void SetOwner(IListOwner* pOwner);

	/**
	 * @brief ��ȡ��ǰ����
	 * @return ���ص�ǰ����
	 */
	int GetIndex() const;

	/**
	 * @brief ��������
	 * @param[in] iIndex ����ֵ
	 * @return ��
	 */
	void SetIndex(int iIndex);

	/**
	 * @brief ����˫���¼�
	 * @return ��
	 */
	void InvokeDoubleClickEvent();

	/**
	 * @brief �����ؼ�˫���¼�
	 * @param[in] callback �յ�˫����Ϣʱ�Ļص�����
	 * @return ��
	 */
	void AttachDoubleClick(const EventCallback& callback) { OnEvent[kEventMouseDoubleClick] += callback; }

	/**
	 * @brief �����س��¼�
	 * @param[in] callback �յ��س�ʱ�Ļص�����
	 * @return ��
	 */
	void AttachReturn(const EventCallback& callback) { OnEvent[kEventReturn] += callback; }

protected:
	int m_iIndex;
	IListOwner* m_pOwner;
};

} // namespace ui

#endif // UI_CONTROL_LIST_H_
