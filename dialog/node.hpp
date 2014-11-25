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

#ifndef DNW_DIALOG_NODE_HPP
#define DNW_DIALOG_NODE_HPP

#include "utility/common.hpp"
#include "system/fwd.hpp"


namespace dnw {
  namespace dialog {

    bool removeNode(system::Device const &device, String const &language);
    bool moveNodeUp(system::Device const &device, String const &language);
    bool moveNodeDown(system::Device const &device, String const &language);

  }
}


#endif // DNW_DIALOG_NODE_HPP
