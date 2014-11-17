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

#ifndef DNW_AUTHENTICATION_SESSION_HPP
#define DNW_AUTHENTICATION_SESSION_HPP

#include "authentication/userdatabase.hpp"
#include <Wt/Auth/Login>
#include <Wt/Auth/AuthModel>


namespace dnw {
  namespace authentication {

    class Session {
    private:
      using AbstractUserDatabase = Wt::Auth::AbstractUserDatabase;
      using AuthService = Wt::Auth::AuthService;
      using AuthModel = Wt::Auth::AuthModel;
      using Login = Wt::Auth::Login;

    public:
      Session();
      ~Session();

      // Deleted functions
      Session(Session &&) = delete;
      Session(Session const &) = delete;
      void operator=(Session &&) = delete;
      void operator=(Session const &) = delete;

    public:
      AbstractUserDatabase &users();
      Login &login();
      AuthModel &authModel();

    public:
      static void configureAuth();
      static AuthService const &auth();

    private:
      UserDatabase m_users;
      Login m_login;
      AuthModel m_model;
    };

  }
}


#endif // DNW_AUTHENTICATION_SESSION_HPP
