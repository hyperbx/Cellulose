#pragma once
#include <string>
#define CP_SHIFT_JIS 932

#define INI_BEGIN_SECTION(section) \
{ \
    std::string CurrentSection = section;

#define INI_READ_STRING_B(var)     var = reader.Get(CurrentSection, #var, var)
#define INI_READ_BOOLEAN_B(var)    var = reader.GetBoolean(CurrentSection, #var, var)
#define INI_READ_FLOAT_B(var)      var = reader.GetFloat(CurrentSection, #var, var)
#define INI_READ_INTEGER_B(var)    var = reader.GetInteger(CurrentSection, #var, var)
#define INI_READ_DOUBLE_B(var)     var = reader.GetReal(CurrentSection, #var, var)
#define INI_READ_ENUM_B(type, var) var = (type)reader.GetInteger(CurrentSection, #var, var)

#define INI_END_SECTION() \
}

#define INI_READ_STRING(section, var)     var = reader.Get(section, #var, var)
#define INI_READ_BOOLEAN(section, var)    var = reader.GetBoolean(section, #var, var)
#define INI_READ_FLOAT(section, var)      var = reader.GetFloat(section, #var, var)
#define INI_READ_INTEGER(section, var)    var = reader.GetInteger(section, #var, var)
#define INI_READ_DOUBLE(section, var)     var = reader.GetReal(section, #var, var)
#define INI_READ_ENUM(section, type, var) var = (type)reader.GetInteger(section, #var, var)

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

#define INIT_CONSOLE() \
    AllocConsole(); \
    freopen("CONOUT$", "w", stdout);

inline std::wstring MakeWideString(const char* pStr, uint32_t cp = CP_SHIFT_JIS)
{
    if (!pStr)
    {
        return {};
    }
    const auto len = strlen(pStr);
    const auto bufLen = MultiByteToWideChar(cp, 0, pStr, len, nullptr, 0);

	std::wstring buffer{};
    buffer.resize(bufLen);

    MultiByteToWideChar(cp, 0, pStr, len, buffer.data(), bufLen);
    return buffer;
}

inline std::string GetSubstringBeforeLastChar(const std::string str, char c, int cIndex = 0)
{
    std::string result;
    const size_t index = str.rfind(c);

    if (std::string::npos != index)
        result = str.substr(0, index);

    for (int i = 0; i < cIndex; i++)
        return GetSubstringBeforeLastChar(result, c, i);

    return result;
}

inline std::string GetSubstringAfterLastChar(const std::string& str, char c, int cIndex = 0)
{
    std::string result = str;
    size_t index;

    for (int i = 0; i <= cIndex; ++i)
    {
        index = result.rfind(c);

        if (index == std::string::npos)
            return "";

        result = result.substr(index + 1);
    }

    return result;
}

inline bool FileExists(const std::string& path)
{
    struct stat buffer;

    return stat(path.c_str(), &buffer) == 0;
}