#include <Windows.h> //Header basico da api win32

// Ponto inicial da aplica��o. Toda aplica��o win32 usa fun��o WinMain ao inv�s de main
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    // cria janela com hello world e OK
    MessageBox(nullptr, L"Hello, World!", L"T�tulo da Janela", MB_ICONEXCLAMATION | MB_OK);

    // returna 0 ao Windows
    return 0;
}