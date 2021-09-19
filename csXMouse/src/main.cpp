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

#include "XMouseRes.h"
#include "Win32/SysParam.h"

#include "XMouse.h"

#if 0
bool isChecked(HWND check)
{
  return SendMessageW(check, BM_GETCHECK, 0, 0) == BST_CHECKED;
}

void setChecked(HWND check, const bool on)
{
  const WPARAM wParam = on
      ? BST_CHECKED
      : BST_UNCHECKED;
  SendMessageW(check, BM_SETCHECK, wParam, 0);
}

void toggleChecked(HWND check)
{
  if( isChecked(check) ) {
    setChecked(check, false);
  } else {
    setChecked(check, true);
  }
}

bool registerWindowClass(HINSTANCE instance)
{
  WNDCLASSEXW wcex;
  if( GetClassInfoExW(instance, WNDCLASS_NAME_csXMouse, &wcex) != FALSE ) {
    return true; // Window class is already registered!
  }

  wcex.cbSize        = sizeof(WNDCLASSEXW);
  wcex.style         = 0;
  wcex.lpfnWndProc   = DefDlgProcW;
  wcex.cbClsExtra    = 0;
  wcex.cbWndExtra    = DLGWINDOWEXTRA + sizeof(LONG_PTR);
  wcex.hInstance     = instance;
  wcex.hIcon         = LoadIconW(instance, MAKEINTRESOURCEW(IDI_csXMouse));
  wcex.hCursor       = LoadCursorW(nullptr, IDC_ARROW);
  wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
  wcex.lpszMenuName  = nullptr;
  wcex.lpszClassName = WNDCLASS_NAME_csXMouse;
  wcex.hIconSm       = LoadIconW(instance, MAKEINTRESOURCEW(IDI_csXMouse));

  if( RegisterClassExW(&wcex) == 0 ) {
    MessageBoxW(nullptr, L"RegisterClassExW()", L"Error",
                MB_ICONERROR | MB_OK);
    return false;
  }

  return true;
}

INT_PTR CALLBACK DialogProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch( msg ) {
  case WM_INITDIALOG:
    setChecked(GetDlgItem(wnd, IDC_ActWndTrk), Win32::getActiveWindowTracking());
    setChecked(GetDlgItem(wnd, IDC_ActWndTrkZOrd), Win32::getActiveWindowTrackingZOrder());
    return TRUE;

  case WM_COMMAND:

    /*
     * HIWORD(wParam) == Control-defined notification code
     * LOWORD(wParam) == Control identifier
     */

    if(        LOWORD(wParam) == IDOK ) {
      Win32::setActiveWindowTracking(isChecked(GetDlgItem(wnd, IDC_ActWndTrk)));
      Win32::setActiveWindowTrackingZOrder(isChecked(GetDlgItem(wnd, IDC_ActWndTrkZOrd)));
      EndDialog(wnd, IDOK);
      return TRUE;

    } else if( LOWORD(wParam) == IDCANCEL ) {
      EndDialog(wnd, IDCANCEL);
      return TRUE;

    } else if( LOWORD(wParam) == IDC_ActWndTrk ) {
      toggleChecked(GetDlgItem(wnd, IDC_ActWndTrk));
      return TRUE;

    } else if( LOWORD(wParam) == IDC_ActWndTrkZOrd ) {
      toggleChecked(GetDlgItem(wnd, IDC_ActWndTrkZOrd));
      return TRUE;

    }

    break; // WM_COMMAND

  default:
    break;
  }

  return FALSE;
}
#endif

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/,
                      LPWSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
#if 1
  // Win32::DialogBase d;
  XMouse d;
  const bool result = d.exec(hInstance);
#else
  if( !registerWindowClass(hInstance) ) {
    return EXIT_FAILURE;
  }

  const bool result = DialogBoxParamW(hInstance, MAKEINTRESOURCEW(IDD_csXMouse), nullptr,
                                      DialogProc, 0) == IDOK;
#endif

  return result
      ? EXIT_SUCCESS
      : EXIT_FAILURE;
}
