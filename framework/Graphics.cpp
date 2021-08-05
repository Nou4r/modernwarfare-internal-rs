//
// Created by draven on 6/6/2021.
//

// https://github.com/hailzfn/IGodsEye-Reborn/blob/master/Game/Graphics/Graphics.cpp

#include <string>

#include "Graphics.h"
#include "Hooks.h"
#include "Debug.h"
#include "Framework.h"
#include "Interop.h"

bool graphics::started = false;
bool graphics::needsRestart = false;
ImFont* graphics::font = nullptr;
IDXGISwapChain3* graphics::g_pSwapChain = nullptr;
ID3D12CommandQueue* graphics::g_pCommandQueue = nullptr;
ID3D12Device* graphics::g_pDevice = nullptr;
ID3D12DescriptorHeap* graphics::g_pRtvDescHeap = nullptr;
ID3D12DescriptorHeap* graphics::g_pSrvDescHeap = nullptr;
ID3D12Fence* graphics::g_pFence = nullptr;
FrameContext* graphics::g_frameContext = nullptr;
ID3D12Resource** graphics::g_resources = nullptr;
D3D12_CPU_DESCRIPTOR_HANDLE* graphics::g_descriptors = nullptr;
HANDLE graphics::g_waitableObject = NULL;
HANDLE graphics::g_FenceEvent = NULL;
UINT graphics::g_frameCount = 0;
UINT graphics::g_frameIndex = 0;
UINT64 graphics::g_fenceLastSignalValue = 0;
ID3D12GraphicsCommandList* graphics::g_pCommandList = nullptr;

static void initImguiTheme() noexcept
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
    colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
    colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
//    colors[ImGuiCol_WindowShadow] = ImColor(0, 0, 0);

    style->ChildRounding = 4.0f;
    style->FrameBorderSize = 1.0f;
    style->FrameRounding = 2.0f;
    style->GrabMinSize = 7.0f;
    style->PopupRounding = 2.0f;
    style->ScrollbarRounding = 12.0f;
    style->ScrollbarSize = 13.0f;
    style->TabBorderSize = 1.0f;
    style->TabRounding = 0.0f;
    style->WindowRounding = 4.0f;
}

void graphics::start(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue)
{
    if (!graphics::started) {
        // Init graphics
        graphics::startD3D12(pSwapChain, pCommandQueue);

        // Setup imgui context
        IMGUI_CHECKVERSION();
        const auto ctx = ImGui::CreateContext();

        // Setup Platform/Renderer bindings
        ImGui_ImplWin32_Init(hooks->gameWindow);
        ImGui_ImplDX12_Init(graphics::g_pDevice, graphics::g_frameCount,
                            DXGI_FORMAT_R8G8B8A8_UNORM, graphics::g_pSrvDescHeap,
                            graphics::g_pSrvDescHeap->GetCPUDescriptorHandleForHeapStart(),
                            graphics::g_pSrvDescHeap->GetGPUDescriptorHandleForHeapStart());

        initImguiTheme();
        interop::on_imgui_init(ctx);

        hooks->hookWndProc();

        graphics::started = true;
    } else {
        if (graphics::needsRestart) {
            graphics::restart(pSwapChain, pCommandQueue);
            graphics::needsRestart = false;
        }
    }
}

void graphics::startD3D12(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue)
{
    graphics::g_pSwapChain = pSwapChain;
    graphics::g_pCommandQueue = pCommandQueue;

    // Get the device
    if (FAILED(graphics::g_pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**) &graphics::g_pDevice)))
        DEBUG_ERROR("1");

    // Get the swap chain description
    DXGI_SWAP_CHAIN_DESC1 sdesc = graphics::getSwapchainDesc();

    graphics::g_frameCount = sdesc.BufferCount;

    // Create the RTV descriptor heap
    graphics::createRtvDescriptorHeap();

    // Create the CBV descriptor heap
    graphics::createCbvDescriptorHeap();

    // Create fence
    graphics::createFence();

    // ALlocate frame context
    graphics::g_frameContext = new FrameContext[graphics::g_frameCount];
    graphics::g_resources = new ID3D12Resource* [graphics::g_frameCount];
    graphics::g_descriptors = new D3D12_CPU_DESCRIPTOR_HANDLE[graphics::g_frameCount];

    // Create the command allocator
    graphics::createCommandAllocator();

    // Get descriptors
    graphics::getDescriptors();

    // Create the command list
    graphics::createCommandList();

    // Waitable Object
    graphics::g_waitableObject = graphics::g_pSwapChain->GetFrameLatencyWaitableObject();

    // Create event
    graphics::g_FenceEvent = CreateEvent(nullptr, false, false, nullptr);
    if (graphics::g_FenceEvent == NULL)
        DEBUG_ERROR("7");

    // Create render target
    graphics::createRenderTarget();
}

