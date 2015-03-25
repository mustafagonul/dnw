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
#include "system/filesystem/config.hpp"
#include "system/filesystem/node.hpp"
#include "system/system.hpp"
#include "authentication/session.hpp"
#include "utility/common.hpp"


namespace dnw {

  class Application : public Wt::WApplication {
  private:
    using Config = dnw::system::filesystem::Config;
    using Node = dnw::system::filesystem::Node;
    using System = dnw::system::System;
    using Session = dnw::authentication::Session;
    using Environment = Wt::WEnvironment;

  public:
    explicit Application(Environment const &);
    virtual ~Application();

  private:
    Config    config;
    Node      node;
    System    system;
    Session   session;
  };

}


#endif // DNW_APPLICATION_HPP
