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

#ifndef DNW_WT_STRINGRESOURCE_HPP
#define DNW_WT_STRINGRESOURCE_HPP

#include "utility/common.hpp"
#include <Wt/WStreamResource>


namespace dnw {
  namespace wt {

    class StringResource : public Wt::WStreamResource {
    private:
      using Parent = Wt::WObject;

    public:
      explicit StringResource(Parent *parent = nullptr);
      virtual ~StringResource();

    public:
      virtual void handleRequest(Wt::Http::Request const &request, Wt::Http::Response &response) override;

    public:
      void setString(String const &str);

    private:
      String m_string;
    };




  }
}


#endif // DNW_WT_STRINGRESOURCE_HPP
