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

#include <Wt/WApplication>
#include "system/system.hpp"
#include "system/filesystem/config.hpp"
#include "system/filesystem/node.hpp"
#include "widget/application.hpp"


dnw::system::filesystem::Config conf;
dnw::system::filesystem::Node node;
dnw::system::System sys(conf, node);


using namespace Wt;


WApplication *createApplication(const WEnvironment& env)
{
  return new dnw::widget::Application(sys, env);
}


int main(int argc, char **argv)
{
  dnw::authentication::Session::configureAuth();

  return WRun(argc, argv, &createApplication);
}

