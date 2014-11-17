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
 * @file field/field.hpp
 * @author Mustafa Gonul
 */

#ifndef DNW_FIELD_FIELD_HPP
#define DNW_FIELD_FIELD_HPP

#include "system/fwd.hpp"
#include <string>


namespace dnw {
  namespace field {

    /**
     * @class dnw::field::Field
     * @brief This class is a base class for working on fields of a node
     */
    class Field {
    protected:
      using Device = dnw::system::Device;
      using String = std::string;
      using Index  = unsigned;

    protected:
      /**
       * @brief Constructor
       * @param device
       * @param field
       */
      Field(Device const &device, String const &field);

      /**
       * @name Deleted functions
       * @{
       */
      Field(Field &&) = delete;
      Field(Field const &) = delete;
      void operator=(Field &&) = delete;
      void operator=(Field const &) = delete;

      /** @} */ // end of deleted functions

    protected:
      /**
       * @brief Returns the number of files in the field.
       * @return The number of the files.
       */
      Index count() const;

      /**
       * @brief Checks if the file given with @a name parameter exists in the field.
       * @param name
       * @return Success value
       */
      bool exists(String const &name) const;

      /**
       * @brief Removes the file given with the parameter @a name from the field.
       * @param name
       * @return Success value
       */
      bool remove(String const &name) const;

      /**
       * @brief Edits the file given with the parameter @a name in the field with @a data.
       * @param name
       * @param data
       * @return Success value
       */
      bool edit(String const &name, String const &data) const;

      /**
       * @brief Returns the name of the file at the @a index in the field.
       * @param index
       * @return Name of the file in a specific field.
       */
      String name(Index index) const;

      /**
       * @brief Returns data in the file given with @a name parameter in the field.
       * @param name
       * @return Data in the file. If there is no file, returns an empty string.
       */
      String data(String const &name) const;

      /**
       * @ Returns path to file.
       * @param name
       * @return File path
       */
      String path(String const &name) const;


    protected:
      Device const &device; /**< device */

    private:
      String field;         /**< field */
    };

  }
}

#endif // DNW_FIELD_FIELD_HPP
