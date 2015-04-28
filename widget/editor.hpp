#ifndef DNW_WIDGET_EDITOR_HPP
#define DNW_WIDGET_EDITOR_HPP

#include "widget/widget.hpp"
#include "wt/stringresource.hpp"
#include <Wt/WInPlaceEdit>
#include <Wt/WResource>


namespace dnw {
  namespace widget {

    class Editor : public Widget {
    private:
      using InPlaceEdit    = Wt::WInPlaceEdit;
      using InPlaceEdits   = std::vector<InPlaceEdit *>;
      using TextEdit       = Wt::WTextEdit;
      using TextEdits      = std::vector<TextEdit *>;
      using Resource       = Wt::WResource;
      using Resources      = std::vector<Resource *>;
      using FileListJs     = wt::StringResource;
      using FileMap        = std::map<String, String>;

    public:
      explicit Editor(System const &system, Parent *parent = nullptr);
      virtual ~Editor();

    public:
      virtual void update() final;
      virtual void regenerate() final;

    public:
      Signal &itemChanged(); // TODO mustafa: should be change later

    private:
      void onCodes();
      void onFiles();

    private:
      // Save & upload
      void saveName(String const &languageTag, InPlaceEdit *edit);
      void saveContent(String const &languageTag, TextEdit *textEdit);
      void uploadContent(String const &languageTag, TextEdit *textEdit);
      void resetContent(String const &languageTag, TextEdit *textEdit);
      void pasteContent(String const &languageTag, TextEdit *textEdit);
      void pasteName(String const &languageTag, InPlaceEdit *inPlaceEdit);

    private:
      InPlaceEdits edits;
      TextEdits    textEdits;
      Resources    resources;
      FileListJs   imageListJs;
      FileListJs   linkListJs;
      FileMap      fileMap;
      Signal       itemChangedSignal;
    };

  }
}


#endif // DNW_WIDGET_EDITOR_HPP
