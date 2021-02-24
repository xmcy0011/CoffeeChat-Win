#include "stdafx.h"
#include "session_box.h"

namespace gui {
    namespace session {
        SessionBox::SessionBox() {
        }
        SessionBox::~SessionBox() {
        }
        void SessionBox::InitControl(std::string sessionId, const std::wstring& name, bool isGroup) {
            lab_session_name = static_cast<ui::Label*>(FindSubControl(L"lab_session_name"));
            assert(lab_session_name);

            lab_session_name->SetText(name);
        }
    }
}