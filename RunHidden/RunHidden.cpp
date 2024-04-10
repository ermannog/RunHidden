// RunHidden.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << "Error: No parameters specified.\n";
		return 1;
	}

	// Converte la stringa char in wchar_t
	int appPathLength = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, NULL, 0);
	LPWSTR appPath = new WCHAR[appPathLength];
	MultiByteToWideChar(CP_ACP, 0, argv[1], -1, appPath, appPathLength);


	// Crea un processo per l'applicazione specificata
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	if (!CreateProcess(NULL,	// No module name (use command line)
		appPath,
		NULL,					// Process handle not inheritable
		NULL,					// Thread handle not inheritable
		FALSE,					// Set handle inheritance to FALSE
		0,						// No creation flags
		NULL,					// Use parent's environment block
		NULL,					// Use parent's starting directory 
		&si,					// Pointer to STARTUPINFO structure
		&pi)					// Pointer to PROCESS_INFORMATION structure
	) {					
		std::cout << "Error: Failed to create process.\n";
		return 2;
	}

	// Elimina la stringa wchar_t
	delete[] appPath;

	// Chiudi le handle del processo figlio
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
