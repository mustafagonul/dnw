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

#include "authentication/userdatabase.hpp"
#include "admin/password.hpp"
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/Identity>


namespace dnw {
namespace authentication {


UserDatabase::UserDatabase()
  : BaseClass()
{
}

UserDatabase::~UserDatabase()
{
}

UserDatabase::User UserDatabase::findWithId(String const &id) const
{
  if (id == "admin")
    return User("admin", *this);

  return User();
}

UserDatabase::User UserDatabase::findWithIdentity(String const &provider, WString const &identity) const
{
  if (provider == Wt::Auth::Identity::LoginName &&
      identity == "admin")
    return User("admin", *this);

  return User();
}

UserDatabase::WString UserDatabase::identity(User const &user, String const &provider) const
{
  if (provider == Wt::Auth::Identity::LoginName)
    return user.id();

  return "";
}

void UserDatabase::addIdentity(User const &user, String const &provider, WString const &id)
{
}

void UserDatabase::removeIdentity(User const &user, String const &provider)
{
}

void UserDatabase::setPassword(User const &user, PasswordHash const &password)
{
}

UserDatabase::PasswordHash UserDatabase::password(User const &user) const
{
  if (user.isValid() == false)
    return PasswordHash();

  using HashFunction = Wt::Auth::MD5HashFunction;

  HashFunction hashFunction;

  return PasswordHash(hashFunction.name(),
                      admin::salt(),
                      admin::hash());
}


} // authentication
} // dnw
