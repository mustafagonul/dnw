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

#ifndef DNW_UTILITY_API_HPP
#define DNW_UTILITY_API_HPP


// Here detecting environment
#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__ || defined __MINGW64__
  #define DNW_WINDOWS_ENVIRONMENT
#else
  #define DNW_XNIX_ENVIRONMENT
#endif


// Here is the windows side
#ifdef DNW_WINDOWS_ENVIRONMENT
  #ifdef __GNUC__
    #define DNW_EXPORT __attribute__ ((dllexport))
    #define DNW_IMPORT __attribute__ ((dllimport))
  #else
    #define DNW_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #define DNW_IMPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
  #endif

  #define DNW_HIDDEN
#endif


// Here is the *nix side
#ifdef DNW_XNIX_ENVIRONMENT
  #if __GNUC__ >= 4
    #define DNW_EXPORT __attribute__ ((visibility ("default")))
    #define DNW_IMPORT __attribute__ ((visibility ("default")))
    #define DNW_HIDDEN __attribute__ ((visibility ("hidden")))
  #else
    #define DNW_EXPORT
    #define DNW_IMPORT
    #define DNW_HIDDEN
  #endif
#endif


// Api
#ifdef DNW_EXECUTABLE
  #define DNW_API DNW_IMPORT
#else
  #define DNW_API DNW_EXPORT
#endif


#endif // DNW_UTILITY_API_HPP
