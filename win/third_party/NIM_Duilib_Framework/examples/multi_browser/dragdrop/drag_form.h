#pragma once

/** @class DragForm
  * @brief ģ��ϵͳ��ק���ܵİ�͸�����壬��Ϊʹ���˵ͼ����̹�������һЩ��ȫ���������
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class BitmapControl;
class DragForm : public ui::WindowImplBase
{
public:
	/**
	* �ͼ����̹��ӵĻص�����
	* @param[in] nCode ������
	* @param[in] wParam ���Ӳ���
	* @param[in] lParam ���Ӳ���
	* @return LRESULT	�������
	*/
	static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	/**
	* �����Զ�����ק����
	* @param[in] bitmap ��קЧ��λͼ
	* @param[in] pt_offset ��קͼ�����������ƫ��
	* @return void	�޷���ֵ
	*/
	static void CreateCustomDragImage(HBITMAP bitmap, POINT pt_offset);

	/**
	* �ر��Զ�����ק����
	* @return void	�޷���ֵ
	*/
	static void CloseCustomDragImage();

public:	
	// �����麯��
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;
	virtual UINT GetClassStyle() const override;

	/**
	* ���ݿؼ����������Զ���ؼ�
	* @param[in] pstrClass �ؼ�����
	* @return Control* �����Ŀؼ���ָ��
	*/
	virtual ui::Control* CreateControl(const std::wstring& pstrClass) override;

	/**
	* ���ڳ�ʼ������
	* @return void	�޷���ֵ
	*/
	virtual void InitWindow() override;

private:
	DragForm();
	~DragForm(){};

	/**
	* ����һ����קЧ���Ĵ���
	* @param[in] bitmap ��קЧ��λͼ����
	* @param[in] pt_offset ��קͼ�����������ƫ��
	* @return void	�޷���ֵ
	*/
	static DragForm* CreateDragForm(HBITMAP bitmap, POINT pt_offset);

	/**
	* ������קЧ����λͼ
	* @param[in] bitmap ��קЧ��λͼ����
	* @return void	�޷���ֵ
	*/
	void SetDragImage(HBITMAP bitmap);
public:
	static const LPCTSTR kClassName;

private:
	static HHOOK	s_mouse_hook;
	static DragForm *s_drag_form;
	static POINT	s_point_offset;
	BitmapControl	*bitmap_control_;
};