#ifndef DNW_UTILITY_RESULT_HPP
#define DNW_UTILITY_RESULT_HPP

#include <string>
#include <vector>
#include <boost/any.hpp>


namespace dnw {
  namespace utility {

    class Result {
    private:
      using String = std::string;
      using Message = String;
      using Messages = std::vector<Message>;
      using Index = Messages::size_type;
      using Iterator = Messages::const_iterator;
      using Any = boost::any;

    public:
      explicit Result(Message const &msg);
      explicit Result(Any const &key);

      Result();

      // TODO mustafa: special functions, move constructors.

    public:
      bool check() const;
      void add(Message const &msg);
      void add(Result const &result);
      void clear();
      void setKey(Any const &any);

      Any const &key() const;
      Index      count() const;
      Message    message(Index index) const;
      String     all(String const &delimeter) const;

      Iterator begin() const { m_messages.cbegin(); }
      Iterator end() const   { m_messages.cend();   }

    public:
      operator bool() const                     { return check();        }
      bool operator()() const                   { return check();        }

      Message operator() (Index index) const    { return message(index); }
      Message operator[] (Index index) const    { return message(index); }

      void operator +=(Message const &msg)      { add(msg);              }
      void operator +=(Result const &result)    { add(result);           }

    private:
      Messages m_messages;
      Any      m_key;
    };

  }
}


#endif // DNW_UTILITY_RESULT_HPP
