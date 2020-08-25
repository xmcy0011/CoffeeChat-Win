#ifndef UI_CORE_TILEBOX_H_
#define UI_CORE_TILEBOX_H_

#pragma once

namespace ui
{

class UILIB_API TileLayout : public Layout
{
public:
	TileLayout();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual CSize ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;
	virtual CSize AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable) override;
	virtual bool SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/**
	 * @brief ��ȡ�����С
	 * @return ���������С
	 */
	CSize GetItemSize() const;

	/**
	 * @brief ���������С
	 * @param[in] szItem �����С����
	 * @return ��
	 */
	void SetItemSize(CSize szItem);

	/**
	 * @brief ��ȡ������
	 * @return ����������
	 */
	int GetColumns() const;

	/**
	 * @brief ������ʾ��������
	 * @param[in] nCols Ҫ������ʾ���е���ֵ
	 * @return ��
	 */
	void SetColumns(int nCols);

protected:
	int m_nColumns;
	CSize m_szItem;
};

class UILIB_API TileBox : public Box
{
public:
	TileBox();
};

}
#endif // UI_CORE_TILEBOX_H_
