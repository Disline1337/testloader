#include "Injection.h"

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
#include "main.h"
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING


auto version = "1";
string check = dchar("http://f0632720.xsph.ru/version.txt");


string repl(string subject, const string& search, const string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
string dls(string URL) {
	HINTERNET interwebs = InternetOpenA("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HINTERNET urlFile;
	string rtn;
	if (interwebs) {
		urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
		if (urlFile) {
			char buffer[2000];
			DWORD bytesRead;
			do {
				InternetReadFile(urlFile, buffer, 2000, &bytesRead);
				rtn.append(buffer, bytesRead);
				memset(buffer, 0, 2000);
			} while (bytesRead);
			InternetCloseHandle(interwebs);
			InternetCloseHandle(urlFile);
			string p = repl(rtn, "|n", "\r\n");
			return p;
		}
	}
	InternetCloseHandle(interwebs);
	string p = repl(rtn, "|n", "\r\n");
	return p;
}


using namespace std;


void window()
{
	VM_DOLPHIN_BLACK_START
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);

	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, 800, 200, 520, 800, TRUE); }
	SetLayeredWindowAttributes(hwnd, 1000, 1000, LWA_ALPHA);

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);


	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("mode con cols=60 lines=25");
	VM_DOLPHIN_BLACK_END
}

void windowname()
{
	VM_DOLPHIN_BLACK_START
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<> distr(0, 51);
	string name = "";
	char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
	for (int i = 0; i < 15; ++i)
	{
		name = name + alphabet[distr(mt)];
		SetConsoleTitleA(name.c_str());
	}
	VM_DOLPHIN_BLACK_END
}

void setup() {
	VM_DOLPHIN_BLACK_START
	window();
	windowname();
	VM_DOLPHIN_BLACK_END
}

void download(const char* dllLink, const char* dllPath)
{
	VM_DOLPHIN_BLACK_START
/*	cout << dllLink << endl;
	cout << dllPath << endl;
	system("PAUSE");*/
	URLDownloadToFileA(0, dllLink, dllPath, 0, 0);
	DeleteUrlCacheEntryA(dllLink);
	VM_DOLPHIN_BLACK_END
}

void validate() {
	VM_DOLPHIN_BLACK_START
	cout << "checking version" << endl;

	const char* host = dchar("http://f0632720.xsph.ru/load/updated.exe");

	string filename = dchar("updated.exe");
	string name = experimental::filesystem::current_path().string() + "\\" + filename;

	if (version != dls(check)) {
			download(host, name.c_str());
			cout << "updating loader" << endl;
			Sleep(500);
			system("cls");
			cout << "placed on disk C" << endl;
			cout << "\n";
			cout << "opening" << endl;
			Sleep(1500);
			system(name.c_str());
			exit(1);
	}
	else {
		system("cls");
		cout << "latest build";
		Sleep(100);
		system("cls");
		cout << "starting";
		CheckLicense();
	}
	VM_DOLPHIN_BLACK_END
}

void vk() {
	Sleep(450);
	cout << "h";
	Sleep(150);
	system("cls");
	cout << "ht";
	Sleep(150);
	system("cls");
	cout << "htt";
	Sleep(150);
	system("cls");
	cout << "http";
	Sleep(150);
	system("cls");
	cout << "https";
	Sleep(150);
	system("cls");
	cout << "https:";
	Sleep(150);
	system("cls");
	cout << "https:/";
	Sleep(150);
	system("cls");
	cout << "https://";
	Sleep(150);
	system("cls");
	cout << "https://v";
	Sleep(150);
	system("cls");
	cout << "https://vk";
	Sleep(150);
	system("cls");
	cout << "https://vk.c";
	Sleep(150);
	system("cls");
	cout << "https://vk.co";
	Sleep(150);
	system("cls");
	cout << "https://vk.com";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/r";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/ri";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/ris";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/rise";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/risex";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/risexc";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/risexcs";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/risexcsg";
	Sleep(150);
	system("cls");
	cout << "https://vk.com/risexcsgo";
	cout << "\n";
	Sleep(150);

	ShellExecute(NULL, "open", "https://vk.com/risexcsgo", NULL, NULL, SW_SHOW);
	exit(0);
}

void ds() {
	Sleep(450);
	cout << "h";
	Sleep(150);
	system("cls");
	cout << "ht";
	Sleep(150);
	system("cls");
	cout << "htt";
	Sleep(150);
	system("cls");
	cout << "http";
	Sleep(150);
	system("cls");
	cout << "https";
	Sleep(150);
	system("cls");
	cout << "https:";
	Sleep(150);
	system("cls");
	cout << "https:/";
	Sleep(150);
	system("cls");
	cout << "https://";
	Sleep(150);
	system("cls");
	cout << "https://d";
	Sleep(150);
	system("cls");
	cout << "https://di";
	Sleep(150);
	system("cls");
	cout << "https://dis";
	Sleep(150);
	system("cls");
	cout << "https://disc";
	Sleep(150);
	system("cls");
	cout << "https://disco";
	Sleep(150);
	system("cls");
	cout << "https://discor";
	Sleep(150);
	system("cls");
	cout << "https://discord";
	Sleep(150);
	system("cls");
	cout << "https://discord.";
	Sleep(150);
	system("cls");
	cout << "https://discord.g";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4j";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQp";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpf";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpfB";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpfBw";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpfBwY";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpfBwYB";
	Sleep(150);
	system("cls");
	cout << "https://discord.gg/4jQpfBwYB";
	cout << "\n";

	ShellExecute(NULL, "open", "https://discord.gg/4jQpfBwYBG", NULL, NULL, SW_SHOW);
	cout << "\a";
	exit(1);
}

