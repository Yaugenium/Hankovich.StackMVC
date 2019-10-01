#pragma once

#include "stdafx.h"
#include <string>

#include "Iterator.h"

template <class T> class View
{
private:
	HWND hWnd;
	HWND ListBox;
	HWND Text;
	Iterator<T>* iterator;

public:
	View(HWND hWnd) : hWnd(hWnd) {};

	void initialization(Iterator<T>* iter)
	{
		iterator = iter;

		Text = CreateWindowW(L"STATIC", L"Stack", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER, 290, 40, 150, 19, hWnd, nullptr, HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
		ListBox = CreateWindowW(L"LISTBOX", nullptr, WS_TABSTOP | WS_CHILD | WS_VISIBLE | LBS_NOTIFY | WS_VSCROLL | WS_BORDER, 290, 60, 150, 330, hWnd, nullptr, HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
	}

	void update(int id)
	{
		switch(id)
		{
		case ID_PUSH:
		{
			iterator->first();

			SendMessage(ListBox, LB_ADDSTRING, 0, LPARAM(to_wstring(iterator->currentItem()).c_str()));

			UpdateWindow(hWnd);
		}
		break;

		case ID_POP:
		{
			SendMessage(ListBox, LB_DELETESTRING, WPARAM(SendMessage(ListBox, LB_GETCOUNT, 0, 0) - 1), 0);

			UpdateWindow(hWnd);
		}
		break;

		case ID_CLEAR:
		{
			SendMessage(ListBox, LB_RESETCONTENT, 0, 0);

			UpdateWindow(hWnd);
		}
		break;

		default:
			break;
		}
	}
};
