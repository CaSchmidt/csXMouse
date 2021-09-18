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

#ifndef WINDOW_H
#define WINDOW_H

#include <list>
#include <memory>

#include "Win32/Types.h"

namespace Win32 {

  using WindowPtr = std::unique_ptr<class Window>;

  class Window {
  public:
    virtual ~Window() noexcept;

    bool isNull() const;

    hwnd_t handle() const;

    int controlId() const;

    lresult_t sendMessage(uint_t msg, wparam_t wParam, lparam_t lParam) const;

    long_ptr_t userData() const;
    void setUserData(long_ptr_t data);

    virtual lresult_t onCommand(wparam_t wParam, lparam_t lParam); // WM_COMMAND

  protected:
    Window(hwnd_t wnd) noexcept;
    Window(hwnd_t dlg, int idDlgItem) noexcept;

    void setHandle(hwnd_t wnd);

  private:
    hwnd_t _wnd{nullptr};
  };

  using Windows = std::list<WindowPtr>;

} // namespace Win32

#endif // WINDOW_H
