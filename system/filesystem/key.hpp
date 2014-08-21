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
 * @file system/filesystem/device.hpp
 * @author Mustafa Gonul
 */

#ifndef SITE_SYSTEM_FILESYSTEM_KEY_HPP
#define SITE_SYSTEM_FILESYSTEM_KEY_HPP

#include <string>
#include <vector>


namespace site {
  namespace system {
    namespace filesystem {

      /**
       * @class site::system::filesystem::Key
       * @brief This class represents filesystem keys.
       */
      class Key {
      private:
        using String  = std::string;
        using Index   = unsigned;
        using Indices = std::vector<Index>;
        using Level   = unsigned;

      public:
        /**
         * @brief Constructor
         * @param str
         *
         * In this module keys have a string representation. User can convert string to key and vice versa.
         * It the user passes an empty string to constructor, key will point the root node.
         */
        explicit Key(String const &str= "");

      public:
        /**
         * @brief Returns the depth of the key.
         * @return depth value
         */
        Index depth() const;

        /**
         * @brief Returns the node index at a specific level.
         * @param level
         * @return index
         */
        Index index(Level level) const;

        /**
         * @brief Returns the last node index.
         * @return index
         */
        Index last() const;

        /**
         * @brief Returns the string representation of the key.
         * @return String representation of the key.
         */
        String string() const;

        /**
         * @brief Pops a level from the key.
         */
        void pop();

        /**
         * @brief Pushes a node index to key.
         * @param index
         */
        void push(Index index);

        /**
         * @brief Checks if there is no index value in the key.
         * @return check value
         */
        bool empty() const;

        /**
         * @brief Checks if the keys are equal.
         * @param key
         * @return check value
         */
        bool same(Key const &key) const;

        /**
         * @brief Checks if the current key is the child key of the key given with @a key parameter.
         * @param key
         * @return check value
         */
        bool childOf(Key const &key) const;

        /**
         * @brief Checks if the current key is the parent key of the key given with @a key parameter.
         * @param key
         * @return check value
         */
        bool parentOf(Key const &key) const;

      private:
        /**
         * @brief Returns delimiter used while generation string representation of the key.
         * @return delimiter
         */
        static char delimiter();

      private:
        Indices indices; /**< Indices */
      };

    }
  }
}


#endif // SITE_SYSTEM_FILESYSTEM_KEY_HPP
