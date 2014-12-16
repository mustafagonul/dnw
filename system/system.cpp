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

#include "system/system.hpp"
#include "system/config.hpp"
#include "system/node.hpp"


namespace dnw {
namespace system {


static const String defaultLanguageTag = "en";
static const String defaultLanguageStr = "English";


System::System(Config &config, Node &root)
  : m_config(config)
  , m_root(root)
  , m_languageTags()
  , m_languageStrs()
  , m_currentLanguageTag(defaultLanguageTag)
  , m_baseLanguageTag(defaultLanguageTag)
  , m_currentKey(root.rootKey())
{
  static const String languageHeader = "languages";
  static const String baseLanguageHeader = "base_language";

  using OStr = boost::optional<String>;

  // if there is no config about languages
  auto count = config.count(languageHeader);
  if (count == 0) {
    m_languageTags.push_back(defaultLanguageTag);
    m_languageStrs.push_back(defaultLanguageStr);
    m_baseLanguageTag = defaultLanguageTag;
    m_currentLanguageTag = defaultLanguageTag;

    return;
  }

  // adding languages
  for (decltype(count) i = 0; i < count; ++i) {
    OStr tag, str;
    if ((tag = config.property(languageHeader, i)) &&
        (str = config.value(languageHeader, i))) {
      m_languageTags.push_back(tag.value());
      m_languageStrs.push_back(str.value());
    }
  }

  // if there is base language
  OStr base;
  if ((base = config.value(baseLanguageHeader, "base"))) {
    m_baseLanguageTag = base.value();
    m_currentLanguageTag = base.value();

    return;
  }

  // if there is no base language
  m_baseLanguageTag = m_languageTags.front();
  m_currentLanguageTag = m_languageTags.front();
}

Size System::languageCount() const
{
  return m_languageTags.size();
}

String System::languageTag(Index index) const
{
  if (index >= m_languageTags.size())
    return String();

  return m_languageTags[index];
}

String System::languageStr(Index index) const
{
  if (index >= m_languageStrs.size())
    return String();

  return m_languageStrs[index];
}

String System::baseLanguage() const
{
  return m_baseLanguageTag;
}

String System::language() const
{
  return m_currentLanguageTag;
}

System::NodePtr System::node() const
{
  return m_root.clone(key());
}

System::NodePtr System::root() const
{
  return m_root.root();
}

Any System::key() const
{
  return m_currentKey;
}

void System::setKey(Any const &key)
{
  m_currentKey = key;
}

void System::setLanguage(String const &language)
{
  auto iter = std::find(m_languageTags.begin(), m_languageTags.end(), language);
  if (iter != m_languageTags.end())
    m_currentLanguageTag = language;
}


} // system
} // dnw
