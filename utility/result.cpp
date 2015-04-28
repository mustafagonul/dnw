#include "utility/result.hpp"


namespace dnw {
namespace utility {


Result::Result()
  : m_messages()
  , m_key()
{
}

Result::Result(Message const &msg)
  : Result()
{
  add(msg);
}

Result::Result(Any const &key)
  : Result()
{
  setKey(key);
}

bool Result::check() const
{
  return m_messages.empty();
}

void Result::add(Message const &msg)
{
  m_messages.push_back(msg);
}

void Result::add(Result const &result)
{
  std::copy(result.begin(), result.end(), std::back_inserter<Messages>(m_messages));
}

void Result::clear()
{
  m_messages.clear();
}

void Result::setKey(Any const &any)
{
  m_key = any;
}

Result::Any const &Result::key() const
{
  return m_key;
}

Result::Index Result::count() const
{
  return m_messages.size();
}

Result::Message Result::message(Index index) const
{
  if (index >= count())
    return Message();

  return m_messages[index];
}

Result::String Result::all(String const &delimeter) const
{
  String result;

  for (auto &msg : m_messages) {
    result += msg;
    result += delimeter;
  }

  return result;
}


} // utility
} // dnw


