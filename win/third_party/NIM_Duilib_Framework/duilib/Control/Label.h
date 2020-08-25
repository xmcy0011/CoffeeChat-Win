#ifndef UI_CONTROL_LABEL_H_
#define UI_CONTROL_LABEL_H_

#pragma once

namespace ui
{

template<typename InheritType = Control>
class UILIB_API LabelTemplate : public InheritType
{
public:
	LabelTemplate();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual std::wstring GetText() const;
	virtual std::string GetUTF8Text() const;
	virtual void SetText(const std::wstring& strText);
	virtual void SetUTF8Text(const std::string& strText);
	virtual void SetTextId(const std::wstring& strTextId);
	virtual void SetUTF8TextId(const std::string& strTextId);
	virtual bool HasHotState();
	virtual CSize EstimateText(CSize szAvailable, bool& bReEstimateSize) override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual void PaintText(IRenderContext* pRender) override;

	/**
	 * @brief �����ı���ʽ
	 * @param[in] uStyle Ҫ���õ���ʽ
	 * @return ��
	 */
	void SetTextStyle(UINT uStyle);

	/**
	 * @brief ��ȡ�ı���ʽ
	 * @return �����ı���ʽ
	 */
	UINT GetTextStyle() const;

	/**
	 * @brief ��ȡָ��״̬�µ��ı���ɫ
	 * @param[in] stateType Ҫ��ȡ��״̬��־
	 * @return ����ָ��״̬�µ��ı���ɫ
	 */
	std::wstring GetStateTextColor(ControlStateType stateType);

	/**
	 * @brief ����ָ��״̬�µ��ı���ɫ
	 * @param[in] stateType Ҫ���õ�״̬��־
	 * @param[in] dwTextColor Ҫ���õ�״̬��ɫ�ַ�������ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor);

	/**
	 * @brief ��ȡ��ǰ������
	 * @return ���������ţ��ñ���� global.xml �б�ʶ
	 */
	std::wstring GetFont() const;

	/**
	 * @brief ���õ�ǰ����
	 * @param[in] index Ҫ���õ������ţ��ñ�ű����� global.xml �д���
	 * @return ��
	 */
	void SetFont(const std::wstring& strFontId);

	/**
	 * @brief ��ȡ���ֱ߾�
	 * @return �������ֵı߾���Ϣ
	 */
	UiRect GetTextPadding() const;

	/**
	 * @brief �������ֱ߾���Ϣ
	 * @param[in] rc �߾���Ϣ
	 * @return ��
	 */
	void SetTextPadding(UiRect rc);

	/**
	 * @brief �ж��Ƿ��ǵ���ģʽ
	 * @return ���� true ��ʾ����ģʽ������Ϊ false
	 */
	bool IsSingleLine();

	/**
	 * @brief ����Ϊ��������ģʽ
	 * @param[in] bSingleLine Ϊ true ʱΪ����ģʽ������Ϊ false
	 * @return ��
	 */
	void SetSingleLine(bool bSingleLine);

	/**
	 * @brief �Ƿ������������
	 * @return ���� true Ϊ���ƣ�false Ϊ������
	 */
	bool IsLineLimit();

