#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;
#define CREATE_DIRS 1
#define COPY_AND_CREATE_FILES 2


wchar_t dir[1000];
wchar_t create_file[1000];

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void AddMenus(HWND);
void AddFields(HWND);
void CreateDirs(wstring path, HWND hWnd);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSW wc = {};
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;


	if (!RegisterClassW(&wc)) return -1;

	CreateWindowW(L"myWindowClass", L"My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 800, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {

	case WM_COMMAND:
		switch (wp) {
		case CREATE_DIRS:
			CreateDirs(L"D:\\FILE11\\FILE12\\FILE13\\", hWnd);
			CreateDirs(L"D:\\FILE21\\", hWnd);
			break;
		case COPY_AND_CREATE_FILES:
			STARTUPINFO si;
			PROCESS_INFORMATION piApp;
			ZeroMemory(&si, sizeof(STARTUPINFO));
			si.cb = sizeof(STARTUPINFO);
			if (!CreateProcess(L"D:\\processes\\CreateFChild.exe", NULL, NULL, NULL, FALSE,
				CREATE_NEW_CONSOLE, NULL, NULL, &si, &piApp))
				
			{
				cout << "The mew process is not created." << endl
					<< "Check a name of the process." << endl;
			}
			// ждем завершения созданного процесса
			WaitForSingleObject(piApp.hProcess, INFINITE);
			CloseHandle(piApp.hThread);
			CloseHandle(piApp.hProcess);			ZeroMemory(&si, sizeof(STARTUPINFO));			si.cb = sizeof(STARTUPINFO);			if (!CreateProcess(L"D:\\processes\\CreateFiles.exe", NULL, NULL, NULL, FALSE,
				NULL, NULL, NULL, &si, &piApp))

			{
				cout << "The mew process is not created." << endl
					<< "Check a name of the process." << endl;
			}
			// ждем завершения созданного процесса
			WaitForSingleObject(piApp.hProcess, INFINITE);
			CloseHandle(piApp.hThread);
			CloseHandle(piApp.hProcess);			break;

		}
		break;

	

	case WM_CREATE:
		AddFields(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}



void AddFields(HWND hWnd) {

	CreateWindowW(L"Button", L"Create Dirs", WS_VISIBLE | WS_CHILD, 0, 0, 98, 38, hWnd, (HMENU)CREATE_DIRS, NULL, NULL);
	CreateWindowW(L"Button", L"Copy and create", WS_VISIBLE | WS_CHILD, 200, 0, 98, 38, hWnd, (HMENU)COPY_AND_CREATE_FILES, NULL, NULL);



}

void CreateDirs(wstring path, HWND hWnd) {

	for (int i = 0; i < path.length(); i++)
		if (path[i] == '\\') {
			CreateDirectoryW(path.substr(0, i).c_str(), NULL);
			MessageBoxW(hWnd, path.substr(0, i).c_str(), L"The folder was created", MB_OK);
		}


}














/*
int main()
{
wchar_t lpszCommandLine[] = L"D:\\asd.exe C:\\masm32 D:\\File11";
STARTUPINFO si;
PROCESS_INFORMATION piCom;
ZeroMemory(&si, sizeof(STARTUPINFO));
si.cb = sizeof(STARTUPINFO);
// создаем новый консольный процесс
CreateProcess(NULL, lpszCommandLine, NULL, NULL, FALSE,
NULL, NULL, NULL, &si, &piCom);
// закрываем дескрипторы этого процесса
CloseHandle(piCom.hThread);
CloseHandle(piCom.hProcess);
cout << "the new process is created" << endl;
cout << "type anything to finish" << endl;
return 0;
}
*/