#pragma once

#include "VirtualTileBox.h"
#include <map>

struct DownloadTask
{
	int nId;
	std::wstring sName;
};

class Provider : public VirtualTileInterface
{
public:
	Provider();
	~Provider();

	virtual ui::Control* CreateElement() override;

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(ui::Control *control, int index) override;

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount() override;

public:
	void SetTotal(int nTotal);
	void RemoveTask(int nIndex);
	void ChangeTaskName(int nIndex, const std::wstring& sName);

private:
	int m_nTotal;
	std::vector<DownloadTask> m_vTasks;
	nbase::NLock  lock_;
};

