#pragma once

/** @class CustomLayout
  * @brief ���ڻỰ����������SessionBox���Զ���TabBox��Ϊ������������ʾ����ͼ��Ԥ��ͼ����д�˶��ӿؼ��Ĳ����߼�
  * @copyright (c) 2016, NetEase Inc. All rights reserved
  * @author Redrain
  * @date 2019/3/20
  */
class CustomLayout : public ui::Layout
{
public:
	virtual ui::CSize ArrangeChild(const std::vector<ui::Control*>& m_items, ui::UiRect rc) override;
	ui::CSize SetCustomPos(ui::Control* pControl, ui::UiRect containerRect);
};