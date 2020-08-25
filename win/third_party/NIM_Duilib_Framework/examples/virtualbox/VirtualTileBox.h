#pragma once

typedef std::function<void(int nStartIndex, int nEndIndex)> DataChangedNotify;
typedef std::function<void()> CountChangedNotify;

class UILIB_API VirtualTileInterface: public nbase::SupportWeakCallback
{
public:
	VirtualTileInterface();
	/**
	* @brief ����һ������
	* @return ���ش����������ָ��
	*/
	virtual ui::Control* CreateElement() = 0;

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(ui::Control *control, int index) = 0;

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount() = 0;

	void RegNotifys(const DataChangedNotify& dcNotify, const CountChangedNotify& ccNotify);

protected:
	void EmitDataChanged(int nStartIndex, int nEndIndex);
	void EmitCountChanged();

private:
	DataChangedNotify m_DataChangedNotify;
	CountChangedNotify m_CountChangedNotify;
};

class UILIB_API VirtualTileLayout : public ui::TileLayout
{
public:
	VirtualTileLayout();
	virtual ui::CSize ArrangeChild(const std::vector<ui::Control*>& items, ui::UiRect rc) override;
	virtual ui::CSize AjustSizeByChild(const std::vector<ui::Control*>& items, ui::CSize szAvailable) override;
	virtual bool SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;
	virtual int GetElementsHeight(int nCount);
	virtual void LazyArrangeChild();
	virtual int AjustMaxItem();

private:
	bool m_bAutoCalcColumn;
};

class UILIB_API VirtualTileBox : public ui::ListBox
{
	friend class VirtualTileLayout;
public:
	VirtualTileBox(ui::Layout* pLayout = new VirtualTileLayout);

	/**
	* @brief �������ݴ������
	* @param[in] pProvider ��������Ҫ��д VirtualListInterface �Ľӿ�����Ϊ���ݴ������
	* @return ��
	*/
	virtual void SetDataProvider(VirtualTileInterface *pProvider);

	virtual VirtualTileInterface* GetDataProvider();

	/**
	* @brief ˢ���б�
	* @return ��
	*/
	virtual void Refresh();

	/**
	* @brief ɾ����������
	* @return ��
	*/
	virtual void RemoveAll() override;

	/**
	* @brief �����Ƿ�ǿ�����²���
	* @param[in] bForce ����Ϊ true Ϊǿ�ƣ�����Ϊ��ǿ��
	* @return ��
	*/
	void SetForceArrange(bool bForce);

	/**
	* @brief ��ȡ��ǰ���пɼ��ؼ�������
	* @param[out] collection �����б�
	* @return ��
	*/
	void GetDisplayCollection(std::vector<int>& collection);

	/**
	* @brief �ÿؼ��ڿɼ���Χ��
	* @param[in] iIndex �ؼ�����
	* @param[in] bToTop �Ƿ������Ϸ�
	* @return ��
	*/
	void EnsureVisible(int iIndex, bool bToTop = false);

protected:
	/// ��д����ӿڣ��ṩ���Ի�����
	virtual void SetScrollPos(ui::CSize szPos) override;
	virtual void HandleMessage(ui::EventArgs& event) override;
	virtual void SetPos(ui::UiRect rc) override;

	/**
	* @brief ���²�������
	* @param[in] bForce �Ƿ�ǿ�����²���
	* @return ��
	*/
	void ReArrangeChild(bool bForce);

	/**
	* @brief ���̰���֪ͨ
	* @param[in] ch ����
	* @return ��
	*/
	virtual void OnKeyDown(TCHAR ch) {}

	/**
	* @brief ���̵���֪ͨ
	* @param[in] ch ����
	* @return ��
	*/
	virtual void OnKeyUp(TCHAR ch) {}

private:
	enum ScrollDirection
	{
		kScrollUp = -1,
		kScrollDown = 1
	};

	/**
	* @brief ����һ������
	* @return ���ش����������ָ��
	*/
	Control* CreateElement();

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	void FillElement(Control *pControl, int iIndex);

	/**
	* @brief ��ȡԪ������
	* @return ����Ԫ����ָ��
	*/
	int GetElementCount();

	/**
	* @brief �õ�n��Ԫ�ض�Ӧ�ĸ߶Ⱥͣ�
	* @param[in] nCount Ҫ�õ�����Ԫ�صĸ߶ȣ�-1��ʾȫ��Ԫ��
	* @return ����ָ������Ԫ�صĸ߶Ⱥ�
	*/
	int CalcElementsHeight(int nCount);

	/**
	* @brief �õ��ɼ���Χ�ڵ�һ��Ԫ�ص�ǰһ��Ԫ������
	* @param[out] bottom ������һ��Ԫ�ص� bottom ֵ
	* @return ������һ��Ԫ�ص�����
	*/
	int GetTopElementIndex(int &bottom);

	/**
	* @brief �ж�ĳ��Ԫ���Ƿ��ڿɼ���Χ��
	* @param[in] iIndex Ԫ������
	* @return ���� true ��ʾ�ɼ�������Ϊ���ɼ�
	*/
	bool IsElementDisplay(int iIndex);

	/**
	* @brief �ж��Ƿ�Ҫ���²���
	* @param[out] direction ���Ϲ����������¹���
	* @return true Ϊ��Ҫ���²��֣�����Ϊ false
	*/
	bool NeedReArrange(ScrollDirection &direction);

	VirtualTileLayout* GetTileLayout();

	int GetRealElementHeight();

	int GetColumns();

	void LazyArrangeChild();

	void OnModelDataChanged(int nStartIndex, int nEndIndex);
	
	void OnModelCountChanged();

	int ElementIndexToItemIndex(int nElementIndex);

	int ItemIndexToElementIndex(int nItemIndex);

private:
	VirtualTileInterface *m_pDataProvider;
	int m_nMaxItemCount;	// �б���ʵ�ؼ���������  
	int m_nOldYScrollPos;
	bool m_bArrangedOnce;
	bool m_bForceArrange;	// ǿ�Ʋ��ֱ��
};
