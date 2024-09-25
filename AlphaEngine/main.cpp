// ---------------------------------------------------------------------------
// includes
#pragma once
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "GSM/GameStateManager.h"
#include "Level/NormalLevel.h"
#include "Level/PrefabLevel.h"
#include "Level/CombatLevel.h"
#include "Level/LogoLevel.h"
#include "Utils/Utils.h"
#include "Level/Menu.h"
#include "Camera/Camera.h"
#include <dwmapi.h>
#include <windows.h>
#include "ResourceManager/ResourceManager.h"
#pragma comment(lib, "dwmapi.lib")

// ---------------------------------------------------------------------------
// main

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MOUSEWHEEL)
	{
		if ((SHORT)HIWORD(wParam) > 0)
		{
			Camera::GetInstance().AddHeight(-0.5);
		}
		else 
		{
			Camera::GetInstance().AddHeight(0.5);
		}
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	int gGameRunning = 1;

	// Using custom window procedure
#ifdef NDEBUG
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, 0, 60, true, WndProc);
	AESysSetFullScreen(1);
#else
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, 1, 60, true, WndProc);
	AESysSetFullScreen(0);
#endif

	// Initialization of your own variables go here

	HWND hwnd = AESysGetWindowHandle();

	if (hwnd == NULL) {
		return 0;
	}

	RECT rc;

	// Changing the window title
	AESysSetWindowTitle("Huntress");


	GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

	// reset the system modules
	AESysReset();

	GSM::GameStateManager::GetInstance().ChangeLevel(new level::Menu);

	// Game Loop
	while (gsm.ShouldExit() == false && gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Your own update logic goes here
		gsm.Update();

		if (GetActiveWindow() == hwnd)
		{
			//DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(RECT));
			GetWindowRect(hwnd, &rc);
			//rc.top += 31;
			ClipCursor(&rc);
		}

		// Informing the system about the loop's end
		AESysFrameEnd();
	}

	gsm.Exit();

	// free the system
	AESysExit();
}