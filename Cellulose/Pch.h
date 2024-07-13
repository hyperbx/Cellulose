#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <detours.h>

#include <commdlg.h>
#include <cstdint>
#include <cstdio>
#include <format>
#include <ShlObj.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <wrl/client.h>

#include "Dependencies\INIReader.h"
#include "Helpers.h"
#include "Configuration.h"
#include "DialogHelpers.h"
#include "ResourceRedirector.h"