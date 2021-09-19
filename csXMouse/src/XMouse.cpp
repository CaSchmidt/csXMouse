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

#include <Windows.h>

#include "Win32/CheckBox.h"
#include "Win32/SysParam.h"

#include "XMouse.h"

#include "XMouseRes.h"

////// public ////////////////////////////////////////////////////////////////

XMouse::XMouse() noexcept
  : Win32::DialogBase()
{
}

XMouse::~XMouse() noexcept
{
}

Win32::lresult_t XMouse::onInitDialog(Win32::hwnd_t wnd, Win32::lparam_t lParam)
{
  _controls.emplace_back(Win32::CheckBox::create(wnd, IDC_ActWndTrk));
  _controls.emplace_back(Win32::CheckBox::create(wnd, IDC_ActWndTrkZOrd));
  Win32::CHECKBOX(getControl(IDC_ActWndTrk))->setChecked(Win32::getActiveWindowTracking());
  Win32::CHECKBOX(getControl(IDC_ActWndTrkZOrd))->setChecked(Win32::getActiveWindowTrackingZOrder());
  return Win32::DialogBase::onInitDialog(wnd, lParam);
}

Win32::lresult_t XMouse::onOk(Win32::wparam_t /*wParam*/, Win32::lparam_t /*lParam*/)
{
  Win32::setActiveWindowTracking(Win32::CHECKBOX(getControl(IDC_ActWndTrk))->isChecked());
  Win32::setActiveWindowTrackingZOrder(Win32::CHECKBOX(getControl(IDC_ActWndTrkZOrd))->isChecked());
  return TRUE;
}

////// protected /////////////////////////////////////////////////////////////

const wchar_t *XMouse::dialogName() const
{
  return MAKEINTRESOURCEW(IDD_XMouse);
}

const wchar_t *XMouse::iconName() const
{
  return MAKEINTRESOURCEW(IDI_XMouse);
}

const wchar_t *XMouse::wndClassName() const
{
  return WNDCLASS_XMouse;
}
