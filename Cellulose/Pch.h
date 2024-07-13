#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <detours.h>

#include <cstdint>
#include <cstdio>
#include <format>
#include <stdlib.h>

#include "Dependencies\INIReader.h"
#include "Helpers.h"
#include "Configuration.h"
#include "ResourceRedirector.h"