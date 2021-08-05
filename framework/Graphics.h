//
// Created by draven on 6/6/2021.
//

// https://github.com/hailzfn/IGodsEye-Reborn/blob/master/Game/Graphics/Graphics.h

#pragma once

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx12.h"
#include <d3d12.h>
#include <dxgi1_4.h>

struct FrameContext
{
    ID3D12CommandAllocator* CommandAllocator = nullptr;
    UINT64                  FenceValue = 0;
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class graphics
{
public:
    static void start(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue);
    static void stop();
    static void newFrame();
    static HRESULT render(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags);
    static void clear();
    static void clearVariables();
private:
    static void startD3D12(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue);
    static void restart(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue);

    static FrameContext* waitForNextFrameResources();
    static DXGI_SWAP_CHAIN_DESC1 getSwapchainDesc();
    static void createCbvDescriptorHeap();
    static void createRtvDescriptorHeap();
    static void createFence();
    static void createCommandAllocator();
    static void getDescriptors();
    static void createCommandList();
    static void createRenderTarget();
public:
    static bool started;
    static bool needsRestart;
    static IDXGISwapChain3* g_pSwapChain;
    static ID3D12CommandQueue* g_pCommandQueue;
private:
    static ImFont* font;
    static ID3D12Device* g_pDevice;
    static ID3D12DescriptorHeap* g_pRtvDescHeap;
    static ID3D12DescriptorHeap* g_pSrvDescHeap;
    static ID3D12Fence* g_pFence;
    static FrameContext* g_frameContext;
    static ID3D12Resource** g_resources;
    static D3D12_CPU_DESCRIPTOR_HANDLE* g_descriptors;
    static HANDLE g_waitableObject;
    static HANDLE g_FenceEvent;
    static UINT g_frameCount;
    static UINT g_frameIndex;
    static UINT64 g_fenceLastSignalValue;
    static ID3D12GraphicsCommandList* g_pCommandList;
};

