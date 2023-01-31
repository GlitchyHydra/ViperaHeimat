#pragma once

#include <wrl.h>


#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
// D3D12 extension library.
//#include <d3dx12.h>

const uint8_t g_NumFrames = 3;
bool g_UseWarp = false;
uint32_t g_ClientWidth = 1280;
uint32_t g_ClientHeight = 720;

bool g_IsInitialized = false;

HWND g_hWnd;
RECT g_WindowRect;

#include <wrl.h>

Microsoft::WRL::ComPtr<ID3D12Device2> g_Device;
Microsoft::WRL::ComPtr<ID3D12CommandQueue> g_CommandQueue;
Microsoft::WRL::ComPtr<IDXGISwapChain4> g_SwapChain;
Microsoft::WRL::ComPtr<ID3D12Resource> g_BackBuffers[g_NumFrames];
Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> g_CommandList;
Microsoft::WRL::ComPtr<ID3D12CommandAllocator> g_CommandAllocators[g_NumFrames];
Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> g_RTVDescriptorHeap;

UINT g_RTVDescriptorSize;
UINT g_CurrentBackBufferIndex;

Microsoft::WRL::ComPtr <ID3D12Fence> g_Fence;

uint64_t g_FenceValue = 0;
uint64_t g_FrameFenceValues[g_NumFrames]{};
HANDLE g_FenceEvent;