#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <detours.h>

#include <commdlg.h>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <format>
#include <ShlObj.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Shlwapi.h>
#include <wrl/client.h>

#include "Dependencies\INIReader.h"
#include "Dependencies\json.h"
#include "Helpers.h"
#include "Configuration.h"
#include "LocaleService.h"
#include "DialogHelpers.h"
#include "ResourceRedirector.h"