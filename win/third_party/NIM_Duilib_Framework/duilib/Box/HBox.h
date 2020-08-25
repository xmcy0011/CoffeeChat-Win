#ifndef UI_CORE_HBOX_H_
#define UI_CORE_HBOX_H_

#pragma once

namespace ui
{

class UILIB_API HLayout : public Layout
{
public:
	HLayout();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual CSize ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;
	virtual CSize AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable) override;
};

class UILIB_API HBox : public Box
{
public:
	HBox();
};

}
#endif // UI_CORE_HBOX_H_
