#include <iostream>
#include "ProcessMemory.h"
#include "resource.h"

int					thread_fct(LPVOID param)
{
	ProcessMemory*	pProcMem = (ProcessMemory*)param;
	bool			is_running = true;
	bool			key_pressed = false;
	bool			retVal = false;

	while (is_running && pProcMem) {
		if (GetAsyncKeyState(VK_F2)) {
			if (!key_pressed) {
				retVal = pProcMem->write4(0x908D50, pProcMem->read4(0x908D50) + 2000);
				key_pressed = true;
			}
		} else if (GetAsyncKeyState(VK_F3)) {
			if (!key_pressed) {
				retVal = pProcMem->write4(0x908D2C, pProcMem->read4(0x908D2C) + 10);
				key_pressed = true;
			}
		} else if (GetAsyncKeyState(VK_F5)) {
			if (!key_pressed) {
				pProcMem->write4(0x90A348, 4000);
				pProcMem->write4(0x90B964, 4000);
				pProcMem->write4(0x90CF80, 4000);
				pProcMem->write4(0x90E59C, 4000);
				key_pressed = true;
			}
		}
		else
			key_pressed = false;
		Sleep(50);
	}
	return (0);
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message) {
	case WM_INITDIALOG:
		return ((INT_PTR)TRUE);

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return ((INT_PTR)TRUE);
		}
		break;
	}
	return ((INT_PTR)FALSE);
}

int					main(void)
{
	bool			retVal = false;
	ProcessMemory*	pProcMem = NULL;
	HANDLE			hThread = NULL;

	/* DialogBox(NULL, MAKEINTRESOURCE(IDD_DIALOG1), NULL, About); */

	pProcMem = new ProcessMemory();
	retVal = pProcMem->loadProcessByWindowName("Might and Magic® VI");
	if (retVal) {
		std::cout << "Might and Magic VI Found !" <<std::endl
			<< "==========================" <<std::endl <<std::endl
			<< "F2  \t  Give 2000 Gold" <<std::endl
			<< "F3  \t  Give 10 Food" <<std::endl <<std::endl
			<< "F5  \t  Set each heroes life points to 4000" <<std::endl;
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_fct, pProcMem, 0, 0);
		if (hThread)
			WaitForSingleObject(hThread, -1);
	}
	else
		std::cout << "Game not Found..." <<std::endl;
	delete pProcMem;

	system("PAUSE");
	return (EXIT_SUCCESS);
}
