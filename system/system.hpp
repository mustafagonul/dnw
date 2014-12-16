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

#ifndef DNW_SYSTEM_SYSTEM_HPP
#define DNW_SYSTEM_SYSTEM_HPP

#include "utility/common.hpp"
#include "system/fwd.hpp"
#include <memory>


namespace dnw {
  namespace system {

    class System {
    private:
      using NodePtr = std::shared_ptr<Node>;

    public:
      System(Config &config, Node &root);

      // TODO mustafa: special functions

    public:
      Size   languageCount() const;
      String languageTag(Index index) const;
      String languageStr(Index index) const;
      String baseLanguage() const;

      String  language() const;
      NodePtr node() const;
      NodePtr root() const;
      Any     key() const;

      void setKey(Any const &key);
      void setLanguage(String const &language);

    private:
      Config &m_config;
      Node   &m_root;

      Strings m_languageTags;
      Strings m_languageStrs;
      String  m_currentLanguageTag;
      String  m_baseLanguageTag;
      Any     m_currentKey;
    };

  }
}


#endif // DNW_SYSTEM_SYSTEM_HPP
