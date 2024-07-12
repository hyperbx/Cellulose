#pragma once

#define FUNCTION_PTR(returnType, callingConvention, function, location, ...) \
    returnType (callingConvention *function)(__VA_ARGS__) = (returnType(callingConvention*)(__VA_ARGS__))(location)

#define PROC_ADDRESS(libraryName, procName) \
    GetProcAddress(LoadLibrary(TEXT(libraryName)), procName)

#define HOOK(returnType, callingConvention, functionName, location, ...) \
    typedef returnType callingConvention functionName(__VA_ARGS__); \
    functionName* original##functionName = (functionName*)(location); \
    returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INLINE_HOOK(returnType, callingConvention, functionName, location, ...) \
    typedef returnType callingConvention functionName(__VA_ARGS__); \
    inline static functionName* original##functionName = (functionName*)(location); \
    inline static returnType callingConvention implOf##functionName(__VA_ARGS__)

#define INSTALL_HOOK(functionName) \
{ \
    DetourTransactionBegin(); \
    DetourUpdateThread(GetCurrentThread()); \
    DetourAttach((void**)&original##functionName, implOf##functionName); \
    DetourTransactionCommit(); \
}

#define INSTALL_HOOK_EXPLICIT(functionName, addr) \
{ \
	*(void**)&original##functionName = (void*)(addr); \
    DetourTransactionBegin(); \
    DetourUpdateThread(GetCurrentThread()); \
    DetourAttach((void**)&original##functionName, &implOf##functionName); \
    DetourTransactionCommit(); \
}

#define WRITE_MEMORY(location, type, ...) \
{ \
    const type data[] = { __VA_ARGS__ }; \
    DWORD oldProtect; \
    VirtualProtect((void*)(location), sizeof(data), PAGE_EXECUTE_READWRITE, &oldProtect); \
    memcpy((void*)(location), data, sizeof(data)); \
    VirtualProtect((void*)(location), sizeof(data), oldProtect, &oldProtect); \
}

#define WRITE_JUMP(location, function) \
{ \
    WRITE_MEMORY(location, uint8_t, 0xE9); \
    WRITE_MEMORY(location + 1, uint32_t, (uint32_t)(function) - (size_t)(location) - 5); \
}
	
#define WRITE_CALL(location, function) \
{ \
    WRITE_MEMORY(location, uint8_t, 0xE8); \
    WRITE_MEMORY(location + 1, uint32_t, (uint32_t)(function) - (size_t)(location) - 5); \
}

#define WRITE_NOP(location, count) \
{ \
    DWORD oldProtect; \
    VirtualProtect((void*)(location), (size_t)(count), PAGE_EXECUTE_READWRITE, &oldProtect); \
    for (size_t i = 0; i < (size_t)(count); i++) \
        *((uint8_t*)(location) + i) = 0x90; \
    VirtualProtect((void*)(location), (size_t)(count), oldProtect, &oldProtect); \
}

#define CHECK_MODULE(in_ptr, in_module) \
	if (in_ptr == 0) \
	{ \
		MessageBoxA(nullptr, "Failed to get module " ##in_module, "Fatal Error", MB_ICONERROR); \
		exit(-1); \
	}