#include "Global.h"

extern "C" __declspec(dllimport) PLIST_ENTRY NTAPI PsLoadedModuleList;

class DiscordTexture
{
private:
	UCHAR Stub[12];

public:
	ULONG Width;
	ULONG Height;
	UCHAR Texture[];

	_FI ULONG GetTextureSize() {
		return this->Width * this->Height * 4;
	}

	_FI void UpdateFrameCount() {
		ULONG& FrameCount = *(ULONG*)((ULONG_PTR)this + 4);
		FrameCount++;
	}
};

//tmp hook data
PVOID* xKdEnumerateDebuggingDevicesPtr;
PVOID xKdEnumerateDebuggingDevicesVal;

#define GameProc "r5apex.exe"

namespace Win32K {
	ULONG64 gafAsyncKeyState;
	ULONG64 gafAsyncKeyStateRecentDown;
}

unsigned __int16 GetAsyncKeyState(unsigned int a1)
{
	__int16 result;

	if (a1 >= 0x100) { result = 0; }
	else
	{
		unsigned __int64 v1 = (unsigned __int8)a1;
		unsigned __int64 v2 = (unsigned __int64)(unsigned __int8)a1 >> 3;

		__int16 v4 = 0;
		unsigned int v3 = v1 & 7;

		int v5 = *(unsigned __int8*)(v2 + EPtr(Win32K::gafAsyncKeyStateRecentDown));

		if (_bittest((LONG*)&v5, v3)) {
			v4 = 1;
			*(UCHAR*)(v2 + EPtr(Win32K::gafAsyncKeyStateRecentDown)) = v5 & ~(1 << v3);
		}

		result = v4 | 0x8000;
		if (!(*((UCHAR*)EPtr(Win32K::gafAsyncKeyState) + (v1 >> 2)) & (unsigned __int8)(1 << (2 * (v1 & 3)))))
			result = v4;
	}

	return result;
}

#include <cmath>
#include <cfloat>


#include "MathASM.h"
#include "VectorMath.h"
 #include "GameGlobal.h"
#include "GameSDK.h"

#define Log(...) DbgPrint("[FACE]" __VA_ARGS__)



void MatrixInit()
{

	M::viewRenderer = Read<uint64_t>(M::modBase + 0x75461d0); // view_render
	DbgPrintEx(0,0,"ViewRender: %p\n", M::viewRenderer);
	if (!M::viewRenderer)
	{
		M::viewMatrix = 0x0;
		return;
	}
	M::viewMatrix = Read<uint64_t>(M::viewRenderer + 0x11a210); // view_matrix
	DbgPrintEx(0, 0, "viewMatrix: %p\n", M::viewMatrix);
	if (!M::viewMatrix)
	{
		M::viewRenderer = 0x0;
		return;
	}
	M::matr = Read<Matrix>(M::viewMatrix);
	DbgPrintEx(0, 0, "matr: %p\n", M::matr);
		

}

bool InitCheat()
{

	static bool init = false;

	if (!init)
	{
		auto Process = GetProcess(GameProc);

		if (!Process)
			return false;

		M::modBase = (ULONG64)GetUserModuleBase(Process, E("r5apex.exe"));
		DbgPrintEx(0, 0, "M::modBase%p\n", M::modBase);

	





		init = true;
	}

	return init;
}


#include "ESP.h"
#include "AIM.h"
void Cheat()
{

	if (!InitCheat())
		return;

	//MatrixInit();

	menu();
	RenderCheat();
	if (set::ItemESP)
	RenderItems();

}

