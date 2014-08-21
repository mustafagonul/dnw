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

#include "utility/file.hpp"
#include <fstream>


namespace site {
namespace utility {
namespace file {


std::string read(std::string const &filename)
{
  std::ifstream file(filename);
  std::string result;

  char ch;
  while (file.get(ch))
    result += ch;

  return result;
}

void write(std::string const &filename, std::string const &str)
{
  std::ofstream file(filename);
  file << str;
}


} // file
} // utility
} // site

