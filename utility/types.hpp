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

#ifndef DNW_UTILITY_TYPES_HPP
#define DNW_UTILITY_TYPES_HPP

#include <string>
#include <vector>
#include <boost/any.hpp>


namespace dnw {

  using Count = std::size_t;
  using Size = std::size_t;
  using Index = std::size_t;
  using Indices = std::vector<Index>;
  using String = std::string;
  using Strings = std::vector<std::string>;
  using Any = boost::any;
  using Anys = std::vector<Any>;

}


#endif // DNW_UTILITY_TYPES_HPP