void f() {
	Sleep(450);
	cout << "h";
	Sleep(150);
	system("cls");
	cout << "ht";
	Sleep(150);
	system("cls");
	cout << "htt";
	Sleep(150);
	system("cls");
	cout << "http";
	Sleep(150);
	system("cls");
	cout << "https";
	Sleep(150);
	system("cls");
	cout << "https:";
	Sleep(150);
	system("cls");
	cout << "https:/";
	Sleep(150);
	system("cls");
	cout << "https://";
	Sleep(150);
	system("cls");
	cout << "https://r";
	Sleep(150);
	system("cls");
	cout << "https://ri";
	Sleep(150);
	system("cls");
	cout << "https://ris";
	Sleep(150);
	system("cls");
	cout << "https://rise";
	Sleep(150);
	system("cls");
	cout << "https://risex";
	Sleep(150);
	system("cls");
	cout << "https://risex.";
	Sleep(150);
	system("cls");
	cout << "https://risex.x";
	Sleep(150);
	system("cls");
	cout << "https://risex.xy";
	Sleep(150);
	system("cls");
	cout << "https://risex.xyz";

	ShellExecute(NULL, "open", "https://risex.xyz", NULL, NULL, SW_SHOW);
	cout << "\a";
	exit(1);
}

int doi(string game, string dllname) {
	string path = experimental::filesystem::temp_directory_path().string() + dllname;

	const char* szDllFile = path.c_str();
	const char* szProc = game.c_str();

	PROCESSENTRY32 PE32{ 0 };
	PE32.dwSize = sizeof(PE32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		DWORD Err = GetLastError();
		printf("CreateToolhelp32Snapshot failed: 0x%X\n", Err);
		system("PAUSE");
		return 0;
	}

	DWORD PID = 0;
	BOOL bRet = Process32First(hSnap, &PE32);
	while (bRet)
	{
		if (!strcmp(szProc, PE32.szExeFile))
		{
			PID = PE32.th32ProcessID;
			break;
		}
		bRet = Process32Next(hSnap, &PE32);
	}

	CloseHandle(hSnap);

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (!hProc)
	{
		DWORD Err = GetLastError();
		printf("OpenProcess failed: 0x%X\n", Err);
		system("PAUSE");
		return 0;
	}

	if (!ManualMap(hProc, szDllFile))
	{
		CloseHandle(hProc);
		printf("Something went wrong\n");
		system("PAUSE");
		return 0;
	}

	CloseHandle(hProc);
	remove(szDllFile);
	cin.get();
	return 0;

	return true;
}

void distribution()
{
	VM_DOLPHIN_BLACK_START
	char *CB = dchar("http://f0632720.xsph.ru/gee/cheat.dll");

	string dllname = dchar("svchost.dll");
	string path = experimental::filesystem::temp_directory_path().string() + dllname;


	int option;

	system("cls");
	system("color 3");
	cout << "---------------------------------\n";
	cout << "|  Выбери чит    Choose cheat   |\n";
	cout << "|-------------------------------|\n";
	cout << "|    CSGO:                      |\n";
	cout << "|                               |\n";
	cout << "|  1 - RiseX                    |\n";
	cout << "|                               |\n";
	cout << "|-------------------------------|\n";
	cout << "|                               |\n";
	cout << "|           2 - discord         |\n";
	cout << "|           3 - vk.com          |\n";
	cout << "|           4 - forum           |\n";
	cout << "|                               |\n";
	cout << "---------------------------------\n" << endl;
	cout << "\n -->> ";
	cin >> option;

	switch (option) 
	{
		case 1: {
			Sleep(600);
			system("cls");
			system("color 2");

			ShellExecute(NULL, "open", "steam://run/730", NULL, NULL, SW_SHOW);
			cout << "[INFO]: Starting game..." << endl;

			Sleep(30000);

			cout << "[INFO]: Injecting..." << endl;

			Sleep(15000);

			char* dllname = dchar("svchost.dll");

			char* game = dchar("csgo.exe");
			download(CB, path.c_str());
			doi(game, dllname);

			cout << "\a";
			cout << "[INFO]: Injected" << endl;
			cout << "[ADMIN]: Good luck";

			Sleep(500);
			break;
	}
		case 2: {
			ds();
			break;
		}
		case 3: {
			vk();
			break;
		}
		case 4: {
			f();
			break;
		}
		default: 
		{
			//		remove("C:\\dll.dll");
			Sleep(1);
			exit(1);
		}
	}
	VM_DOLPHIN_BLACK_END
}

int main()
{
	VM_DOLPHIN_BLACK_START
	setup();
	Sleep(500);

/*	if (protection::check_security() != protection::debug_results::none) {
		return 0;
	}*/

	setlocale(LC_ALL, "Russian");
//	Protection::AllChecks();
	validate();
	Sleep(1500);
	if (CheckLicense) {
		distribution();
	}

	VM_DOLPHIN_BLACK_END
}