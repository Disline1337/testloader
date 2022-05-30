#include <string>
#include <Windows.h>
#include <ShlObj_core.h>
#include <fstream>

#include <curl/curl.h>
#pragma comment(lib, "libcurl.lib")
#pragma comment(lib, "crypt32.lib")
#include <experimental/filesystem>
#include <shellapi.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")
#include <WinInet.h>
#pragma comment(lib, "Wininet.lib")

using namespace std;

class CUtils
{
public:
	string dls(string URL);
};

extern CUtils* utils;