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

#ifndef DNW_SYSTEM_FILESYSTEM_DEVICE_HPP
#define DNW_SYSTEM_FILESYSTEM_DEVICE_HPP

#include "system/device.hpp"
#include "system/filesystem/key.hpp"


namespace dnw {
  namespace system {
    namespace filesystem {

      /**
       * @class dnw::system::filesystem::Device
       * @brief This class implements abstract Device class. Holds the information at filesystem.
       */
      class Device : public dnw::system::Device {
      private:
        using Base = dnw::system::Device;

      public:
        /**
         * @brief Default constructor
         */
        Device();

      private:
        /**
         * Private constructor used by clone function.
         * @param key
         */
        explicit Device(Key const &key);

      public:
        virtual ~Device();

      public:
        // Clone function
        virtual DevicePtr clone(Any const &key) const;

      public:
        /**
         * @name Check function
         * @{
         */

        /**
         * @brief Checks if devices points the same node.
         * @param device
         * @return Sameness value
         */
        virtual bool isSame(Base const &device) const;

        /** @} */ // end of check function

      public:
        /**
         * @name Node functions
         * @{
         */

        /**
         * @brief Returns the node count at the current node.
         * @return Node count
         */
        virtual Index nodeCount() const;

        /**
         * @brief Pushes a new node to the end.
         * @return Success value
         */
        virtual bool pushNode() const;

        /**
         * @brief Pops the node at the end.
         * @return Success value
         */
        virtual bool popNode() const;

        /**
         * @brief Pops the node at the end to another child node.
         * @param index
         * @return Success value
         */
        virtual bool popNodeToNode(Index index) const;

        /**
         * @brief Pops the node at the end to parent node.
         * @return Success value
         */
        virtual bool popNodeToParent() const;

        /**
         * @brief Swaps two nodes.
         * @param i1
         * @param i2
         * @return Success value
         */
        virtual bool swapNodes(Index i1, Index i2) const;

        /** @} */ // end of node functions

      public:
        /**
         * @name Field functions
         * @{
         */

        /**
         * @brief Returns the number of files in the @a field.
         * @param field
         * @return The number of the files.
         */
        virtual Index count(String const &field) const;

        /**
         * @brief Checks if the file given with @a name parameter exists in the @a field.
         * @param field
         * @param name
         * @return Success value
         */
        virtual bool exists(String const &field, String const &name) const;

        /**
         * @brief Removes the file given with the parameter @a name from the @a field.
         * @param field
         * @param name
         * @return Success value
         */
        virtual bool remove(String const &field, String const &name) const;

        /**
         * @brief Edits the file given with the parameter @a name in the @a field with @a data.
         * @param field
         * @param name
         * @param data
         * @return Success value
         */
        virtual bool edit(String const &field, String const &name, String const &data) const;

        /**
         * @brief Returns the name of the file at the @a index in the @a field.
         * @param field
         * @param index
         * @return Name of the file in a specific field.
         */
        virtual String name(String const &field, Index index) const;

        /**
         * @brief Returns data in the file given with @a name parameter in the @a field.
         * @param field
         * @param name
         * @return Data in the file. If there is no file, returns an empty string.
         */
        virtual String data(String const &field, String const &name) const;

        /**
         * @brief Returns path of the file
         * @param field
         * @param name
         * @return Path of the file in the given field
         */
        String path(String const &field, String const &name) const;

        /** @} */ // end of field functions

      public:
        /**
         * @name Key functions
         * @{
         */

        /**
         * @brief Returns current node key internal value.
         * @return Node key internal value.
         */
        virtual Any currentKey() const;

        /**
         * @brief Returns parent node key internal value.
         * @return Node key internal value. If there is no parent, returns root key.
         */
        virtual Any parentKey() const;

        /**
         * @brief Returns root node key internal value.
         * @return Node key internal value.
         */
        virtual Any rootKey() const;

        /**
         * @brief Returns child node key internal value.
         * @param index
         * @return Node key internal value. If there is no node at the @a index, return root key.
         */
        virtual Any nodeKey(Index index) const;

        /** @} */ // end of key functions

      private:

        /**
         * @brief Key
         * @return key
         */
        Key const &key() const;

      private:
        Key const m_key; /**< key */
      };

    }
  }
}


#endif // DNW_SYSTEM_FILESYSTEM_DEVICE_HPP
