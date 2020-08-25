#ifndef UI_CONTROL_CHECKBOX_H_
#define UI_CONTROL_CHECKBOX_H_

#pragma once

namespace ui
{

template<typename InheritType = Control>
class UILIB_API CheckBoxTemplate : public ButtonTemplate<InheritType>
{
public:
	CheckBoxTemplate();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void Activate() override;
	virtual Image* GetEstimateImage() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void PaintStatusColor(IRenderContext* pRender) override;
	virtual void PaintStatusImage(IRenderContext* pRender) override;
	virtual void PaintText(IRenderContext* pRender) override;
	virtual bool HasHotState();

	/**
	 * @brief �жϵ�ǰ�Ƿ���ѡ��״̬
	 * @return ���� true Ϊѡ��״̬������Ϊ false
	 */
	bool IsSelected() const { return m_bSelected; }

	/**
	 * @brief ���ÿؼ��Ƿ�ѡ��״̬
	 * @param[in] bSelected Ϊ true ʱΪѡ��״̬��false ʱΪȡ��ѡ��״̬
	 * @param[in] bTriggerEvent �Ƿ���״̬�ı��¼���true Ϊ���ͣ�����Ϊ false��Ĭ��Ϊ false
	 * @return ��
	 */
	virtual void Selected(bool bSelected, bool bTriggerEvent = false);

	/**
	 * @brief ��ȡ��ѡ��ʱ��ͼƬ
	 * @param[in] stateType Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @return ����ͼƬλ��
	 */
	std::wstring GetSelectedStateImage(ControlStateType stateType);

	/**
	 * @brief ���ñ�ѡ��ʱ��ͼƬ
	 * @param[in] stateType Ҫ��������״̬�µ�ͼƬ
	 * @param[in] strImage ͼƬ��ַ
	 * @return ��
	 */
	void SetSelectedStateImage(ControlStateType stateType, const std::wstring& strImage);

	/**
	 * @brief ��ȡ��ѡ��ʱ���ı���ɫ
	 * @return ���ر�ѡ��ʱ���ı���ɫ
	 */
	std::wstring GetSelectedTextColor();

	/**
	 * @brief ���ñ�ѡ��ʱ���ı���ɫ
	 * @param[in] dwTextColor Ҫ���õ���ɫ�ַ���������ɫ������ global.xml �д���
	 * @return ��
	 */
	void SetSelectedTextColor(const std::wstring& dwTextColor);

	/**
	 * @brief ��ȡ��ѡ��ʱ�Ŀؼ���ɫ 
	 * @param[in] stateType Ҫ��ȡ����״̬�µ���ɫ
	 * @return ������ɫ�ַ�������ֵ�� global.xml �ж���
	 */
	std::wstring GetSelectStateColor(ControlStateType stateType);

	/**
	 * @brief ���ñ�ѡ��ʱ�Ŀؼ���ɫ
	 * @param[in] stateType Ҫ���ú���״̬�µ���ɫ
	 * @param[in] stateColor Ҫ���õ���ɫ
	 * @return ��
	 */
	void SetSelectedStateColor(ControlStateType stateType, const std::wstring& stateColor);

	/**
	 * @brief ��ȡ��ѡ��ʱ��ǰ��ͼƬ
	 * @param[in] stateType Ҫ��ȡ����״̬�µ�ǰ��ͼƬ
	 * @return ����ͼƬλ��
	 */
	std::wstring GetSelectedForeStateImage(ControlStateType stateType);

	/**
	 * @brief ���ñ�ѡ��ʱ��ǰ��ͼƬ
	 * @param[in] stateType Ҫ���ú���״̬�µ�ǰ��ͼƬ
	 * @param[in] pStrImage ͼƬλ��
	 * @return ��
	 */
	void SetSelectedForeStateImage(ControlStateType stateType, const std::wstring& pStrImage);

	/**
	 * @brief ������ѡ��ʱ���¼�
	 * @param[in] callback ��ѡ��ʱ�����Ļص�����
	 * @return ��
	 */
	void AttachSelect(const EventCallback& callback) { this->OnEvent[kEventSelect] += callback; }

