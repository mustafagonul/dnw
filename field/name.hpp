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
 * @file field/name.hpp
 * @author Mustafa Gonul
 */

#ifndef DNW_FIELD_NAME_HPP
#define DNW_FIELD_NAME_HPP

#include "field/field.hpp"


namespace dnw {
  namespace field {

    /**
     * @class dnw::field::Name
     * @brief This class is for working on name field of a node.
     */
    class Name : public Field {
    public:
      /**
       * @brief Constructor
       * @param device
       */
      explicit Name(Device const &device);

    public:
      /**
       * @brief Checks if name exists in the given @a language
       * @param language
       * @return Success value
       */
      bool nameExists(String const &language) const;

      /**
       * @brief Edits name of the node in the given @a language with @a data.
       * @param language
       * @param data
       * @return Success value
       */
      bool editName(String const &language, String const &data) const;

      /**
       * @brief Returns name of the node in the given @a language.
       * @param language
       * @return Name of the node in the given @a language.
       */
      String name(String const &language) const;
    };

  }
}


#endif // DNW_FIELD_NAME_HPP
