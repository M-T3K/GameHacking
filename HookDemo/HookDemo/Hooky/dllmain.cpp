// dllmain.cpp : Defines the entry point for the DLL application.
#include "Windows.h"

// Adaptation of GuidedHacking's Tutorial
// So full credit to them
auto hooky(LPVOID o_func, LPVOID hk_func, int size) -> bool {

	// We need at least 5 bytes to place our jmp instruction
	if (size < 5) {
		return false;
	}

	DWORD old_protection;
	VirtualProtect(o_func, size, PAGE_EXECUTE_READWRITE, &old_protection);
	memset(o_func, 0x90, size); // We set memory to NOP

	DWORD relative_address = (DWORD)hk_func - (DWORD)o_func - size;
	
	*(BYTE *)o_func = 0xE9; // Replacing the previous NOP's with a JMP
	*(DWORD *)((DWORD)hk_func + 1) = relative_address;

}

DWORD jmpBackAddress;

auto hk_func() -> void __declspec(naked) {


	// Volvemos a donde estabamos
	// incluyendo la instrucciones que hemos sobreescrito
	_asm {
		add eax, 4
		mov dword ptr[ebp + 8], eax
		mov eax, dword ptr[ebp+8]
		jmp [jmpBackAddress]
	}
}

auto CheatThread(LPVOID param) -> DWORD WINAPI {

	DWORD hk_address = 0x00F12688;// instruccion 
	int hk_size = 6; // Tiene que ser >= 5, asi que necesitamos incluir la siguiente intruccion
	jmpBackAddress = hk_address + hk_size;

	hooky((LPVOID)hk_address, hk_func, hk_size);

	while (true) {
	
		if (GetAsyncKeyState(VK_DELETE)) {
		
			return 0;
		}
		Sleep(100); // The game updates every second, we dont need more than this
	
	}
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
              DWORD  ul_reason_for_call,
			  LPVOID lpReserved
              ) {

	// Only one we care about for now
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CheatThread, hModule, 0, nullptr);
	}
    return TRUE;
}

