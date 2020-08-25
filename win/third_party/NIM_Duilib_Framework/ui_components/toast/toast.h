#pragma once

namespace nim_comp {
/** @class Toast
 * @brief �ṩһ�����׵���ʾ���壬�൱��MessageBox�ļ򻯰�
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2016/8/24
 */
class Toast : public ui::WindowImplBase
{
public:
	/**
	 * ����Ļ�м���ʾһ����ʾ��
	 * @param[in] content ��ʾ����
	 * @param[in] duration ����ʱ��(����),0����һֱ��ʾ
	 * @param[in] parent �����ھ��������ṩ�Ļ�toast����ʾ�ڸ����ڵ�����
	 * @return void �޷���ֵ
	 */
	static void ShowToast(const std::wstring &content, int duration = 0, HWND parent = NULL);
public:
	Toast(){};
	~Toast(){};

	//�����麯��
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual std::wstring GetWindowId() const /*override*/;
	virtual UINT GetClassStyle() const override;

	/**
	 * ���ڳ�ʼ������
	 * @return void	�޷���ֵ
	 */
	virtual void InitWindow() override;

	/**
	 * ���ز�����ײ㴰����Ϣ
	 * @param[in] uMsg ��Ϣ����
	 * @param[in] wParam ���Ӳ���
	 * @param[in] lParam ���Ӳ���
	 * @return LRESULT ������
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

	/**
	 * ���ô������ʾʱ��
	 * @param[in] duration ����ʱ�䣬��λ����
	 * @return void	�޷���ֵ
	 */
	void SetDuration(int duration);

private:
	/**
	 * �������пؼ�������Ϣ
	 * @param[in] msg ��Ϣ�������Ϣ
	 * @return bool true �������ݿؼ���Ϣ��false ֹͣ���ݿؼ���Ϣ
	 */
	bool OnClicked(ui::EventArgs* msg);

	/**
	 * ������ʾ����
	 * @param[in] str ��ʾ����
	 * @return void	�޷���ֵ
	 */
	void SetContent(const std::wstring &str);

	public:
		static const LPCTSTR kClassName;
	private:
		ui::RichEdit	*content_;
		ui::Button		*close_button_;
	};
}