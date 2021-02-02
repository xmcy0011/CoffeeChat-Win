/** @file config.h
  * @brief config
  * @author fei.xu
  * @date 2021/02/01
  */

#ifndef _CONFIG_5653A3FF_A344_418A_AFFF_BB06A2431FC4_
#define _CONFIG_5653A3FF_A344_418A_AFFF_BB06A2431FC4_

#include "cim/cim.h"

struct StorageInfo {
    std::string userName;
    std::string pwdMd5;
};

/** @class Config
  * @brief ≈‰÷√
  * @author fei.xu
  * @date 2021/2/2
  */
class Config: public StorageInfo {
  public:
    static Config* getInstace();

    void load();
    void save();

  private:
    Config() = default;
    ~Config() = default;
};


#endif//_CONFIG_5653A3FF_A344_418A_AFFF_BB06A2431FC4_