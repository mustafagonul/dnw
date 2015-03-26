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
 * @file field/text.hpp
 * @author Mustafa Gönül
 */

#ifndef DNW_FIELD_TEXT_HPP
#define DNW_FIELD_TEXT_HPP

#include "field/field.hpp"


namespace dnw {
  namespace field {

    /**
     * @class dnw::field::Text
     * @brief This class is for working on text field of a node.
     */
    class Text: public Field {
    protected:
      /**
       * @brief Constructor
       * @param node
       * @param field
       */
      explicit Text(Node const &node, String const &field);

    public:
      /**
       * @brief Checks if text exists in the given @a language.
       * @param language
       * @return Success value
       */
      bool textExists(String const &language) const;

      /**
       * @brief Edits text of the node in the given @a language with @a data.
       * @param language
       * @param data
       * @return Success value
       */
      bool editText(String const &language, String const &data) const;

      /**
       * @brief Search the string given with the @a data parameter in the file given @a langauge.
       * @param language
       * @param data
       * @param Success value
       */
      bool searchText(String const &language, String const &data, bool caseSensitive) const;

      /**
       * @brief Returns text of the node in the given @a language.
       * @param language
       * @return Name of the node in the given @a language.
       */
      String text(String const &language) const;
    };

  }
}


#endif // DNW_FIELD_TEXT_HPP
