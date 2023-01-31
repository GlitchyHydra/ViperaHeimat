//#include "Vipera"
#include "hzpch.h"

#include "Window.h"

#include <shellapi.h> //For CommandLineToArgvW

#include <d3d11.h>
//#include <d3dx11.h>
//#include <d3dx10.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

IDXGISwapChain* swapchain;
ID3D11Device* dev;
ID3D11DeviceContext* devcon;

void InitD3D(HWND hWnd);
void CleanD3D(void);

ID3D11RenderTargetView* backbuffer;

void InitD3D(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = SCREEN_WIDTH;
    scd.BufferDesc.Height = SCREEN_HEIGHT;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;
    scd.Windowed = TRUE;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D_FEATURE_LEVEL pFeatureLevel;
    std::vector<D3D_FEATURE_LEVEL> featuresLevels = std::vector<D3D_FEATURE_LEVEL>{ D3D_FEATURE_LEVEL_11_0 };
    HRESULT hr = D3D11CreateDevice(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        D3D11_CREATE_DEVICE_DEBUG,
        &(*featuresLevels.begin()),
        featuresLevels.size(),
        D3D11_SDK_VERSION,
        &dev,
        &pFeatureLevel,
        &devcon);

    if (FAILED(hr))
    {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return;
    }

    IDXGIDevice* dxgiDevice = 0;
    dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);

    IDXGIAdapter* dxgiAdapter = 0;
    dxgiDevice->GetParent(__uuidof(IDXGIAdapter),
        (void**)& dxgiAdapter);

	// Finally got the IDXGIFactory interface.
	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory),
            (void**)& dxgiFactory);

    dxgiFactory->CreateSwapChain(dev,
        &scd,
        &swapchain);

    dxgiFactory->Release();
    dxgiAdapter->Release();
    dxgiDevice->Release();

    //ID3D11Device::CheckMultisampleQualityLevels(DXGI_FORMAT_)

    ID3D11Texture2D* pBackBuffer;
    swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

    //use
    dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
    pBackBuffer->Release();

    devcon->OMSetRenderTargets(1, &backbuffer, NULL);

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    devcon->RSSetViewports(1, &viewport);
}

// global
ID3D11VertexShader* pVs;    // the vertex shader
ID3D11PixelShader* pPs;     // the pixel shader
ID3D11InputLayout* pLayout;    // global

void InitPipeline()
{
    ID3D10Blob* Vs, * Ps;
    HRESULT hr = D3DCompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, &Vs, 0);
    hr = D3DCompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, &Ps, 0);

    // encapsulate both shaders into shader objects
    dev->CreateVertexShader(Vs->GetBufferPointer(), Vs->GetBufferSize(), NULL, &pVs);
    dev->CreatePixelShader(Ps->GetBufferPointer(), Ps->GetBufferSize(), NULL, &pPs);

    // set the shader objects
    devcon->VSSetShader(pVs, 0, 0);
    devcon->PSSetShader(pPs, 0, 0);

    // create the input layout object
    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    dev->CreateInputLayout(ied, 2, Vs->GetBufferPointer(), Vs->GetBufferSize(), &pLayout);
    devcon->IASetInputLayout(pLayout);
}
//DirectX::XMFLOAT4
struct VERTEX
{
    FLOAT X, Y, Z;
    float color[4];
};

ID3D11Buffer* pVBuffer;


void InitGraphics()
{
    VERTEX vertices[]
    {
        {0.0f, 0.5f, 0.0f, {1.0f, 0.0f, 0.0f, 1.0f}},
        {0.45f, -0.5, 0.0f, {0.0f, 1.0f, 0.0f, 1.0f}},
        {-0.45f, -0.5f, 0.0f, {0.0f, 0.0f, 1.0f, 1.0f}}
    };

    // create the vertex buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
    bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

    dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


    // copy the vertices into the buffer
    D3D11_MAPPED_SUBRESOURCE ms;
    devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
    memcpy(ms.pData, vertices, sizeof(vertices));                 // copy the data
    devcon->Unmap(pVBuffer, NULL);                           // unmap the buffer

    
}

void RenderFrame(void)
{
    const float a[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	devcon->ClearRenderTargetView(backbuffer, a);

    // select which vertex buffer to display
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;
    devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
    
    // select which primtive type we are using
    devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // draw the vertex buffer to the back buffer
    devcon->Draw(3, 0);

    swapchain->Present(0, 0);
}

void CleanD3D()
{
    swapchain->SetFullscreenState(FALSE, NULL);

    // close and release all existing COM objects
    pVs->Release();
    pPs->Release();
    swapchain->Release();
    backbuffer->Release();
    dev->Release();
    devcon->Release();
}


LRESULT CALLBACK WindowProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

    Vipera::Window window;
    window.init(hInstance);

    InitD3D(window.getHWND());

    InitPipeline();
    InitGraphics();

// display the window on the screen
    ShowWindow(window.getHWND(), nCmdShow);
    
    // this struct holds Windows event messages
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while (1)
    {
        bool isMessageReceived = PeekMessage(&msg,
            NULL,
            0,
            0,
            PM_REMOVE);

        if (isMessageReceived)
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
                break;
        }

        RenderFrame();
    }

    CleanD3D();

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}