//meme thread
NTSTATUS FakeThread()
{
	//disable apc
	ImpCall(KeEnterGuardedRegion);

	//unhook kernel hook
	_InterlockedExchangePointer(xKdEnumerateDebuggingDevicesPtr, xKdEnumerateDebuggingDevicesVal);
	xKdEnumerateDebuggingDevicesPtr = nullptr; xKdEnumerateDebuggingDevicesVal = nullptr;

	//create gui thread context
	auto hNtdll = GetUserModuleBase(ImpCall(IoGetCurrentProcess), E("user32"));
	auto CallBack = GetProcAdress(hNtdll, E("GetForegroundWindow"));
	CallUserMode(CallBack);

	//get target process
	NewScan: DiscordTexture* DBuff = nullptr;
	auto TargetProc = GetProcessWModule(E(GameProc), E("DiscordHook"), nullptr);
	//find discord texture
	ULONG64 Addr = 0; do {
		MEMORY_BASIC_INFORMATION MemInfo{}; SIZE_T RetSize;
		if (NT_SUCCESS(ImpCall(ZwQueryVirtualMemory, ZwCurrentProcess(), (PVOID)Addr, MemoryBasicInformation, &MemInfo, 48, &RetSize))) {
			if ((MemInfo.Type & (MEM_COMMIT | MEM_MAPPED)) &&
				(MemInfo.Protect & PAGE_READWRITE) &&
				(MemInfo.RegionSize == 0x3201000)) {
				DBuff = (DiscordTexture*)MemInfo.AllocationBase;
			} Addr += MemInfo.RegionSize;
		} else Addr += PAGE_SIZE;
	} while (Addr < (ULONG_PTR)0x7FFFFFFEFFFFi64);


	//check buffer
	if (!DBuff) {
		DetachFromProcess(TargetProc);
		Sleep(1);
		goto NewScan;
	}



	//don't unload discord memory
	ImpCall(MmSecureVirtualMemory, DBuff, 0x3201000, PAGE_READWRITE);

	//alloc render instance
	//Render gRender{};

	//ULONG64 featureMask = RtlGetEnabledExtendedFeatures((ULONG64)(-1));

	//your cheat
	while (true)
	{


		//XSTATE_SAVE SaveState;
		//KeSaveExtendedProcessorState(featureMask, &SaveState);

		//acquire process lock & check process died
		if (ImpCall(PsAcquireProcessExitSynchronization, TargetProc)) {
			DetachFromProcess(TargetProc);
			break;
		}

		//discord ne prosral`sa
		if (!DBuff->Width || !DBuff->Height)
			goto ReleaseProcessLockSleep;

		//start frame (render)
		rctx.NewFrame(DBuff->Width, DBuff->Height, E(L"Calibri"), 20, 1);



		//run cheat
		Gbl::ScreenSize.x = DBuff->Width;
		Gbl::ScreenSize.y = DBuff->Height;
		width = DBuff->Width;
		height = DBuff->Height;
		static int cases = 0;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		switch (cases) {
		case 0: { r -= 0.0015f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.0015f; b -= 0.0015f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.0015f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.0015f; g -= 0.0015f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}
		rctx.String(1, 1, E(L"Apex Discord Memez"), TA_LEFT, RGB(r*255, g*255, b*255));

		Cheat();
		//MatrixInit();
		//end frame (copy)
		rctx.EndFrame(DBuff->Texture);
		DBuff->UpdateFrameCount();

		//unlock process & wait
		ReleaseProcessLockSleep:
		ImpCall(PsReleaseProcessExitSynchronization, TargetProc);
		Sleep(1);

		//END UNLOAD
		if (GetAsyncKeyState(0x23)) {
			sp("end cheat!!!");
			//KeRestoreExtendedProcessorState(&SaveState);
		//	HookMgr::VMT_UnHook();
			DetachFromProcess(TargetProc);
			break;
		}

		//KeRestoreExtendedProcessorState(&SaveState);
	}

	//enable all apc
	ImpCall(KeLeaveGuardedRegion);

	//lol return 1!!
	return STATUS_NOT_IMPLEMENTED;
}

#pragma code_seg(push)
#pragma code_seg("INIT")

//create thread meme
bool SetupKernelThread(PVOID KBase, PVOID ThreadStartAddr)
{
	//get thread fake start address
	PVOID hMsVCRT = nullptr;
	auto Process = GetProcessWModule(E("explorer.exe"), E("msvcrt"), &hMsVCRT);
	auto FakeStartAddr = (PUCHAR)GetProcAdress(hMsVCRT, E("_endthreadex")) + 0x30;

	auto win32k = GetKernelModuleBase(E("win32kbase.sys"));
	Win32K::gafAsyncKeyState = (ULONG64)EPtr(GetProcAdress(win32k, E("gafAsyncKeyState")));
	Win32K::gafAsyncKeyStateRecentDown = (ULONG64)EPtr(GetProcAdress(win32k, E("gafAsyncKeyStateRecentDown")));

	//get usermode func
	auto Var = UAlloc(0x1000); HANDLE Thread = nullptr;
	auto hNtdll = GetUserModuleBase(Process, E("ntdll"));
	auto CallBack = GetProcAdress(hNtdll, E("NtQueryAuxiliaryCounterFrequency"));

	//set kernel hook
	xKdEnumerateDebuggingDevicesPtr = (PVOID*)RVA((ULONG64)EPtr(KeQueryAuxiliaryCounterFrequencyFn) + 4, 7);
	xKdEnumerateDebuggingDevicesVal = _InterlockedExchangePointer(xKdEnumerateDebuggingDevicesPtr, ThreadStartAddr);

	//create new thread
	CLIENT_ID Cid;
	ImpCall(RtlCreateUserThread, ZwCurrentProcess(), nullptr, false, 0, 0, 0, CallBack, Var, &Thread, &Cid);

	if (Thread)
	{
		//close useless handle
		ImpCall(ZwClose, Thread);

		//spoof thread start address
		PETHREAD EThread;
		ImpCall(PsLookupThreadByThreadId, Cid.UniqueThread, &EThread);
		auto StartAddrOff = *(USHORT*)(FindPatternSect(KBase, E("PAGE"), E("48 89 86 ? ? ? ? 48 8B 8C")) + 3);
		*(PVOID*)((ULONG64)EThread + StartAddrOff/*Win32StartAddress*/) = FakeStartAddr;
		ImpCall(ObfDereferenceObject, EThread);

		//wait exec kernel callback
		while (xKdEnumerateDebuggingDevicesPtr && xKdEnumerateDebuggingDevicesVal) 
		{
			Sleep(10);
		}
	}

	//cleanup
	UFree(Var);
	DetachFromProcess(Process);

	//ret create status
	return (bool)Thread;
}

//driver entry point
// 
// 
//NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObj, _In_ PUNICODE_STRING RegistryPath)
//{
//	DbgPrintEx(0, 0, "Driver Created.\n");
//
//	// Fix Paramms
//	UNREFERENCED_PARAMETER(RegistryPath);
//	UNREFERENCED_PARAMETER(DriverObj);+


NTSTATUS DriverEntry()
{

	//UNREFERENCED_PARAMETER(a1);
	PVOID KBase = *reinterpret_cast<PVOID*>(std::uintptr_t(PsLoadedModuleList) + 0x30);

	//import set
	ImpSet(IoIs32bitProcess);
	ImpSet(PsGetProcessWow64Process);
	ImpSet(ExAllocatePoolWithTag);
	ImpSet(ExFreePoolWithTag);
	ImpSet(IoGetCurrentProcess);
	ImpSet(KeAttachProcess);
	ImpSet(KeDelayExecutionThread);
	ImpSet(KeDetachProcess);
	ImpSet(KeEnterGuardedRegion);
	ImpSet(KeLeaveGuardedRegion);
	ImpSet(KeQueryAuxiliaryCounterFrequency);
	ImpSet(KeUserModeCallback);
	ImpSet(MmIsAddressValid);
	ImpSet(ObfDereferenceObject);
	ImpSet(PsAcquireProcessExitSynchronization);
	ImpSet(PsGetProcessPeb);
	ImpSet(PsLookupProcessByProcessId);
	ImpSet(PsLookupThreadByThreadId);
	ImpSet(PsReleaseProcessExitSynchronization);
	ImpSet(RtlCreateUserThread);
	ImpSet(ZwAllocateVirtualMemory);
	ImpSet(ZwClose);
	ImpSet(ZwFreeVirtualMemory);
	ImpSet(ZwQuerySystemInformation);
	ImpSet(ZwQueryVirtualMemory); 
	ImpSet(MmSecureVirtualMemory);
	ImpSet(ZwProtectVirtualMemory);
	ImpSet(DbgPrint);


	//ImpCall(DbgPrint, "Kernel: 0x%p | a1: 0x%p\n", KBase, a1);

	//disable apc+
	ImpCall(KeEnterGuardedRegion);

	
	//Log("KBASE: 0x%p | Base: 0x%p\n", KBase, baseNtoskrnl);
	//create kernel usermode thread
	SetupKernelThread(KBase, FakeThread);

	//enable all apc
	ImpCall(KeLeaveGuardedRegion);

	return STATUS_SUCCESS;
}

#pragma code_seg(pop)