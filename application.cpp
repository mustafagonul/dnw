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
#include <Wt/WEnvironment>
#include <Wt/WBootstrapTheme>
// #include <boost/filesystem.hpp>
#include <mutex>


// namespace fs = boost::filesystem;


namespace dnw {


using Mutex = std::recursive_mutex;
using Guard = std::lock_guard<Mutex>;


/*
static bool copy_recursive(fs::path source, fs::path destination)
try {
  // source check
  if (fs::exists(source) == false)
    return false;

  // if the source is directory
  if (fs::is_directory(source)) {
    // destination check
    if (fs::exists(destination) == false)
      return false;
    // if the destination is not directory
    if (fs::is_directory(destination) == false)
      return false;

    // creating directory
    destination /= source.filename();
    if (fs::create_directory(destination) == false)
      return false;

    // item loop
    for (fs::directory_iterator iter(source); iter != fs::directory_iterator(); ++iter) {
      auto itemSource = iter->path();
      auto itemDestination = destination / itemSource.filename();

      if (copy_recursive(itemSource, itemDestination) == false)
        return false;
    }

    return true;
  }

  // it the source is regular file
  if (fs::is_regular_file(source)) {
    if (fs::is_directory(destination))
      destination /= source.filename();
    fs::copy_file(source, destination, fs::copy_option::overwrite_if_exists);
    return true;
  }

  // others
  return false;
}
catch (...) {
  return false;
}
*/

static void logConnetion(Wt::WEnvironment const &env)
{
  static Mutex mutex;
  Guard guard(mutex);


  std::ofstream file;
  file.open("connection_log.txt", std::ofstream::out | std::ofstream::app);
  file << boost::posix_time::second_clock::local_time() << "    " << env.clientAddress() << std::endl;
  file.close();
}

Application::Application(Environment const &env)
  : Wt::WApplication(env)
{
  // UTF8
  Wt::WString::setDefaultEncoding(Wt::UTF8);

  // Theme
  setTheme(new Wt::WBootstrapTheme());

  // Title
  setTitle("Dnw");

  // connection log
  logConnetion(env);

  // main
  auto main = new dnw::widget::Main();
  root()->addWidget(main);
}

Application::~Application()
{
}


} // dnw
