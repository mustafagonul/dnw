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
#include <boost/interprocess/sync/file_lock.hpp>


using namespace std;
using namespace Wt;
using namespace boost::interprocess;


WApplication *createApplication(const WEnvironment& env)
{
  return new dnw::Application(env);
}


int main()
{
  // lock file name
  #ifndef NDEBUG // debug mode
    static const auto lockFileName = "mustafagonul-dnw-debug.lockfile";
  #else
    static const auto lockFileName = "mustafagonul-dnw.lockfile";
  #endif


  try {
    // creating file if not exits
    ofstream file;
    file.open(lockFileName);
    file.close();

    // locking file
    file_lock flock(lockFileName);
    if (flock.try_lock() == false) {
      std::cerr << "Already Running !!!" << std::endl;

      return -1;
    }
  }
  catch (...) {
    std::cerr << "Lock File Error !!!" << std::endl;

    return -1;
  }

  // parameters
#ifndef NDEBUG // debug mode
  const char *argv[] = {
    "dnw_exe",
    "--docroot", ".",
    "--http-address", "0.0.0.0",
    "--http-port", "8080",
  };
#else // release mode
  const char *argv[] = {
    "dnw_exe",
    "--docroot", ".",
    "--http-address", "0.0.0.0",
    "--http-port", "80",
  };
#endif

  // server running
  int argc = sizeof(argv) / sizeof(argv[0]);
  int result = 0;
  try {
    result = WRun(argc, const_cast<char **>(argv), &createApplication);
  }
  catch (...) {
    result = -1;
  }

  // result
  return result;
}

