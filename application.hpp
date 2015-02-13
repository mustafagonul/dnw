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

#ifndef DNW_APPLICATION_HPP
#define DNW_APPLICATION_HPP

#include <Wt/WApplication>
#include "widget/main.hpp"
#include "utility/common.hpp"


namespace dnw {

  class Application : public Wt::WApplication {
  private:
    using Environment = Wt::WEnvironment;
    using Handle = void *;

  public:
    explicit Application(Environment const &);
    virtual ~Application();
  };

}


#endif // DNW_APPLICATION_HPP
