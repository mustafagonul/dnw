/*
 * Copyright (C) 2014 Mustafa Gönül
 *
 * dnw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dnw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
**/

#ifndef DNW_AUTHENTICATION_USERDATABASE_HPP
#define DNW_AUTHENTICATION_USERDATABASE_HPP

#include "utility/common.hpp"
#include <Wt/Auth/AbstractUserDatabase>
#include <Wt/Auth/User>
#include <Wt/Auth/PasswordHash>


namespace dnw {
  namespace authentication {

    class UserDatabase : public Wt::Auth::AbstractUserDatabase {
    private:
      using BaseClass = Wt::Auth::AbstractUserDatabase;
      using WString = Wt::WString;
      using User = Wt::Auth::User;
      using PasswordHash = Wt::Auth::PasswordHash;

    public:
      UserDatabase();
      virtual ~UserDatabase();

    public:
      virtual User findWithId(String const &id) const;
      virtual User findWithIdentity(String const &provider, WString const &identity) const;

      virtual WString identity(User const &user, String const &provider) const;
      virtual void addIdentity(User const &user, String const &provider, WString const &id);
      virtual void removeIdentity(User const &user, String const &provider);

      virtual void setPassword(User const &user, PasswordHash const &password);
      virtual PasswordHash password(User const &user) const;
    };

  }
}


#endif // DNW_AUTHENTICATION_USERDATABASE_HPP
