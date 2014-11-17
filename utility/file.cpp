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


namespace dnw {
namespace utility {
namespace file {


String read(String const &filename)
{
  std::ifstream file(filename);
  String result;

  char ch;
  while (file.get(ch))
    result += ch;

  return result;
}

void write(String const &filename, String const &str)
{
  std::ofstream file(filename);
  for (auto ch : str)
    file.put(ch);
}


} // file
} // utility
} // dnw

