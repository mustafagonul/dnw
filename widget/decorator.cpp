#include "widget/decorator.hpp"


namespace dnw {
namespace widget {


Decorator::Decorator(System const &system, Parent *parent)
  : Widget(system, parent)
  , container(nullptr)
  , widget(nullptr)
{
  container = new Container;
  container->setOverflow(Container::OverflowAuto);
}

Decorator::~Decorator()
{
  if (container) {
    removeWidget(container);
    delete container;
  }
}

void Decorator::update()
{
  if (widget)
    widget->update();
}

void Decorator::regenerate()
{
  if (widget)
    widget->regenerate();
}

void Decorator::clear()
{
  removeWidget(container);

  Widget::clear();
}

void Decorator::addContainer()
{
  addWidget(container);
}

void Decorator::setWidget(Widget *w)
{
  container->clear();
  widget = w;

  if (widget) {
    container->addWidget(widget);
    widget->update();
  }
}


} // widget
} // dnw

