#include <Windows.h>

#include <Win32/DialogBase.h>

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE /*hPrevInstance*/, PWSTR /*pCmdLine*/, int /*nCmdShow*/)
{
  Win32::DialogBase d;
  const bool result = d.exec(hInstance);
  return result
      ? EXIT_SUCCESS
      : EXIT_FAILURE;
}
