/****************************************************************************
** Copyright (c) 2021, Carsten Schmidt. All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
**
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** 3. Neither the name of the copyright holder nor the names of its
**    contributors may be used to endorse or promote products derived from
**    this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/

#ifndef WIN32_TYPES_H
#define WIN32_TYPES_H

#include <cstdint>

#include <typeinfo>

/*
 * cf. [MS-DTYP]: Windows Data Types
 * cf. https://docs.microsoft.com/en-us/windows/win32/winprog/windows-data-types
 */

namespace Win32 {

  namespace impl {

    template<typename Type32, typename Type64, std::size_t N>
    struct option3264 {
      // SFINAE
    };

    template<typename Type32, typename Type64>
    struct option3264<Type32,Type64,4> {
      using type = Type32;
    };

    template<typename Type32, typename Type64>
    struct option3264<Type32,Type64,8> {
      using type = Type64;
    };

    template<typename Type32, typename Type64>
    struct select3264 {
      using type = typename option3264<Type32,Type64,sizeof(void*)>::type;
    };

  } // namespace impl

  using long_ptr_t = impl::select3264<int32_t,int64_t>::type;

  using uint_t = unsigned int;

  using uint_ptr_t = impl::select3264<uint32_t,uint64_t>::type;

  // Handles /////////////////////////////////////////////////////////////////

  using    handle_t = void*;
  using hinstance_t = handle_t;
  using      hwnd_t = handle_t;

  // Message Handling ////////////////////////////////////////////////////////

  using  lparam_t = long_ptr_t;
  using lresult_t = long_ptr_t;
  using  wparam_t = uint_ptr_t;

} // namespace Win32

#endif // WIN32_TYPES_H
