#pragma once

#include <boost/asio.hpp>

#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#include <wininet.h>
#pragma comment(lib, "Wininet.lib")
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_SPRECATION_WARNING

#include <Windows.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
#include <tchar.h>
#include <experimental/filesystem>
#include <filesystem>
#include "Guard.h"
#include "class.h"
#include "bug.h"
#include <random>

#include "dcrypt/crypt.h"
#include "dcrypt/dchar.h"