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
 * @file field/code.hpp
 * @author Mustafa Gonul
 */

#ifndef SITE_FIELD_CODE_HPP
#define SITE_FIELD_CODE_HPP

#include "field/field.hpp"


namespace site {
  namespace field {

    /**
     * @class site::field::Code
     * @brief This class is for working on code field of a node.
     */
    class Code : public Field {
    public:
      /**
       * @brief Constructor
       * @param device
       */
      explicit Code(Device const &device);

    public:
      /**
       * @brief Returns file count in the code field.
       * @return Code count
       */
      Index codeCount() const;

      /**
       * @brief Returns file name in the code field with the given @a index.
       * @param index
       * @return Code file name
       */
      String codeName(Index index) const;

      /**
       * @brief Returns internal data of the code file given with @a name.
       * @param name
       * @return Code data
       */
      String code(String const &name) const;

      /**
       * @brief Edits code file given in @a name with @a data.
       * @param name
       * @param data
       * @return Success value
       */
      bool editCode(String const &name, String const &data) const;

      /**
       * @brief Removes code file in the field given with @a name.
       * @param name
       * @return Success value
       */
      bool removeCode(String const &name) const;

    };

  }
}

#endif // SITE_FIELD_CODE_HPP
