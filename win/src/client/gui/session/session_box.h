#ifndef _SESSION_BOX_AD7CCD59_3902_431A_A394_5B3A7CDF1DF4_
#define _SESSION_BOX_AD7CCD59_3902_431A_A394_5B3A7CDF1DF4_

#include "duilib/UIlib.h"

namespace gui {
    namespace session {
        class SessionBox: public ui::VBox {
          public:
            SessionBox();
            ~SessionBox();

            void InitControl(std::string sessionId, const std::wstring& name, bool isGroup = false);

          private:
            ui::Label* lab_session_name;
        };
    }
}

#endif // _SESSION_BOX_AD7CCD59_3902_431A_A394_5B3A7CDF1DF4_