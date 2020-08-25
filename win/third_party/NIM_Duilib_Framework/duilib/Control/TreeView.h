#ifndef UI_CONTROL_TREEVIEW_H_
#define UI_CONTROL_TREEVIEW_H_

#pragma once

namespace ui
{

#define ROOT_NODE_DEPTH  -1

class TreeView;
class UILIB_API TreeNode : public ListContainerElement
{
public:
	TreeNode();
	TreeNode(const TreeNode& r) = delete;
	TreeNode& operator=(const TreeNode& r) = delete;

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual bool IsVisible() const override;
	virtual void SetInternVisible(bool bVisible) override;
	virtual void SetWindow(Window* pManager, Box* pParent, bool bInit = true) override;

	/**
	 * @brief ������ʱ����
	 * @param[in] param ��Ϣ��
	 * @return ʼ�շ��� true
	 */
	virtual bool OnClickItem(EventArgs* param);

	/**
	 * @brief �������������������б�����
	 * @param[in] pTreeView ����ָ��
	 * @return ��
	 */
	void SetTreeView(TreeView* pTreeView);

	/**
	 * @brief ��ȡ���ڵ�ָ��
	 * @return ���ظ��ڵ�ָ��
	 */
	TreeNode* GetParentNode();

	/**
	 * @brief ���ø��ڵ�
	 * @param[in] pParentTreeNode ���ڵ�ָ��
	 * @return ��
	 */
	void SetParentNode(TreeNode* pParentTreeNode);

	/**
	 * @brief ����ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool AddChildNode(TreeNode* pTreeNode);

	/**
	 * @brief ��ָ��λ������ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @param[in] iIndex Ҫ�����ĸ�λ��֮��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool AddChildNodeAt(TreeNode* pTreeNode, std::size_t iIndex);

	/**
	 * @brief ��ָ��λ���Ƴ�һ���ӽڵ�
	 * @param[in] index Ҫ�Ƴ����ӽڵ�����
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveChildNodeAt(std::size_t index);

	/**
	 * @brief �����ӽڵ�ָ���Ƴ�һ���ӽڵ�
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveChildNode(TreeNode* pTreeNode);

	/**
	 * @brief �Ƴ������ӽڵ�
	 * @return ��
	 */
	void RemoveAllChildNode();

	/**
	 * @brief �ݹ��ȡ�����ӽڵ����
	 * @return ���������ӽڵ����
	 */
	int GetDescendantNodeCount();

	/**
	 * @brief ��ȡ��һ���ӽڵ����
	 * @return �����ӽڵ����
	 */
	std::size_t GetChildNodeCount();

	/**
	 * @brief ��ȡһ���ӽڵ�ָ��
	 * @param[in] iIndex Ҫ��ȡ���ӽڵ�����
	 * @return �����ӽڵ�ָ��
	 */
	TreeNode* GetChildNode(std::size_t iIndex);

	/**
	 * @brief �����ӽڵ�ָ���ȡ�ӽڵ�λ������
	 * @param[in] pTreeNode �ӽڵ�ָ��
	 * @return ����λ������
	 */
	int	GetChildNodeIndex(TreeNode* pTreeNode);

	/**
	 * @brief �ж��Ƿ�չ��״̬
	 * @return ���� true Ϊչ��״̬������Ϊ false
	 */
	bool IsExpand() const; 

	/**
	 * @brief �����Ƿ�չ����ʾ�ӽڵ�
	 * @param[in] bExpand Ϊ true ʱչ����Ϊ false �ǲ�չ��
	 * @return ��
	 */
	void SetExpand(bool bExpand);

	/**
	 * @brief ��ȡ����㼶
	 * @return ���ص�ǰ�㼶
	 */
	int GetDepth();

private:
	/**
	 * @brief ɾ������
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool RemoveSelf();

private:
	int m_iDepth;
	bool m_bExpand;
	TreeView *m_pTreeView;
	TreeNode *m_pParentTreeNode;
	std::vector<TreeNode*> m_aTreeNodes;
};

class UILIB_API TreeView : public ListBox
{
public:
	TreeView(void);

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void SetAttribute(const std::wstring& strName, const std::wstring& strValue) override;

	/**
	 * @brief ��ȡ���ڵ�
	 * @return ���ظ��ڵ�ָ��
	 */
	TreeNode* GetRootNode()	{ return m_rootNode.get(); }

	/**
	 * @brief ��ȡ�ӽڵ�����ֵ
	 * @return �����ӽڵ�����ֵ
	 */
	int GetIndent() { return m_iIndent;	}

	/**
	 * @brief �����ӽڵ�����ֵ
	 * @param[in] indent Ҫ���õ�����ֵ
	 * @return ��
	 */
	void SetIndent(int indent) { m_iIndent = indent; }

private:
	//���º�������˽�л���������ֹʹ�ã�Ӧ��ʹ��TreeNode�е���غ���
	bool Add(Control* pControl) override;
	bool AddAt(Control* pControl, std::size_t iIndex) override;
	bool Remove(Control* pControl) override;
	bool RemoveAt(std::size_t iIndex) override;
	void RemoveAll() override;

	virtual void SetWindow(Window* pManager, Box* pParent, bool bInit = true) override;

private:
	int m_iIndent;
	std::unique_ptr<TreeNode> m_rootNode;
};

}

#endif // UI_CONTROL_TREEVIEW_H_