	/**
	 * @brief ����ȡ��ѡ��ʱ���¼�
	 * @param[in] callback ȡ��ѡ��ʱ�����Ļص�����
	 * @return ��
	 */
	void AttachUnSelect(const EventCallback& callback) { this->OnEvent[kEventUnSelect] += callback; }

protected:
	bool			m_bSelected;
	std::wstring	m_dwSelectedTextColor;
	StateColorMap	m_selectedColorMap;
};

template<typename InheritType>
CheckBoxTemplate<InheritType>::CheckBoxTemplate() : m_bSelected(false), m_dwSelectedTextColor(), m_selectedColorMap()
{
	m_selectedColorMap.SetControl(this);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::Activate()
{
	if (!this->IsActivatable())
		return;
	Selected(!m_bSelected, true);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::Selected(bool bSelected, bool bTriggerEvent)
{
	if (m_bSelected == bSelected) return;
	m_bSelected = bSelected;

	if (this->m_pWindow != NULL) {
		if (bTriggerEvent) {
			if (m_bSelected) {
				this->m_pWindow->SendNotify(this, kEventSelect);
			}
			else {
				this->m_pWindow->SendNotify(this, kEventUnSelect);
			}
		}
	}

	this->Invalidate();
}

template<typename InheritType>
bool CheckBoxTemplate<InheritType>::HasHotState()
{
	return m_selectedColorMap.HasHotColor() || __super::HasHotState();
}

template<typename InheritType>
Image* CheckBoxTemplate<InheritType>::GetEstimateImage()
{
	Image* estimateImage = __super::GetEstimateImage();
	if (!estimateImage) {
		estimateImage = this->m_imageMap.GetEstimateImage(kStateImageSelectedBk);
	}

	return estimateImage;
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == _T("selected")) Selected(strValue == _T("true"), true);
	else if (strName == _T("selectednormalimage")) SetSelectedStateImage(kControlStateNormal, strValue);
	else if (strName == _T("selectedhotimage")) SetSelectedStateImage(kControlStateHot, strValue);
	else if (strName == _T("selectedpushedimage")) SetSelectedStateImage(kControlStatePushed, strValue);
	else if (strName == _T("selecteddisabledimage")) SetSelectedStateImage(kControlStateDisabled, strValue);
	else if (strName == _T("selectedtextcolor")) SetSelectedTextColor(strValue);
	else if (strName == _T("selectednormalcolor")) SetSelectedStateColor(kControlStateNormal, strValue);
	else if (strName == _T("selectedhotcolor")) SetSelectedStateColor(kControlStateHot, strValue);
	else if (strName == _T("selectedpushedcolor")) SetSelectedStateColor(kControlStatePushed, strValue);
	else if (strName == _T("selecteddisabledcolor")) SetSelectedStateColor(kControlStateDisabled, strValue);
	else if (strName == _T("selectedforenormalimage")) SetSelectedForeStateImage(kControlStateNormal, strValue);
	else if (strName == _T("selectedforehotimage")) SetSelectedForeStateImage(kControlStateHot, strValue);
	else if (strName == _T("selectedforepushedimage")) SetSelectedForeStateImage(kControlStatePushed, strValue);
	else if (strName == _T("selectedforedisabledimage")) SetSelectedForeStateImage(kControlStateDisabled, strValue);
	else __super::SetAttribute(strName, strValue);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintStatusColor(IRenderContext* pRender)
{
	if (!IsSelected()) {
		__super::PaintStatusColor(pRender);
		return;
	}

	m_selectedColorMap.PaintStatusColor(pRender, this->m_rcPaint, this->m_uButtonState);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintStatusImage(IRenderContext* pRender)
{
	if (!IsSelected()) {
		__super::PaintStatusImage(pRender);
		return;
	}

	this->m_imageMap.PaintStatusImage(pRender, kStateImageSelectedBk, this->m_uButtonState);
	this->m_imageMap.PaintStatusImage(pRender, kStateImageSelectedFore, this->m_uButtonState);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::PaintText(IRenderContext* pRender)
{
	if (!IsSelected()) {
		__super::PaintText(pRender);
		return;
	}

	if (this->GetText().empty()) return;
	UiRect rc = this->m_rcItem;
	rc.left += this->m_rcTextPadding.left;
	rc.right -= this->m_rcTextPadding.right;
	rc.top += this->m_rcTextPadding.top;
	rc.bottom -= this->m_rcTextPadding.bottom;

	std::wstring newTextColor = m_dwSelectedTextColor.empty() ? this->m_textColorMap[kControlStateNormal] : m_dwSelectedTextColor;
	DWORD dwTextColor = GlobalManager::GetTextColor(newTextColor);
	DWORD dwDisabledTextColor = GlobalManager::GetTextColor(this->m_textColorMap[kControlStateDisabled]);
	pRender->DrawText(rc, this->GetText(), this->IsEnabled() ? dwTextColor : dwDisabledTextColor, this->m_sFontId, this->m_uTextStyle);
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedStateImage(ControlStateType stateType)
{
	return this->m_imageMap.GetImagePath(kStateImageSelectedBk, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedStateImage(ControlStateType stateType, const std::wstring& pStrImage)
{
	this->m_imageMap.SetImage(kStateImageSelectedBk, stateType, pStrImage);
	if (this->GetFixedWidth() == DUI_LENGTH_AUTO || this->GetFixedHeight() == DUI_LENGTH_AUTO) {
		this->ArrangeAncestor();
	}
	else {
		this->Invalidate();
	}
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedTextColor()
{
	return m_dwSelectedTextColor;
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedTextColor(const std::wstring& dwTextColor)
{
	m_dwSelectedTextColor = dwTextColor;
	this->Invalidate();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectStateColor(ControlStateType stateType)
{
	return m_selectedColorMap[stateType];
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedStateColor(ControlStateType stateType, const std::wstring& stateColor)
{
	m_selectedColorMap[stateType] = stateColor;
	this->Invalidate();
}

template<typename InheritType>
std::wstring CheckBoxTemplate<InheritType>::GetSelectedForeStateImage(ControlStateType stateType)
{
	return this->m_imageMap.GetImagePath(kStateImageSelectedFore, stateType);
}

template<typename InheritType>
void CheckBoxTemplate<InheritType>::SetSelectedForeStateImage(ControlStateType stateType, const std::wstring& pStrImage)
{
	this->m_imageMap.SetImage(kStateImageSelectedFore, stateType, pStrImage);
	if (this->GetFixedWidth() == DUI_LENGTH_AUTO || this->GetFixedHeight() == DUI_LENGTH_AUTO) {
		this->ArrangeAncestor();
	}
	else {
		this->Invalidate();
	}
}

typedef CheckBoxTemplate<Control> CheckBox;
typedef CheckBoxTemplate<Box> CheckBoxBox;

} // namespace ui

#endif // UI_CONTROL_CHECKBOX_H_#ifndef UI_CONTROL_CHECKBOX_H_