void graphics::restart(IDXGISwapChain3* pSwapChain, ID3D12CommandQueue* pCommandQueue)
{
    graphics::startD3D12(pSwapChain, pCommandQueue);
    ImGui_ImplDX12_CreateDeviceObjects();
}

void graphics::stop()
{
    delete graphics::g_frameContext;
}

void graphics::newFrame()
{
    // Start the frame
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

HRESULT graphics::render(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
    // Rendering
    FrameContext* frameCtxt = graphics::waitForNextFrameResources();

    UINT backBufferIdx = graphics::g_pSwapChain->GetCurrentBackBufferIndex();

    frameCtxt->CommandAllocator->Reset();

    {
        static D3D12_RESOURCE_BARRIER barrier = {};
        barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
        barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
        barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
        barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
        barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
        barrier.Transition.pResource = graphics::g_resources[backBufferIdx];
        graphics::g_pCommandList->Reset(frameCtxt->CommandAllocator, nullptr);
        graphics::g_pCommandList->ResourceBarrier(1, &barrier);
        graphics::g_pCommandList->OMSetRenderTargets(1, &graphics::g_descriptors[backBufferIdx], FALSE, nullptr);
        graphics::g_pCommandList->SetDescriptorHeaps(1, &graphics::g_pSrvDescHeap);
    }

    ImGui::Render();
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), graphics::g_pCommandList);

    static D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.pResource = graphics::g_resources[backBufferIdx];

    graphics::g_pCommandList->ResourceBarrier(1, &barrier);
    graphics::g_pCommandList->Close();

    graphics::g_pCommandQueue->ExecuteCommandLists(1, (ID3D12CommandList* const*) &graphics::g_pCommandList);

    HRESULT result = hooks->originalPresent(pSwapChain, SyncInterval, Flags);

    UINT64 fenceValue = graphics::g_fenceLastSignalValue + 1;
    graphics::g_pCommandQueue->Signal(graphics::g_pFence, fenceValue);
    graphics::g_fenceLastSignalValue = fenceValue;
    frameCtxt->FenceValue = fenceValue;

    return result;
}

void graphics::clear()
{
    if (graphics::g_frameContext == nullptr)
        return;

    FrameContext* frameCtxt = &graphics::g_frameContext[graphics::g_frameIndex % graphics::g_frameCount];

    UINT64 fenceValue = frameCtxt->FenceValue;

    // No fence was signaled
    if (fenceValue == 0)
        return;

    frameCtxt->FenceValue = 0;

    if (graphics::g_pFence->GetCompletedValue() < fenceValue) {
        graphics::g_pFence->SetEventOnCompletion(fenceValue, graphics::g_FenceEvent);
        WaitForSingleObject(graphics::g_FenceEvent, INFINITE);
    }

    graphics::clearVariables();
}

