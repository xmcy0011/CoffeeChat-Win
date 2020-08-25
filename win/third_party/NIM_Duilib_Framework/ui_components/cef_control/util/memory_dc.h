/** @file memory_dc.h
 * @brief �ڴ�dc�࣬ά��HBITMAP��HDC���󣬷�����ٵĴ���λͼ����
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @author Redrain
 * @date 2016/7/19
 */
#pragma once

class MemoryDC
{
public:
	MemoryDC();
	~MemoryDC();

	// ��ʼ���ڴ�dc���ݣ�����������Ӧ��λͼ����
	// ���pBits������Ϊ�գ�����pBits�������������λͼ
	// �˺������Է������ã����Զ�ɾ��ԭ����λͼ����
	bool Init(HDC src_dc, int width, int height, const LPVOID pBits = NULL);

	// ɾ��λͼ���󲢳�ʼ������
	void DeleteDC();

	// �ж��ڴ�dc�Ƿ����ʹ��
	bool IsValid();

	HDC GetDC();
	HBITMAP GetBitmap();

	// ��ȡ�ڴ�λͼ����ָ�룬���������λͼ
	BYTE* GetBits();
	// ��ȡ�ڴ�λͼ�Ŀ��
	int	GetWidth();
	// ��ȡ�ڴ�λͼ�ĸ߶�
	int GetHeight();

private:
	bool CreateMemoryDC(HDC src_dc, int width, int height, void** pBits);

private:
	HDC		mem_dc_;
	HBITMAP	bitmap_;
	HBITMAP	old_bitmap_;
	BITMAP	bitmap_info_;

	SIZE	bitmap_size_;
	bool	valid_;
};