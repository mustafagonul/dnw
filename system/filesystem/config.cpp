#include "system/filesystem/config.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>


namespace dnw {
namespace system {
namespace filesystem {


static const char delimiter = '/';
static const String filename = "config.ini";
namespace bpt = boost::property_tree;

/*
template <typename TYPE>
inline static Optional<TYPE> get(String const &property, String const &header)
{
  String pathStr = property;
  pathStr += delimiter;
  pathStr += header;

  bpt::path path(pathStr, delimiter);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  return pt.get_optional<TYPE>(path);
}

template <typename TYPE>
inline static bool set(String const &property, String const &header, TYPE const &value)
{
  String pathStr = property;
  pathStr += delimiter;
  pathStr += header;

  bpt::path path(pathStr, delimiter);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  pt.put(path, value);

  bpt::write_ini(filename, pt);

  return true;
}
*/

Config::Config()
{
}

Config::~Config()
{
}

Size Config::count(String const &header) const
try
{
  bpt::ptree pt;
  bpt::read_ini(filename, pt);
  bpt::path path(header);

  return pt.get_child(path).size();
}
catch (...) {
  return 0;
}

Config::OStr Config::value(String const &header, String const &property) const
try
{
  String pathStr = header;
  pathStr += delimiter;
  pathStr += property;

  bpt::path path(pathStr, delimiter);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  return pt.get_optional<String>(path);
}
catch (...){
  return OStr();
}

Config::OStr Config::value(String const &header, Index index) const
try
{
  bpt::path path(header);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  if (auto child = pt.get_child_optional(path)) {
    auto iter = child.value().begin();
    std::advance(iter, index);

    if (iter == child.value().end())
      return OStr();

    String childPathStr = header;
    childPathStr += delimiter;
    childPathStr += iter->first;

    bpt::path childPath(childPathStr, delimiter);
    return pt.get_optional<String>(childPath);
  }

  return OStr();
}
catch (...) {
  return OStr();
}

Config::OStr Config::property(String const &header, Index index) const
try
{
  bpt::path path(header);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  if (auto child = pt.get_child_optional(path)) {
    auto iter = child.value().begin();
    std::advance(iter, index);

    if (iter == child.value().end())
      return OStr();

    return OStr(iter->first);
  }

  return OStr();
}
catch (...) {
  return OStr();
}

void Config::set(String const &header, String const &property, String const &value)
try
{
  String pathStr = header;
  pathStr += delimiter;
  pathStr += property;

  bpt::path path(pathStr, delimiter);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  pt.put(path, value);

  bpt::write_ini(filename, pt);
}
catch (...) {
}

void Config::set(String const &header, Index index, String const &value)
try
{

  bpt::path path(header);
  bpt::ptree pt;
  bpt::read_ini(filename, pt);

  if (auto child = pt.get_child_optional(path)) {
    auto iter = child.value().begin();
    std::advance(iter, index);

    if (iter == child.value().end())
      return;

    String childPathStr = header;
    childPathStr += delimiter;
    childPathStr += iter->first;

    bpt::path childPath(childPathStr);
    pt.put(childPath, value);

    bpt::write_ini(filename, pt);
  }
}
catch (...) {
}


} // filesystem
} // system
} // dnw
