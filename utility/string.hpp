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
 * @file utility/string.hpp
 * @author Mustafa Gonul
 */

#ifndef SITE_UTILITY_STRING_HPP
#define SITE_UTILITY_STRING_HPP

#include <vector>
#include <string>


namespace site {
  namespace utility {
    namespace string {

      using String  = std::string;
      using Strings = std::vector<std::string>;

      /**
       * @brief Splits @a str with @a delimiter into @a result.
       * @param str
       * @param delimiter
       * @param result
       */
      void split(String const &str, char delimiter, Strings &result);

      /**
       * @brief Splits @a str @a delimiter into @a result.
       * @param str
       * @param delimiter
       * @param result
       */
      void split(String const &str, String const &delimiter, Strings &result);

      /**
       * @brief Splits @a str with newline character into @a result.
       * @param str
       * @param result
       */
      void split(String const &str, Strings &result);

      /**
       * @brief Merges @a items with @a delimiter into @result
       * @param items
       * @param delimiter
       * @param result
       */
      void merge(Strings const &items, char delimiter, String &result);

      /**
       * @brief Replaces @a from strings to @a to strings in the @a str.
       * @param from
       * @param to
       * @param str
       */
      void replace(String const &from, String const &to, String &str);

    }
  }
}


#endif // SITE_UTILITY_STRING_HPP
