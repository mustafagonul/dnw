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

#include "widget/mode.hpp"
#include "system/system.hpp"


namespace dnw {
namespace widget {


Mode::Mode(System const &system, Parent *parent)
  : Widget(system, parent)
  , toolbar(this)
  , guestButton(nullptr)
  , adminButton(nullptr)
{
  addWidget(&toolbar);

  guestButton = new PushButton("Guest", this);
  adminButton = new PushButton("Admin", this);

  toolbar.addButton(guestButton);
  toolbar.addButton(adminButton);

  guestButton->clicked().connect(this, &Mode::onGuest);
  adminButton->clicked().connect(this, &Mode::onAdmin);

  //enButton->clicked().connect([&]{ languageSignal.emit("en"); }); // TODO
  //trButton->clicked().connect([&]{ languageSignal.emit("tr"); }); // TODO
}

Mode::~Mode()
{
}

void Mode::onAdmin()
{
  changed().emit(String("admin"));
}

void Mode::onGuest()
{
  changed().emit(String("guest"));
}

void Mode::update()
{
  if (system().language() == "tr") {
    guestButton->setText("Ziyaretci");
    adminButton->setText("Yonetici");

    return;
  }

  guestButton->setText("Guest");
  adminButton->setText("Admin");
}



} // widget
} // dnw
