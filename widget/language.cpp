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


namespace site {
namespace widget {


Language::Language(String const &language, Parent *parent)
  : Base(language, parent)
  , toolbar(this)
  , enButton(nullptr)
  , trButton(nullptr)
{
  addWidget(&toolbar);

  enButton = new PushButton("English", this);
  trButton = new PushButton("Turkish", this);

  toolbar.addButton(enButton);
  toolbar.addButton(trButton);

  enButton->clicked().connect(this, &Language::onEn);
  trButton->clicked().connect(this, &Language::onTr);
  //enButton->clicked().connect([]{ languageSignal.emit("en"); }); // TODO
  //trButton->clicked().connect([]{ languageSignal.emit("tr"); }); // TODO

}

Language::~Language()
{
}

void Language::update()
{
  if (language() == "tr") {
    enButton->setText("Ingilizce");
    trButton->setText("Turkce");

    return;
  }

  enButton->setText("English");
  trButton->setText("Turkish");

}

void Language::onEn()
{
  changed().emit(String("en"));
}

void Language::onTr()
{
  changed().emit(String("tr"));
}


} // widget
} // site
