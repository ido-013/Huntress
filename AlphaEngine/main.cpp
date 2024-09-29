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
#include "Level/ClearLevel.h"
#include "Utils/Utils.h"
#include "Level/Menu.h"
#include "Camera/Camera.h"
#include <dwmapi.h>
#include <windows.h>
#include "ResourceManager/ResourceManager.h"
#pragma comment(lib, "dwmapi.lib")

// ---------------------------------------------------------------------------
// main

int gGameRunning = 1;

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

	if (message == WM_CLOSE)
	{
		gGameRunning = 0;
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

	// Using custom window procedure
#ifdef NDEBUG
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, 0, 60, true, WndProc);
#else
	AESysInit(hInstance, nCmdShow, windowWidth, windowHeight, 1, 60, true, WndProc);
	AESysSetFullScreen(0);
#endif
	bool fullscreen = true;
	AESysSetFullScreen(fullscreen);

	// Initialization of your own variables go here

	HWND hwnd = AESysGetWindowHandle();

	if (hwnd == NULL) {
		return 0;
	}

	RECT rc;
	GetWindowRect(hwnd, &rc);

	// Changing the window title
	AESysSetWindowTitle("Huntress");

	GSM::GameStateManager& gsm = GSM::GameStateManager::GetInstance();

	// reset the system modules
	AESysReset();

	//GSM::GameStateManager::GetInstance().ChangeLevel(new level::LogoLevel);
	GSM::GameStateManager::GetInstance().ChangeLevel(new level::Menu);
	//GSM::GameStateManager::GetInstance().ChangeLevel(new level::CombatLevel(0));

	// Game Loop
	while (gsm.ShouldExit() == false && gGameRunning)
	{
		AEFrameRateControllerReset();

		// Informing the system about the loop's start
		AESysFrameStart();

		// Your own update logic goes here
		gsm.Update();

		if (GetActiveWindow() == hwnd)
		{
			if (fullscreen)
			{
				GetWindowRect(hwnd, &rc);
			}
			else
			{
				DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(RECT));
			}

			ClipCursor(&rc);
		}

		// Informing the system about the loop's end
		AESysFrameEnd();

		if (AEInputCheckTriggered(AEVK_F11))
		{
			fullscreen = !fullscreen;
			AESysSetFullScreen(fullscreen);
		}
	}

	gsm.Exit();

	//MEM LEAK CHECKS

	// free the system
	AESysExit();
	return 0;
}