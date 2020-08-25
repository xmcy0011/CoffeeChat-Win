#ifndef UI_UTILS_MULTILANGSUPPORT_H_
#define UI_UTILS_MULTILANGSUPPORT_H_

#pragma once

namespace ui 
{

class UILIB_API MutiLanSupport
{
public:
	static MutiLanSupport* GetInstance();

	/**
	 * @brief ����ID��ȡָ�����Ե��ַ���
	 * @param[in] id ָ���ַ��� ID
	 * @return ���� ID ��Ӧ�������ַ���
	 */
	std::wstring GetStringViaID(const std::wstring& id);

	/**
	 * @brief ������������ӳ���
	 * @param[in] strFilePath �����ļ�·��
	 * @return ���� true ��ʾ�ɹ������� false ��ʾʧ��
	 */
	bool LoadStringTable(const std::wstring& strFilePath);

	/**
	 * @brief ���ڴ��м�����������ӳ���
	 * @param[in] hGlobal Ҫ���ص�����ӳ����ڴ��׵�ַ
	 * @return ���� true ��ʾ�ɹ������� false ��ʾʧ��
	 */
	bool LoadStringTable(const HGLOBAL& hGlobal);

private:
	MutiLanSupport() {};
	~MutiLanSupport() {};
	MutiLanSupport(const MutiLanSupport&) = delete;
	MutiLanSupport& operator = (const MutiLanSupport&) = delete;

	/**
	 * @brief ��������
	 * @return ��
	 */
	void ClearAll();

	/**
	 * @brief ��������ӳ�������
	 * @param[in] list ��ȡ������ӳ��������б�
	 * @return �ɹ����� true�����򷵻� false
	 */
	bool AnalyzeStringTable(const std::vector<std::wstring>& list);

private: 
	std::map<std::wstring, std::wstring>  m_stringTable;
};

}
#endif //UI_UTILS_MULTILANGSUPPORT_H_
