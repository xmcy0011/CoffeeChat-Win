#ifndef UI_CORE_CHILDBOX_H_
#define UI_CORE_CHILDBOX_H_

#pragma once

namespace ui
{

class UILIB_API ChildBox : public Box
{
public:
	ChildBox();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void Init() override;
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/**
	 * @brief ���� ChildBox ������ XML �ļ�
	 * @param[in] strXML XML �ļ�·��
	 * @return ��
	 */
	void SetChildLayoutXML(std::wstring strXML);

	/**
	 * @brief ��ȡ ChildBox ������ XML �ļ�
	 * @return ���� ChildBox ������ XML �ļ�
	 */
	std::wstring GetChildLayoutXML();

private:
	std::wstring m_strXMLFile;
};

} // namespace ui
#endif // UI_CORE_CHILDBOX_H_
