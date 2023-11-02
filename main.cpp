#include <windows.h> //Header basico da api win32
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //referencia para a janela, preenchido por uma função
    HWND hWnd;
    //essa struct armazena informação para a classe da janela
    WNDCLASSEX wc;

    //Limpa a classe da janela para ser utilizada
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    //Preenche a struct com as informações necessárias
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
        L"Nosso primeiro programa com janelas",     //Título da janela
        WS_OVERLAPPEDWINDOW,                        //Estilo da Janela
        300,                                        //Posição x da janela
        300,                                        //Posição y da janela
        500,                                        //Largura da Janela
        400,                                        //Altura da Janela
        NULL,                                       //Não tem janela pai, NULL
        NULL,                                       //Não irá criar menus, NULL
        hInstance,                                  // referencia para a aplicação
        NULL                                        // Usado com várias janelas, NUL
        );

    //Exibe a janela na tela
    ShowWindow(hWnd, nCmdShow);

    //Entra no main loop

    //Essa struct armazena as mensagens de eventos do windows
    MSG msg;

    //Espera pela próxima mensagem na fila, armazena o resultado em 'msg';
    while (GetMessage(&msg, NULL, 0, 0))
    {
        //transcreve mensagens de keystroke para o formato correto
        TranslateMessage(&msg);

        //Envia a mensagem para a função WindowProc
        DispatchMessage(&msg);
    }

    // Retorna a parte da mensagem VM_QUIT para o Windows
    return msg.wParam;
}

//Este é o principal gerenciador de mensagens para o programa
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    //Essa mensagem é lida quando a janela é fechada
    case WM_DESTROY:
        //Encerra a aplicação totalmente
        PostQuitMessage(0);
        return 0;
        break;
    }

    //Trata todas as mensagens que não foram gerenciadas no Switch
    return DefWindowProc(hWnd, message, wParam, lParam);
}