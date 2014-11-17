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

#ifndef DNW_SYSTEM_DEVICE_HPP
#define DNW_SYSTEM_DEVICE_HPP

#include <string>
#include <memory>
#include <boost/any.hpp>


namespace dnw {
  namespace system {

    class Device {
    protected:
      using Any       = boost::any;
      using Index     = unsigned;
      using String    = std::string;
      using DevicePtr = std::shared_ptr<Device>;

    protected:
      /**
       * @brief Constructor
       */
      Device();

    private:
      /**
       * @name Deleted functions
       * @{
       */
      Device(Device &&) = delete;
      Device(Device const &) = delete;
      void operator=(Device &&) = delete;
      void operator=(Device const &) = delete;

      /** @} */ // end of deleted functions

    public:
      /**
       * @brief Destructor
       */
      virtual ~Device() = 0;

    public:
      /**
       * @name Clone function
       * @{
       */

      /**
       * @brief Clones with the current device with @a key.
       * @param key
       * @return Clone of the device with @a key.
       */
      virtual DevicePtr clone(Any const &key) const = 0;

      /** @} */ // end of clone function

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
      virtual bool isSame(Device const &device) const = 0;

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
      virtual Index nodeCount() const = 0;

      /**
       * @brief Pushes a new node to the end.
       * @return Success value
       */
      virtual bool pushNode() const = 0;

      /**
       * @brief Pops the node at the end.
       * @return Success value
       */
      virtual bool popNode() const = 0;

      /**
       * @brief Pops the node at the end to another child node.
       * @param index
       * @return Success value
       */
      virtual bool popNodeToNode(Index index) const = 0;

      /**
       * @brief Pops the node at the end to parent node.
       * @return Success value
       */
      virtual bool popNodeToParent() const = 0;

      /**
       * @brief Swaps two nodes.
       * @param i1
       * @param i2
       * @return Success value
       */
      virtual bool swapNodes(Index i1, Index i2) const = 0;

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
      virtual Index count(String const &field) const = 0;

      /**
       * @brief Checks if the file given with @a name parameter exists in the @a field.
       * @param field
       * @param name
       * @return Success value
       */
      virtual bool exists(String const &field, String const &name) const = 0;

      /**
       * @brief Removes the file given with the parameter @a name from the @a field.
       * @param field
       * @param name
       * @return Success value
       */
      virtual bool remove(String const &field, String const &name) const = 0;

      /**
       * @brief Edits the file given with the parameter @a name in the @a field with @a data.
       * @param field
       * @param name
       * @param data
       * @return Success value
       */
      virtual bool edit(String const &field, String const &name, String const &data) const = 0;

      /**
       * @brief Returns the name of the file at the @a index in the @a field.
       * @param field
       * @param index
       * @return Name of the file in a specific field.
       */
      virtual String name(String const &field, Index index) const = 0;

      /**
       * @brief Returns data in the file given with @a name parameter in the @a field.
       * @param field
       * @param name
       * @return Data in the file. If there is no file, returns an empty string.
       */
      virtual String data(String const &field, String const &name) const = 0;

      /**
       * @brief Returns path of the file
       * @param field
       * @param name
       * @return Path of the file in the given field
       */
      virtual String path(String const &field, String const &name) const = 0;

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
      virtual Any currentKey() const = 0;

      /**
       * @brief Returns parent node key internal value.
       * @return Node key internal value.
       */
      virtual Any parentKey() const = 0;

      /**
       * @brief Returns root node key internal value.
       * @return Node key internal value.
       */
      virtual Any rootKey() const = 0;

      /**
       * @brief Returns child node key internal value.
       * @param index
       * @return Node key internal value.
       */
      virtual Any nodeKey(Index index) const = 0;

      /** @} */ // end of key functions

    public:
      /**
       * @name Move - remove node functions
       * @{
       */

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool removeNode(Index index) const;

      /**
       * @brief
       * @param from
       * @param to
       * @return Success value
       */
      bool moveNode(Index from, Index to) const;

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool moveNodeUp(Index index) const;

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool moveNodeDown(Index index) const;

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool moveNodeToLast(Index index) const;

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool moveLastToNode(Index index) const;

      /**
       * @brief
       * @param index
       * @return Success value
       */
      bool moveNodeToParent(Index index) const;

      /**
       * @brief
       * @param index
       * @param to
       * @return Success value
       */
      bool moveNodeToNode(Index index, Index to) const;

      /** @} */ // end of move remove node functions

    public:
      /**
       * @name Device functions
       * @{
       */

      /**
       *
       * @param index
       * @return
       */
      DevicePtr nodeDevice(Index index) const;

      /**
       *
       * @return
       */
      DevicePtr lastDevice() const;

      /**
       *
       * @return
       */
      DevicePtr parentDevice() const;

      /**
       *
       * @return
       */
      DevicePtr rootDevice() const;

      /** @} */ // end of device functions

    };

  }
}

#endif // DNW_SYSTEM_DEVICE_HPP
