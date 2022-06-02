#include "Main.h"
#include "ui/ui.hh"


// Main code
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, ui::window_title, NULL };
	
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	//wc.lpfnWndProc = WindowProcess;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandleA(0);
	wc.hIcon = 0;
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = "class001";
	wc.hIconSm = 0;
	
	RegisterClassEx(&wc);
		
	main_hwnd = CreateWindowEx(0, "class001", "yes", WS_POPUP, 100, 100, ui::window_size.x, ui::window_size.y, 0, 0, wc.hInstance, 0);

	// Initialize Direct3D
	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	// Show the window
	ShowWindow(main_hwnd, SW_SHOW);
	UpdateWindow(main_hwnd);

	// Setup Dear ImGui context
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Main loop
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		{
			static int init = false;
			if (!init) {
				ui::init(g_pd3dDevice);
				init = true;
			}
			ImGui::Begin(ui::window_title, &globals.active, ui::window_flags);
			{
				if (globals.auth)
					ui::main();
				else
					ui::pre();
			}
			ImGui::End();
		}
		ImGui::EndFrame();

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		// Handle loss of D3D9 device
		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!globals.active) {
			msg.message = WM_QUIT;
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	CleanupDeviceD3D();
	DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*auto version = "1";
string check = dchar("http://f0632720.xsph.ru/version.txt");

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
/*	URLDownloadToFileA(0, dllLink, dllPath, 0, 0);
	DeleteUrlCacheEntryA(dllLink);
	VM_DOLPHIN_BLACK_END
}

void validate() {
	VM_DOLPHIN_BLACK_START
	cout << "checking version" << endl;

	const char* host = dchar("http://f0632720.xsph.ru/load/updated.exe");

	string filename = dchar("updated.exe");
	string name = experimental::filesystem::current_path().string() + "\\" + filename;

	if (version != utils->dls(check)) {
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

	setlocale(LC_ALL, "Russian");

	validate();
	Sleep(1500);
	if (CheckLicense) {
		distribution();
	}

	VM_DOLPHIN_BLACK_END
}*/