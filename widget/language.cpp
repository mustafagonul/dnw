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

#include "widget/language.hpp"
#include "system/system.hpp"


namespace dnw {
namespace widget {


Language::Language(System const &system, Parent *parent)
  : Widget(system, parent)
  , m_toolbar(this)
  , m_pushbuttons()
  , m_languageChanged()
{
  // if there is not enough language, there is nothing to create
  Size languageCount = system.languageCount();
  if (languageCount < 2)
    return;

  // adding toolbar
  addWidget(&m_toolbar);

  // buttons
  for (Size i = 0; i < languageCount; ++i) {
    auto languageStr = system.languageStr(i);
    auto languageTag = system.languageTag(i);

    PushButton *button = new PushButton(languageStr, this);
    m_toolbar.addButton(button);

    m_pushbuttons[button] = languageTag;

    button->clicked().connect(std::bind([this](String const &l){
      languageChanged().emit(String(l));
    }, languageTag));
  }
}

Language::~Language()
{
}

void Language::update()
{
}

Language::Signal &Language::languageChanged()
{
  return m_languageChanged;
}


} // widget
} // dnw
