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

#include "application.hpp"
#include "widget/main.hpp"
#include <Wt/WBootstrapTheme>
#include <Wt/WText>
#include <boost/filesystem.hpp>
#include <dlfcn.h>


namespace fs = boost::filesystem;


namespace dnw {


Application::Application(Environment const &env)
  : Wt::WApplication(env)
{
  // UTF8
  Wt::WString::setDefaultEncoding(Wt::UTF8);

  // Theme
  setTheme(new Wt::WBootstrapTheme());

  // Title
  setTitle("Dnw");

  // Library path
  auto path = fs::current_path() / "libdnw.so";
  auto pathStr = path.string();

  // Loading library
  auto libHandle = dlopen(pathStr.c_str(), RTLD_NOW);
  if (libHandle == nullptr) {
    new Wt::WText("Library load error!", root());
    return;
  }

  // Getting function
  using Function = decltype(dnw::widget::createInstance);
  auto ptr = dlsym(libHandle, "createInstance");
  char *error = nullptr;
  if ((error = dlerror()) != nullptr) {
    new Wt::WText(error, root());
    return;
  }

  // Calling function
  auto function = reinterpret_cast<Function *>(ptr);
  auto mainPtr = function();
  auto main = reinterpret_cast<dnw::widget::Main *>(mainPtr);

  // Adding main
  root()->addWidget(main);
}

Application::~Application()
{
}


} // dnw
