#ifndef DNW_DIALOG_PASSWORD_HPP
#define DNW_DIALOG_PASSWORD_HPP

#include "authentication/fwd.hpp"


namespace dnw {
  namespace dialog {

    bool password(authentication::Session &session); // TODO mustafa: more convenient names
    bool checkPassword(); // TODO mustafa: more convenient names
    bool newPassword(); // TODO mustafa: more convenient names

  }
}


#endif // DNW_DIALOG_PASSWORD_HPP
