#pragma once
#include <math.h>
#include <windows.h>

void DrawBonobono(HWND hWnd, HDC hdc, int blink);

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);

void DrawCube(HDC hdc, int x, int y, int x2, int y2);
