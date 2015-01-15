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

#include "wt/stringresource.hpp"
#include <sstream>


namespace dnw {
namespace wt {


using Stream = std::istringstream;


StringResource::StringResource(Parent *parent)
  : Wt::WStreamResource(parent)
  , m_string()
{
}

StringResource::~StringResource()
{
  beingDeleted();
}

void StringResource::handleRequest(Wt::Http::Request const &request, Wt::Http::Response &response)
{
  Stream stream(m_string);

  handleRequestPiecewise(request, response, stream);
}

void StringResource::setString(String const &str)
{
  m_string = str;

  setChanged();
}


} // wt
} // dnw
