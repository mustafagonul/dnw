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
#include "widget/application.hpp"


using namespace Wt;


WApplication *createApplication(const WEnvironment& env)
{
  return new site::widget::Application(env);
}


int main(int argc, char **argv)
{
  return WRun(argc, argv, &createApplication);
}

/*
#include <boost/filesystem.hpp>
#include <limits>
#include <string>

namespace fs = boost::filesystem;

void move(fs::path const &current)
{
  fs::create_directory(current / "content");
  try { fs::rename(current / "en", current / "content" / "en");  } catch (...) {}
  try { fs::rename(current / "tr", current / "content" / "tr");  } catch (...) {}

  unsigned max = std::numeric_limits<unsigned>::max();

  for (unsigned i = 0; i < max; ++i) {
    auto sub = current / std::to_string(i);
    if (fs::exists(sub) == false)
      break;

    move(sub);
  }
}

int main()
{
  auto current = fs::current_path();

  move(current / "data");

  return 0;
}
*/
