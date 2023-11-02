#include <windows.h> //Header basico da api win32
#include <windowsx.h>
#include <d3d9.h>

//Declara��es Globais
LPDIRECT3D9EX d3d;              //pointer para interface do Direct3D
LPDIRECT3DDEVICE9EX d3ddev;     //pointer para a classe do device

//Declara��o de fun��es
bool initD3D(HWND hWnd);        // prepara e inicializa o Direct3D
void render_frame(void);        // renderiza um �nico frame
void cleanD3D(void);             // encerra o Direct3D e libera a mem�ria

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow) 
{
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

    //Prepara e inicializa o Direct3D
    if (!initD3D(hWnd)) {
        cleanD3D();
        MessageBox(hWnd, L"Inicializa��o do Direct3D Falhou!!!", L"Erro Direct3D9Ex", MB_OK);
        return 0;
    };

    //Entra no main loop

    //Essa struct armazena as mensagens de eventos do windows
    MSG msg;

    //Entra no loop infinito de mensagens
    while (true)
    {
        //Verifica se existe alguma mensagem esperando na fila
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //transcreve mensagens de keystroke para o formato correto
            TranslateMessage(&msg);

            //Despacha a mensagem para a fun��o WindowProc
            DispatchMessage(&msg);
        }

        //Se a mensagem � WM_QUIT, sai do loop infinito
        if (msg.message == WM_QUIT)
            break;

        //C�digo do jogo aqui...
        render_frame();

    }

    //Limpa o DirectX e COM
    cleanD3D();
  

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

//Essa fun��o prepara e inicializa o Direct3D para ser usado
bool initD3D(HWND hWnd)
{
    // Create the Direct3D 9Ex interface.
    HRESULT result = Direct3DCreate9Ex(D3D_SDK_VERSION, &d3d);
    if (result != D3D_OK) {
        // Handle the error, perhaps by logging or showing an error message.
        // For example:
        MessageBox(hWnd, L"Failed to create Direct3D 9Ex interface.", L"Error", MB_OK);
        return false;
    }

    D3DPRESENT_PARAMETERS d3dpp{};          // cria a struct que armazena as diversas informa��es da placa de video

    //ZeroMemory(&d3dpp, sizeof(d3dpp));    // Limpa a mem�ria da struct para ser usada (desnecess�rio por inicializado com {} j� zera)

    d3dpp.Windowed = TRUE;                      //aplica��o em modo janela, n�o tela cheia
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;   // descarta frames antigos
    d3dpp.hDeviceWindow = hWnd;                 // define qual janela ser� usada pelo Direct3D

    //Cria a classe de device usando a informa��o aqui fornecida e da struct d3dpp

    result = d3d->CreateDeviceEx(
        D3DADAPTER_DEFAULT,
        D3DDEVTYPE_HAL,
        hWnd,
        D3DCREATE_HARDWARE_VERTEXPROCESSING,
        &d3dpp,
        NULL, // This should be NULL unless you are using a D3DDISPLAYMODEEX structure.
        &d3ddev
    );

    if (result != D3D_OK) {
        // Handle the error, perhaps by logging or showing an error message.
        // For example:
        MessageBox(hWnd, L"Failed to create Direct3D 9Ex device.", L"Error", MB_OK);
        return false;
    }

    return true;
}

// Essa e a fun��o que ir� renderizar um �nico frame
void render_frame(void)
{
    // limpa a janela com a cor azul
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

    d3ddev->BeginScene();   //Inicia a cena 3d

    //Realiza as renderiza��es no backbuffer aqui

    d3ddev->EndScene();     //Finaliza a cena 3d

    d3ddev->PresentEx(NULL, NULL, NULL, NULL, 0);
}

// Essa � a fun��o que limpa o Direct3D e COM
void cleanD3D(void)
{
    d3ddev->Release();      //Fecha e libera o dispositivo 3d
    d3d->Release();         //Fecha e libera o Direct3D
}