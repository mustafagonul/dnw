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
 * @file field/content.hpp
 * @author Mustafa Gonul
 */

#ifndef SITE_FIELD_CONTENT_HPP
#define SITE_FIELD_CONTENT_HPP

#include "field/field.hpp"


namespace site {
  namespace field {

    /**
     * @class site::field::Content
     * @brief This class is for working on content field of a node.
     */
    class Content : public Field {
    public:
      /**
       * @brief Constructor
       * @param device
       */
      explicit Content(Device const &device);

    public:
      /**
       * @brief Checks if content exists in the given @a language
       * @param language
       * @return Success value
       */
      bool contentExists(String const &language) const;

      /**
       * @brief Edits content of the node in the given @a language with @a data.
       * @param language
       * @param data
       * @return Success value
       */
      bool editContent(String const &language, String const &data) const;

      /**
       * @brief Returns content of the node in the given @a language.
       * @param language
       * @return Content of the node in the given @a language.
       */
      String content(String const &language) const;

    };

  }
}


#endif // SITE_FIELD_CONTENT_HPP
