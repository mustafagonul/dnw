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
 * @file field/file.hpp
 * @author Mustafa Gönül
 */

#ifndef DNW_FIELD_FILE_HPP
#define DNW_FIELD_FILE_HPP

#include "field/resource.hpp"


namespace dnw {
  namespace field {

    /**
     * @class dnw::field::File
     * @brief This class is for working on file field of a node.
     */
    class File : public Resource {
    public:
      /**
       * @brief Constructor
       * @param device
       */
      explicit File(Device const &device);
    };

  }
}


#endif // DNW_FIELD_FILE_HPP
