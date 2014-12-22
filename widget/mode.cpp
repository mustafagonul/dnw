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
  , guestButton(nullptr) // TODO mustafa: remove this
  , adminButton(nullptr) // TODO mustafa: remove this
{
  addWidget(&toolbar);

  guestButton = new PushButton(tr("Guest"), this);
  adminButton = new PushButton(tr("Admin"), this);

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

// TODO mustafa: remove this
void Mode::onAdmin()
{
  changed().emit(String("admin"));
}

// TODO mustafa: remove this
void Mode::onGuest()
{
  changed().emit(String("guest"));
}

void Mode::update()
{
  // guestButton->setText(tr("Guest"));
  // adminButton->setText(tr("Admin"));
}



} // widget
} // dnw
