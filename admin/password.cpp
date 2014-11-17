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

#include "admin/password.hpp"
#include "utility/file.hpp"
#include <boost/filesystem.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <Wt/Auth/HashFunction>


namespace fs = boost::filesystem;
namespace bu = boost::uuids;


namespace dnw {
namespace admin {


inline static std::string directory() { return "user"; }


String md5(String const &salt, String const &password)
{
  return Wt::Auth::MD5HashFunction().compute(password, salt);
}

String generateSalt()
{
  bu::random_generator gen;
  bu::uuid id = gen();

  return bu::to_string(id);

  //return boost::lexical_cast<String>(id);
}

void setPassword(String const &pass)
{
  fs::path saltPath = fs::current_path();
  saltPath /= directory();
  saltPath /= "salt";

  fs::path hashPath = fs::current_path();
  hashPath /= directory();
  hashPath /= "hash";

  auto salt = generateSalt();
  auto hash = md5(salt, pass);

  fs::create_directories(fs::current_path() / directory());
  utility::file::write(saltPath.string(), salt);
  utility::file::write(hashPath.string(), hash);
}

bool checkPassword(String const &pass)
{
  fs::path saltPath = fs::current_path();
  saltPath /= directory();
  saltPath /= "salt";

  fs::path hashPath = fs::current_path();
  hashPath /= directory();
  hashPath /= "hash";

  auto hashInFile = utility::file::read(hashPath.string());
  auto salt = utility::file::read(saltPath.string());
  auto hash = md5(salt, pass);

  return hash == hashInFile;
}

bool passwordExists()
{
  fs::path saltPath = fs::current_path();
  saltPath /= directory();
  saltPath /= "salt";

  fs::path hashPath = fs::current_path();
  hashPath /= directory();
  hashPath /= "hash";

  return fs::exists(saltPath) &&
         fs::is_regular_file(saltPath) &&
         fs::exists(hashPath) &&
         fs::is_regular_file(hashPath);
}

String hash()
{
  fs::path hashPath = fs::current_path();
  hashPath /= directory();
  hashPath /= "hash";

  if (fs::exists(hashPath) == false)
    return "";
  if (fs::is_regular_file(hashPath) == false)
    return "";

  return utility::file::read(hashPath.string());
}

String salt()
{
  fs::path saltPath = fs::current_path();
  saltPath /= directory();
  saltPath /= "salt";

  if (fs::exists(saltPath) == false)
    return "";
  if (fs::is_regular_file(saltPath) == false)
    return "";

  return utility::file::read(saltPath.string());
}



} // admin
} // dnw
