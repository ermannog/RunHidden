// RunHidden.cpp : Questo file contiene la funzione '', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {

	
	if (wcscmp(lpCmdLine, L"/?") ==0 ) {
		MessageBoxW(
			NULL,
			(LPCWSTR)L"  RunHidden application\n\n  [application]\n  Specify the path or file name of the application",
			(LPCWSTR)L"Using Run Hidden",
			MB_ICONINFORMATION | MB_OK);
		return 0;
	}

	// Impostazione variabili argc e argv
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (NULL == argv)
	{
		MessageBoxW(NULL, L"CommandLineToArgvW failed.", L"Error", MB_ICONERROR |MB_OK);
		return 10;
	}

	// Verifica esistenza di almeno un parametro
	if (argc < 2) {
		MessageBoxW(NULL, L"No parameters specified.", L"Error", MB_ICONERROR | MB_OK);
		return 1;
	}

	// Creazione del processo per l'applicazione specificata
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	if (!CreateProcessW(NULL,	// No module name
		argv[1],				// Command line				
		NULL,					// Process handle not inheritable
		NULL,					// Thread handle not inheritable
		FALSE,					// Set handle inheritance to FALSE
		CREATE_NO_WINDOW,		// The process is a console application that is being run without a console window
		NULL,					// Use parent's environment block
		NULL,					// Use parent's starting directory 
		&si,					// Pointer to STARTUPINFO structure
		&pi)					// Pointer to PROCESS_INFORMATION structure
	) {					
		MessageBoxW(NULL, L"Failed to create process.", L"Error", MB_ICONERROR | MB_OK);
		return 2;
	}
 
	// Chiusura handles del processo 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	// Rilascio risorse argv
	LocalFree(argv);

	return 0;
}