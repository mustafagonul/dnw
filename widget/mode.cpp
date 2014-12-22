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
#include <Wt/WPushButton>


namespace dnw {
namespace widget {


Mode::Mode(System const &system, Parent *parent)
  : Widget(system, parent)
  , toolbar(this)
{
  using PushButton = Wt::WPushButton;

  addWidget(&toolbar);

  auto guestButton = new PushButton(tr("Guest"), this);
  auto adminButton = new PushButton(tr("Admin"), this);

  toolbar.addButton(guestButton);
  toolbar.addButton(adminButton);

  guestButton->clicked().connect(std::bind([this]{
    changed().emit(String("guest"));
  }));
  adminButton->clicked().connect(std::bind([this]{
    changed().emit(String("admin"));
  }));
}

Mode::~Mode()
{
}

void Mode::update()
{
}


} // widget
} // dnw
