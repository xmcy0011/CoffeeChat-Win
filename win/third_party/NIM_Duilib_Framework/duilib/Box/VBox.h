#ifndef UI_CORE_VBOX_H_
#define UI_CORE_VBOX_H_

#pragma once

namespace ui
{

class UILIB_API VLayout : public Layout
{
public:
	VLayout();
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual CSize ArrangeChild(const std::vector<Control*>& items, UiRect rc) override;
	virtual CSize AjustSizeByChild(const std::vector<Control*>& items, CSize szAvailable) override;
};

class UILIB_API VBox : public Box
{
public:
	VBox();
};

}
#endif // UI_CORE_VBOX_H_
