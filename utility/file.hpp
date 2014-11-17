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

/**
 * @file utility/file.hpp
 * @author Mustafa Gonul
 */

#ifndef DNW_UTILITY_FILE_HPP
#define DNW_UTILITY_FILE_HPP

#include "utility/types.hpp"


namespace dnw {
  namespace utility {
    namespace file {

      /**
       * @brief Writes @a data to the file named @a filename.
       * @param filename
       * @param data
       */
      void write(String const &filename, String const &data);


      /**
       * @brief Reads the data from the file specified with @a filename
       * @param filename
       * @return Data in the file.
       */
      String read(String const &filename);
    }
  }
}


#endif // DNW_UTILITY_FILE_HPP