	/**
	 * @brief �����������
	 * @param[in] bLineLimit ���� true Ϊ���ƣ�false Ϊ������
	 * @return ��
	 */
	void SetLineLimit(bool bLineLimit);

protected:
	std::wstring m_sFontId;
	UINT	m_uTextStyle;
	bool    m_bSingleLine;
	bool    m_bLineLimit;
	int		m_hAlign;
	int		m_vAlign;
	UiRect	m_rcTextPadding;
	std::wstring	m_sText;
	std::wstring	m_sTextId;
	StateColorMap	m_textColorMap;
};

template<typename InheritType>
LabelTemplate<InheritType>::LabelTemplate() :
	m_sFontId(),
	m_uTextStyle(DT_LEFT | DT_TOP | DT_END_ELLIPSIS | DT_NOCLIP | DT_SINGLELINE),
	m_bSingleLine(true),
	m_bLineLimit(false),
	m_hAlign(DT_LEFT),
	m_vAlign(DT_CENTER),
	m_rcTextPadding(),
	m_sText(),
	m_sTextId(),
	m_textColorMap()
{
	if (dynamic_cast<Box*>(this)) {
		this->m_cxyFixed.cx = this->m_cxyFixed.cy = DUI_LENGTH_STRETCH;
	}
	else {
		this->m_cxyFixed.cx = this->m_cxyFixed.cy = DUI_LENGTH_AUTO;
	}

	m_textColorMap[kControlStateNormal] = GlobalManager::GetDefaultTextColor();
	m_textColorMap[kControlStateDisabled] = GlobalManager::GetDefaultDisabledTextColor();
	m_textColorMap.SetControl(this);
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetText() const
{
	std::wstring strText = m_sText;
	if (strText.empty() && !m_sTextId.empty()) {
		strText = MutiLanSupport::GetInstance()->GetStringViaID(m_sTextId);
	}

	return strText;
}

template<typename InheritType>
std::string LabelTemplate<InheritType>::GetUTF8Text() const
{
	std::string strOut;
	StringHelper::UnicodeToMBCS(GetText(), strOut, CP_UTF8);
	return strOut;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetText(const std::wstring& strText)
{
	if (m_sText == strText) return;
	m_sText = strText;

	if (this->GetFixedWidth() == DUI_LENGTH_AUTO || this->GetFixedHeight() == DUI_LENGTH_AUTO) {
		this->ArrangeAncestor();
	}
	else {
		this->Invalidate();
	}
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetUTF8Text(const std::string& strText)
{
	std::wstring strOut;
	StringHelper::MBCSToUnicode(strText, strOut, CP_UTF8);
	SetText(strOut);
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextId(const std::wstring& strTextId)
{
	if (m_sTextId == strTextId) return;
	m_sTextId = strTextId;

	if (this->GetFixedWidth() == DUI_LENGTH_AUTO || this->GetFixedHeight() == DUI_LENGTH_AUTO) {
		this->ArrangeAncestor();
	}
	else {
		this->Invalidate();
	}
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetUTF8TextId(const std::string& strTextId)
{
	std::wstring strOut;
	StringHelper::MBCSToUnicode(strTextId, strOut, CP_UTF8);
	SetTextId(strOut);
}

template<typename InheritType>
bool LabelTemplate<InheritType>::HasHotState()
{
	return m_textColorMap.HasHotColor() || __super::HasHotState();
}

template<typename InheritType>
CSize LabelTemplate<InheritType>::EstimateText(CSize szAvailable, bool& bReEstimateSize)
{
	if (m_bSingleLine)
		m_uTextStyle |= DT_SINGLELINE;
	else
		m_uTextStyle &= ~DT_SINGLELINE;

	int width = this->GetFixedWidth();
	if (width < 0) {
		width = 0;
	}
	CSize fixedSize;
	if (!GetText().empty()) {
		auto pRender = this->m_pWindow->GetRenderContext();
		UiRect rect = pRender->MeasureText(GetText(), m_sFontId, m_uTextStyle, width);
		if (this->GetFixedWidth() == DUI_LENGTH_AUTO) {
			fixedSize.cx = rect.right - rect.left + m_rcTextPadding.left + m_rcTextPadding.right;
		}
		if (this->GetFixedHeight() == DUI_LENGTH_AUTO) {
			int estimateWidth = rect.right - rect.left;
			int estimateHeight = rect.bottom - rect.top;

			if (!m_bSingleLine && this->GetFixedWidth() == DUI_LENGTH_AUTO && this->GetMaxWidth() == DUI_LENGTH_STRETCH) {
				bReEstimateSize = true;
				int maxWidth = szAvailable.cx - m_rcTextPadding.left - m_rcTextPadding.right;
				if (estimateWidth > maxWidth) {
					estimateWidth = maxWidth;
					UiRect newRect = pRender->MeasureText(GetText(), m_sFontId, m_uTextStyle, estimateWidth);
					estimateHeight = newRect.bottom - newRect.top;
				}
			}
			fixedSize.cx = estimateWidth + m_rcTextPadding.left + m_rcTextPadding.right;
			fixedSize.cy = estimateHeight + m_rcTextPadding.top + m_rcTextPadding.bottom;
		}
	}

	return fixedSize;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetAttribute(const std::wstring& strName, const std::wstring& strValue)
{
	if (strName == _T("align")) {
		if (strValue.find(_T("left")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_CENTER | DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
			m_uTextStyle |= DT_LEFT;
		}
		if (strValue.find(_T("center")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_LEFT | DT_RIGHT);
			m_uTextStyle |= DT_CENTER;
		}
		if (strValue.find(_T("right")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_LEFT | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			m_uTextStyle |= DT_RIGHT;
		}
		if (strValue.find(_T("top")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_BOTTOM | DT_VCENTER);
			m_uTextStyle |= (DT_TOP | DT_SINGLELINE);
		}
		if (strValue.find(_T("vcenter")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_TOP | DT_BOTTOM);
			m_uTextStyle |= (DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (strValue.find(_T("bottom")) != std::wstring::npos) {
			m_uTextStyle &= ~(DT_TOP | DT_VCENTER | DT_VCENTER);
			m_uTextStyle |= (DT_BOTTOM | DT_SINGLELINE);
		}
	}
	else if (strName == _T("endellipsis")) {
		if (strValue == _T("true")) m_uTextStyle |= DT_END_ELLIPSIS;
		else m_uTextStyle &= ~DT_END_ELLIPSIS;
	}
	else if (strName == _T("linelimit")) SetLineLimit(strValue == _T("true"));
	else if (strName == _T("singleline")) SetSingleLine(strValue == _T("true"));
	else if (strName == _T("text")) SetText(strValue);
	else if (strName == _T("textid")) SetTextId(strValue);
	else if (strName == _T("font")) SetFont(strValue);
	else if (strName == _T("normaltextcolor")) SetStateTextColor(kControlStateNormal, strValue);
	else if (strName == _T("hottextcolor"))	SetStateTextColor(kControlStateHot, strValue);
	else if (strName == _T("pushedtextcolor"))	SetStateTextColor(kControlStatePushed, strValue);
	else if (strName == _T("disabledtextcolor"))	SetStateTextColor(kControlStateDisabled, strValue);
	else if (strName == _T("textpadding")) {
		UiRect rcTextPadding;
		LPTSTR pstr = NULL;
		rcTextPadding.left = _tcstol(strValue.c_str(), &pstr, 10);  ASSERT(pstr);
		rcTextPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		rcTextPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
		rcTextPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
		SetTextPadding(rcTextPadding);
	}
	else __super::SetAttribute(strName, strValue);
}

template<typename InheritType>
void LabelTemplate<InheritType>::PaintText(IRenderContext* pRender)
{
	if (GetText().empty()) return;
	UiRect rc = this->m_rcItem;
	rc.left += m_rcTextPadding.left;
	rc.right -= m_rcTextPadding.right;
	rc.top += m_rcTextPadding.top;
	rc.bottom -= m_rcTextPadding.bottom;

	ControlStateType stateType = this->m_uButtonState;
	if (stateType == kControlStatePushed && GetStateTextColor(kControlStatePushed).empty()) {
		stateType = kControlStateHot;
	}
	if (stateType == kControlStateHot && GetStateTextColor(kControlStateHot).empty()) {
		stateType = kControlStateNormal;
	}
	if (stateType == kControlStateDisabled && GetStateTextColor(kControlStateDisabled).empty()) {
		stateType = kControlStateNormal;
	}
	std::wstring clrColor = GetStateTextColor(stateType);
	DWORD dwClrColor = GlobalManager::GetTextColor(clrColor);

	if (m_bSingleLine)
		m_uTextStyle |= DT_SINGLELINE;
	else
		m_uTextStyle &= ~DT_SINGLELINE;

	if (this->m_animationManager.GetAnimationPlayer(kAnimationHot)) {
		if ((stateType == kControlStateNormal || stateType == kControlStateHot)
			&& !GetStateTextColor(kControlStateHot).empty()) {
			std::wstring clrColor = GetStateTextColor(kControlStateNormal);
			if (!clrColor.empty()) {
				DWORD dwClrColor = GlobalManager::GetTextColor(clrColor);
				pRender->DrawText(rc, GetText(), dwClrColor, m_sFontId, m_uTextStyle, 255, m_bLineLimit);
			}

			if (this->m_nHotAlpha > 0) {
				std::wstring clrColor = GetStateTextColor(kControlStateHot);
				if (!clrColor.empty()) {
					DWORD dwClrColor = GlobalManager::GetTextColor(clrColor);
					pRender->DrawText(rc, GetText(), dwClrColor, m_sFontId, m_uTextStyle, (BYTE)this->m_nHotAlpha, m_bLineLimit);
				}
			}

			return;
		}
	}

	pRender->DrawText(rc, GetText(), dwClrColor, m_sFontId, m_uTextStyle, 255, m_bLineLimit);
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextStyle(UINT uStyle)
{
	m_uTextStyle = uStyle;
	this->Invalidate();
}

template<typename InheritType>
UINT LabelTemplate<InheritType>::GetTextStyle() const
{
	return m_uTextStyle;
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetStateTextColor(ControlStateType stateType)
{
	return m_textColorMap[stateType];
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetStateTextColor(ControlStateType stateType, const std::wstring& dwTextColor)
{
	if (stateType == kControlStateHot) {
		this->m_animationManager.SetFadeHot(true);
	}
	m_textColorMap[stateType] = dwTextColor;
	this->Invalidate();
}

template<typename InheritType>
std::wstring LabelTemplate<InheritType>::GetFont() const
{
	return m_sFontId;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetFont(const std::wstring& strFontId)
{
	m_sFontId = strFontId;
	this->Invalidate();
}

template<typename InheritType>
UiRect LabelTemplate<InheritType>::GetTextPadding() const
{
	return m_rcTextPadding;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetTextPadding(UiRect rc)
{
	DpiManager::GetInstance()->ScaleRect(rc);
	m_rcTextPadding = rc;
	if (this->GetFixedWidth() == DUI_LENGTH_AUTO || this->GetFixedHeight() == DUI_LENGTH_AUTO) {
		this->ArrangeAncestor();
	}
	else {
		this->Invalidate();
	}
}

template<typename InheritType>
bool LabelTemplate<InheritType>::IsSingleLine()
{
	return m_bSingleLine;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetSingleLine(bool bSingleLine)
{
	if (m_bSingleLine == bSingleLine) return;

	m_bSingleLine = bSingleLine;
	this->Invalidate();
}

template<typename InheritType>
bool LabelTemplate<InheritType>::IsLineLimit()
{
	return m_bLineLimit;
}

template<typename InheritType>
void LabelTemplate<InheritType>::SetLineLimit(bool bLineLimit)
{
	if (m_bLineLimit == bLineLimit) return;

	m_bLineLimit = bLineLimit;
	this->Invalidate();
}

typedef LabelTemplate<Control> Label;
typedef LabelTemplate<Box> LabelBox;

}

#endif // UI_CONTROL_LABEL_H_