void graphics::clearVariables()
{
    graphics::g_pSwapChain = nullptr;
    graphics::g_pDevice = nullptr;
    graphics::g_pCommandQueue = nullptr;

    if (graphics::g_pFence != nullptr) {
        graphics::g_pFence->Release();
        graphics::g_pFence = nullptr;
    }

    if (graphics::g_pSrvDescHeap != nullptr) {
        graphics::g_pSrvDescHeap->Release();
        graphics::g_pSrvDescHeap = nullptr;
    }

    if (graphics::g_pRtvDescHeap != nullptr) {
        graphics::g_pRtvDescHeap->Release();
        graphics::g_pRtvDescHeap = nullptr;
    }

    if (graphics::g_pCommandList != nullptr) {
        graphics::g_pCommandList->Release();
        graphics::g_pCommandList = nullptr;
    }

    if (graphics::g_frameContext != nullptr) {
        for (UINT i = 0; i < graphics::g_frameCount; ++i) {
            if (graphics::g_frameContext[i].CommandAllocator != nullptr) {
                graphics::g_frameContext[i].CommandAllocator->Release();
                graphics::g_frameContext[i].CommandAllocator = nullptr;
            }
        }

        delete[] graphics::g_frameContext;
        graphics::g_frameContext = nullptr;
    }

    if (graphics::g_resources != nullptr) {
        for (UINT i = 0; i < graphics::g_frameCount; ++i) {
            if (graphics::g_resources[i] != nullptr) {
                graphics::g_resources[i]->Release();
                graphics::g_resources[i] = nullptr;
            }
        }

        delete[] graphics::g_resources;
        graphics::g_resources = nullptr;
    }

    if (graphics::g_descriptors != nullptr) {
        delete[] graphics::g_descriptors;
        graphics::g_descriptors = nullptr;
    }

    graphics::g_waitableObject = nullptr;

    if (graphics::g_FenceEvent) {
        CloseHandle(graphics::g_FenceEvent);
        graphics::g_FenceEvent = nullptr;
    }

    graphics::g_frameCount = 0;
    graphics::g_frameIndex = 0;
}

FrameContext* graphics::waitForNextFrameResources()
{
    graphics::g_frameIndex++;

    HANDLE waitableObjects[] = {graphics::g_waitableObject, NULL};
    constexpr DWORD numWaitableObjects = 1;

    FrameContext* frameCtxt = &graphics::g_frameContext[graphics::g_frameIndex % graphics::g_frameCount];
    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);
    return frameCtxt;
}

DXGI_SWAP_CHAIN_DESC1 graphics::getSwapchainDesc()
{
    DXGI_SWAP_CHAIN_DESC1 sdesc;
    graphics::g_pSwapChain->GetDesc1(&sdesc);
    return sdesc;
}

void graphics::createRtvDescriptorHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC descriptorBackBuffers;
    descriptorBackBuffers.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    descriptorBackBuffers.NumDescriptors = graphics::g_frameCount;
    descriptorBackBuffers.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    descriptorBackBuffers.NodeMask = 1;

    if (FAILED(graphics::g_pDevice->CreateDescriptorHeap(&descriptorBackBuffers, IID_PPV_ARGS(&g_pRtvDescHeap))))
        DEBUG_ERROR("2");
}

void graphics::createCbvDescriptorHeap()
{
    D3D12_DESCRIPTOR_HEAP_DESC desc = {};
    desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    desc.NumDescriptors = 1;
    desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    desc.NodeMask = 0;

    if (FAILED(graphics::g_pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pSrvDescHeap))))
        DEBUG_ERROR("3");
}

void graphics::createFence()
{
    if (FAILED(graphics::g_pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&g_pFence))))
        DEBUG_ERROR("4");
}

void graphics::createCommandAllocator()
{
    for (size_t i = 0; i < graphics::g_frameCount; i++) {
        if (FAILED(graphics::g_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(
                &graphics::g_frameContext[i].CommandAllocator))))
            DEBUG_ERROR("5");
    }
}

void graphics::getDescriptors()
{
    SIZE_T rtvDescriptorSize = graphics::g_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

    for (UINT i = 0; i < graphics::g_frameCount; i++) {
        graphics::g_descriptors[i] = rtvHandle;
        rtvHandle.ptr += rtvDescriptorSize;
    }
}

void graphics::createCommandList()
{
    if (FAILED(graphics::g_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                                      graphics::g_frameContext[0].CommandAllocator, NULL,
                                                      IID_PPV_ARGS(&g_pCommandList)))
        || FAILED(g_pCommandList->Close()))
        DEBUG_ERROR("6");
}

void graphics::createRenderTarget()
{
    ID3D12Resource* pBackBuffer = nullptr;
    for (UINT i = 0; i < graphics::g_frameCount; i++) {
        if (FAILED(graphics::g_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer))))
            DEBUG_ERROR("8");
        graphics::g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, graphics::g_descriptors[i]);
        graphics::g_resources[i] = pBackBuffer;
    }
}
