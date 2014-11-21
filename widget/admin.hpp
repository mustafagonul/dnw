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

#include "widget/widget.hpp"
#include <Wt/WInPlaceEdit>


namespace dnw {
  namespace widget {

    class Admin : public Widget {
    private:
      using InPlaceEdit    = Wt::WInPlaceEdit;
      using TextEdit       = Wt::WTextEdit;

    public:
      Admin(Device const &device,
            String const &language,
            Any const &key,
            Parent *parent = nullptr);
      virtual ~Admin();

    public:
      virtual void update();

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

      // Save
      void saveLeftName();
      void saveRightName();
      void saveLeftContent();
      void saveRightContent();

      // Resources
      void onCodes();
      void onFiles();



    private:
      InPlaceEdit *leftEdit;
      InPlaceEdit *rightEdit;
      TextEdit    *leftTextEdit;
      TextEdit    *rightTextEdit;
    };

  }
}

#endif // DNW_WIDGET_ADMIN_HPP
