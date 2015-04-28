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

#ifndef DNW_WIDGET_ADMIN_HPP
#define DNW_WIDGET_ADMIN_HPP

#include "widget/decorator.hpp"


namespace dnw {
  namespace widget {

    class Admin : public Decorator {
    public:
      explicit Admin(System const &system, Parent *parent = nullptr);
      virtual ~Admin();

    public:
      virtual void update() final;
      virtual void regenerate() final;

    public:
      Signal &itemChanged(); // TODO mustafa: should be change later

    private:
      // Child commands
      void addNode();
      void removeNode();
      void moveNodeUp();
      void moveNodeDown();

      // File commands
      void addFile();
      void removeFile();
      void moveFile();

      // Code commands
      void addCode();
      void removeCode();
      void moveCode();

      // Config commands
      void nodeConfig();
      void globalConfig();

      // Widgets
      void editor();
      void suspicious();

    private:
      Signal itemChangedSignal;
    };

  }
}

#endif // DNW_WIDGET_ADMIN_HPP

