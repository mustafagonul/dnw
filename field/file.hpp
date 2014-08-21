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

#ifndef SITE_FIELD_FILE_HPP
#define SITE_FIELD_FILE_HPP

#include "field/field.hpp"


namespace site {
  namespace field {

    /**
     * @class site::field::File
     * @brief This class is for working on file field of a node.
     */
    class File : public Field {
    public:
      /**
       * @brief Constructor
       * @param device
       */
      explicit File(Device const &device);

    public:
      /**
       * @brief Returns file count in the file field.
       * @return File count
       */
      Index fileCount() const;

      /**
       * @brief Returns file name in the file field with the given @a index.
       * @param index
       * @return File name
       */
      String fileName(Index index) const;

      /**
       * @brief Internal data of @a name.
       * @param name
       * @return File data
       */
      String file(String const &name) const;

      /**
       * @brief TODO mustafa
       * @param index
       * @return File link
       */
      String fileLink(Index index) const;

      /**
       * @brief TODO mustafa
       * @param index
       * @return File path
       */
      String filePath(Index index) const;

      /**
       * @brief TODO mustafa
       * @return Directory link.
       */
      String directoryLink() const;

      /**
       * @brief TODO mustafass
       * @param name
       * @return Check value
       */
      bool fileExists(String const &name) const;

      /**
       * @brief Edits @a name file with @a data.
       * @param name
       * @param data
       * @return Success value
       */
      bool editFile(String const &name, String const &data) const;

      /**
       * @brief Removes the @a name file.
       * @param name
       * @return Success value
       */
      bool removeFile(String const &name) const;

      /**
       * @brief Moves the file given with @a name to child node at @a index.
       * @param index
       * @param name
       * @return Success value
       */
      bool moveFileToChild(Index index, String const &name) const;

      /**
       * @brief Moves the file given with @a name to parent node.
       * @param name
       * @return Success value
       */
      bool moveFileToParent(String const &name) const;
    };

  }
}


#endif // SITE_FIELD_FILE_HPP
