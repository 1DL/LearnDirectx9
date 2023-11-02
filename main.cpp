#include <Windows.h> //Header basico da api win32

// Ponto inicial da aplicação. Toda aplicação win32 usa função WinMain ao invés de main
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // cria janela com hello world e OK
    MessageBox(nullptr, L"Hello, World!", L"Título da Janela", MB_ICONEXCLAMATION | MB_OK);

    // returna 0 ao Windows
    return 0;
}