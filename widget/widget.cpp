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

#include "widget/widget.hpp"


namespace site {
namespace widget {


Widget::Widget(Device const &device,
               String const &language,
               Any const &key,
               Parent *parent)
  : Base(language, parent)
  , m_device(device)
  , m_key(key)
{
  setOverflow(Wt::WContainerWidget::OverflowAuto);
}

Widget::~Widget()
{
}

void Widget::setKey(Any const &k)
{
  m_key = k;
}

Widget::Device const &Widget::device() const
{
  return m_device;
}

Widget::Any const &Widget::key() const
{
  return m_key;
}


} // widget
} // site
