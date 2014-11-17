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

#include "authentication/session.hpp"
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/HashFunction>


namespace dnw {
namespace authentication {


Wt::Auth::AuthService g_authService;
Wt::Auth::PasswordService g_passwordService(g_authService);


Session::Session()
  : m_users()
  , m_login()
  , m_model(g_authService, m_users)
{
  m_model.addPasswordAuth(&g_passwordService);
}

Session::~Session()
{
}

Session::AbstractUserDatabase &Session::users()
{
  return m_users;
}

Session::Login &Session::login()
{
  return m_login;
}

Session::AuthModel &Session::authModel()
{
  return m_model;
}

void Session::configureAuth()
{
  // myAuthService.setAuthTokensEnabled(true, "logincookie");
  // myAuthService.setEmailVerificationEnabled(true);
  // myAuthService.setEmailVerificationRequired(true);

  Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
  verifier->addHashFunction(new Wt::Auth::MD5HashFunction());
  g_passwordService.setVerifier(verifier);

  // myPasswordService.setAttemptThrottlingEnabled(true);
  // myPasswordService.setStrengthValidator(new Wt::Auth::PasswordStrengthValidator());
}

Session::AuthService const &Session::auth()
{
  return g_authService;
}


} // authentication
} // dnw
