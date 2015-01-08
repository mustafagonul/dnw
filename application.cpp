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
#include <boost/process.hpp>
#include <dlfcn.h>
#include <mutex>


namespace fs = boost::filesystem;
namespace bp = boost::process;



namespace dnw {


using Mutex = std::recursive_mutex;
using Guard = std::lock_guard<Mutex>;


static const auto g_libraryName = "libdnw.so";
static const auto g_libraryFunction = "createInstance";
static Mutex g_mutex;


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
    fs::copy_file(source, destination, fs::copy_option::overwrite_if_exists);
    return true;
  }

  // others
  return false;
}
catch (...) {
  return false;
}


void Application::writeLine(String const &line)
{
  new Wt::WText(line, root());
  new Wt::WBreak(root());

  processEvents();
}


void Application::runCommand(String const &prefix, String const &cmd)
{
  auto exec = cmd + " 2>&1";

  bp::context ctx;
  ctx.stdout_behavior = bp::capture_stream();
  ctx.environment = bp::self::get_environment();

  auto child = bp::launch_shell(exec, ctx);
  auto &outs = child.get_stdout();


  String line;
  while (std::getline(outs, line))
    writeLine(prefix + ": " + line);
}

Application::Application(Environment const &env)
  : Wt::WApplication(env)
  , libraryHandle(nullptr)
  , mainPtr(nullptr)
{
  // UTF8
  Wt::WString::setDefaultEncoding(Wt::UTF8);

  // Theme
  setTheme(new Wt::WBootstrapTheme());

  // Title
  setTitle("Dnw");

  // library
  if (checkLibrary() == false)
    buildLibrary();
  else
    loadLibrary();
}

bool Application::checkLibrary() const
{
  Guard guard(g_mutex);

  auto path = fs::current_path() / g_libraryName;
  auto pathStr = path.string();
  auto handle = dlopen(pathStr.c_str(), RTLD_NOW);
  if (handle == nullptr)
    return false;

  auto ptr = dlsym(handle, g_libraryFunction);
  dlclose(handle);

  if (ptr == nullptr)
    return false;

  return true;
}

void Application::buildLibrary()
{
  Guard guard(g_mutex);

  // unloading library
  unloadLibrary();

  // directories
  auto cwd = fs::current_path();
  auto rep = cwd / "dnw";
  auto dir = cwd / "dnw_release";

  // deleting directories in case
  fs::remove_all(dir);
  fs::remove_all(rep);

  // build message
  writeLine("Building...");

  // commands
  static const auto gitCommand = "git clone https://github.com/mustafagonul/dnw.git";
  static const auto cmakeCommand = "cmake -DCMAKE_BUILD_TYPE=Release ../dnw";
  static const auto makeCommand = "make dnw";

  // getting repository
  runCommand("git", gitCommand);

  // creating new directory for build,
  // changing current path to this path
  fs::create_directory(dir);
  fs::current_path(dir);

  // cmake & make
  runCommand("cmake", cmakeCommand);
  runCommand("make", makeCommand);

  // restoring current path
  fs::current_path(cwd);

  // copying dynamic library (with message)
  writeLine("Copying...");
  fs::remove(cwd / g_libraryName);
  fs::copy(dir / g_libraryName, cwd / g_libraryName);
  for (fs::directory_iterator iter(rep / "deploy");
       iter != fs::directory_iterator(); ++iter) {
    auto source = iter->path();
    auto destination = cwd;
    auto directory = cwd / source.filename();

    fs::remove_all(directory);
    copy_recursive(source, destination);
  }

  // deleting directories
  fs::remove_all(dir);
  fs::remove_all(rep);

  // completion message
  writeLine("Completed...");

  // loading library
  writeLine("Loading...");
  loadLibrary();
}

void Application::loadLibrary()
{
  Guard guard(g_mutex);

  // In case
  unloadLibrary();

  // Library path
  auto path = fs::current_path() / g_libraryName;
  auto pathStr = path.string();

  // Loading library
  libraryHandle = dlopen(pathStr.c_str(), RTLD_NOW);
  if (libraryHandle == nullptr) {
    writeLine("Library load error!");
    return;
  }

  // checking error
  char *error = dlerror();
  if (error) {
    writeLine(error);
    return;
  }

  // Getting function
  auto ptr = dlsym(libraryHandle, g_libraryFunction);
  error = dlerror();
  if (error) {
    writeLine(error);
    return;
  }

  // Calling function
  using Function = decltype(dnw::widget::createInstance);
  auto function = reinterpret_cast<Function *>(ptr);
  mainPtr = function();

  // Adding main
  root()->clear();
  root()->addWidget(mainPtr.get());

  // Connections
  mainPtr->rebuild().connect(this, &Application::buildLibrary);
}

void Application::unloadLibrary()
{
  Guard guard(g_mutex);

  if (mainPtr) {
    root()->removeWidget(mainPtr.get());
    mainPtr = nullptr;
  }

  if (libraryHandle == nullptr)
    return;

  dlclose(libraryHandle);
  libraryHandle = nullptr;
}

Application::~Application()
{
  unloadLibrary();
}


} // dnw
