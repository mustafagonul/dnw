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

/**
 * @file field/resource.hpp
 * @author Mustafa Gönül
 */

#ifndef DNW_FIELD_RESOURCE_HPP
#define DNW_FIELD_RESOURCE_HPP

#include "field/field.hpp"


namespace dnw {
  namespace field {

    /**
     * @class dnw::field::Resource
     * @brief This class is for working on resources of a node.
     */
    class Resource : public Field {
    protected:
      /**
       * @brief Constructor
       * @param node
       * @param field
       */
      Resource(Node const &node, String const &field);

    public:
      /**
       * @brief Returns resource count in the field.
       * @return resource count
       */
      Count resourceCount() const;

      /**
       * @brief Returns resource name in the field with the given @a index.
       * @param index
       * @return Resource name
       */
      String resourceName(Index index) const;

      /**
       * @brief Internal data of @a name.
       * @param name
       * @return Resource data
       */
      String resource(String const &name) const;

      /**
       * @brief TODO mustafa
       * @param index
       * @return Resource path
       */
      String resourcePath(Index index) const;

      /**
       * @brief TODO mustafa
       * @param name
       * @return Check value
       */
      bool resourceExists(String const &name) const;

      /**
       * @brief Edits @a name resource with @a data.
       * @param name
       * @param data
       * @return Success value
       */
      bool editResource(String const &name, String const &data) const;

      /**
       * @brief Removes the @a name resource.
       * @param name
       * @return Success value
       */
      bool removeResource(String const &name) const;

      /**
       * @brief Moves the resource given with @a name to child node at @a index.
       * @param index
       * @param name
       * @return Success value
       */
      bool moveResourceToChild(Index index, String const &name) const;

      /**
       * @brief Moves the resource given with @a name to parent node.
       * @param name
       * @return Success value
       */
      bool moveResourceToParent(String const &name) const;
    };

  }
}


#endif // DNW_FIELD_RESOURCE_HPP
