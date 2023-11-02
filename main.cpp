#include <windows.h> //Header basico da api win32
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //referencia para a janela, preenchido por uma fun��o
    HWND hWnd;
    //essa struct armazena informa��o para a classe da janela
    WNDCLASSEX wc;

    //Limpa a classe da janela para ser utilizada
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    //Preenche a struct com as informa��es necess�rias
    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = WindowProc;
    wc.hInstance        = hInstance;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName    = L"WindowClass1";
    
    // Registra a classe da janela
    RegisterClassEx(&wc);

    // Cria a janela e usa o resultado como referencia pra ela

    hWnd = CreateWindowEx(
        NULL,
        L"WindowClass1",                            //Nome da classe da janela
        L"Nosso primeiro programa com janelas",     //T�tulo da janela
        WS_OVERLAPPEDWINDOW,                        //Estilo da Janela
        300,                                        //Posi��o x da janela
        300,                                        //Posi��o y da janela
        500,                                        //Largura da Janela
        400,                                        //Altura da Janela
        NULL,                                       //N�o tem janela pai, NULL
        NULL,                                       //N�o ir� criar menus, NULL
        hInstance,                                  // referencia para a aplica��o
        NULL                                        // Usado com v�rias janelas, NUL
        );

    //Exibe a janela na tela
    ShowWindow(hWnd, nCmdShow);

    //Entra no main loop

    //Essa struct armazena as mensagens de eventos do windows
    MSG msg;

    //Espera pela pr�xima mensagem na fila, armazena o resultado em 'msg';
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //transcreve mensagens de keystroke para o formato correto
        TranslateMessage(&msg);

        //Envia a mensagem para a fun��o WindowProc
        DispatchMessage(&msg);
    }

    // Retorna a parte da mensagem VM_QUIT para o Windows
    return msg.wParam;
}

//Este � o principal gerenciador de mensagens para o programa
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    //Essa mensagem � lida quando a janela � fechada
    case WM_DESTROY:
        //Encerra a aplica��o totalmente
        PostQuitMessage(0);
        return 0;
        break;
    }

    //Trata todas as mensagens que n�o foram gerenciadas no Switch
    return DefWindowProc(hWnd, message, wParam, lParam);
}