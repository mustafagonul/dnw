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

#ifndef DNW_DIALOG_SELECT_HPP
#define DNW_DIALOG_SELECT_HPP

#include "utility/common.hpp"


namespace dnw {
  namespace dialog {

    bool selectWithSelectionBox(String const &title, Strings const &strings, Index &current);
    bool selectWithButtonGroup(String const &title, Strings const &strings, Index &current);

  }
}


#endif // DNW_DIALOG_SELECT_HPP
