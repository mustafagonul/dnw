#include "wt/stringresource.hpp"
#include <sstream>


namespace dnw {
namespace wt {


using Stream = std::istringstream;


StringResource::StringResource(Parent *parent)
  : Wt::WStreamResource(parent)
  , m_string()
{
}

StringResource::~StringResource()
{
  beingDeleted();
}

void StringResource::handleRequest(Wt::Http::Request const &request, Wt::Http::Response &response)
{
  Stream stream(m_string);

  handleRequestPiecewise(request, response, stream);
}

void StringResource::setString(String const &str)
{
  m_string = str;

  setChanged();
}


} // wt
} // dnw
