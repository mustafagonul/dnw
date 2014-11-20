#ifndef DNW_UTILITY_TYPES_HPP
#define DNW_UTILITY_TYPES_HPP

#include <string>
#include <vector>
#include <boost/any.hpp>


namespace dnw {

  using Index = std::size_t;
  using Indices = std::vector<Index>;
  using String = std::string;
  using Strings = std::vector<std::string>;
  using Any = boost::any;

}


#endif // DNW_UTILITY_TYPES_HPP
