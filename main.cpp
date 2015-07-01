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
#include <boost/filesystem.hpp>


using namespace std;
using namespace Wt;
using namespace boost::filesystem;


WApplication *createApplication(const WEnvironment& env)
{
  return new dnw::Application(env);
}

// main
#ifndef NDEBUG // debug mode
  int main()
#else // release mode
  int main(int argc, const char **argv)
#endif
{

  // parameters
#ifndef NDEBUG // debug mode
  const char *argv[] = {
    "dnw_exe",
    "--docroot=.",
    "--http-address=0.0.0.0",
    "--http-port=8080",
    "--gdb",
  };

  int argc = sizeof(argv) / sizeof(argv[0]);
#endif

  // server running
  int result = 0;
  try {
    dnw::authentication::Session::configureAuth();

    result = WRun(argc, const_cast<char **>(argv), &createApplication);
  }
  catch (...) {
    result = -1;
  }

  // result
  return result;
}

