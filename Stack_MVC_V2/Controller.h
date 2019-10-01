#pragma once

#include "stdafx.h"
#include <string>

#include "View.h"

template <class T> class Controller
{
private:
	HWND hWnd;
	Stack<T>& model;
	View<T>& view;

	HWND PushButton;
	HWND PopButton;
	HWND TopButton;
	HWND IsEmptyButton;
	HWND SizeButton;
	HWND ClearButton;
	HWND SumButton;

	HWND InputEdit;
	HWND OutputEdit;

public:
	Controller(HWND hWnd, Stack<T>& modelReference, View<T>& viewReference) : hWnd(hWnd), model(modelReference), view(viewReference) {};

	LRESULT takeMessage(UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CREATE:
		{
			PushButton = CreateWindowW(L"BUTTON", L"Push", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 30, 30, 100, 40, hWnd, HMENU(ID_PUSH), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);

			InputEdit = CreateWindowW(L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER, 160, 40, 100, 20, hWnd, nullptr, HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			OutputEdit = CreateWindowW(L"EDIT", nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 30, 130, 230, 20, hWnd, nullptr, HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			
			TopButton = CreateWindowW(L"BUTTON", L"Top", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 30, 180, 100, 40, hWnd, HMENU(ID_TOP), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			SizeButton = CreateWindowW(L"BUTTON", L"Size", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 160, 180, 100, 40, hWnd, HMENU(ID_SIZE), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			IsEmptyButton = CreateWindowW(L"BUTTON", L"Is Empty", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 30, 250, 100, 40, hWnd, HMENU(ID_ISEMPTY), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			SumButton = CreateWindowW(L"BUTTON", L"Sum", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 160, 250, 100, 40, hWnd, HMENU(ID_SUM), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);

			PopButton = CreateWindowW(L"BUTTON", L"Pop", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 30, 342, 100, 40, hWnd, HMENU(ID_POP), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);
			ClearButton = CreateWindowW(L"BUTTON", L"Clear", WS_TABSTOP | WS_VISIBLE | WS_CHILD, 160, 342, 100, 40, hWnd, HMENU(ID_CLEAR), HINSTANCE(GetWindowLong(hWnd, -6)), nullptr);

			view.initialization(model.createIterator());

			UpdateWindow(hWnd);
		}
		break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_PUSH:
			{
				wchar_t buffer[10];
				SendMessage(InputEdit, EM_GETLINE, 0, LPARAM(buffer));
				model.push(wcstod(buffer, nullptr));

				SendMessage(InputEdit, WM_SETTEXT, 0, LPARAM(""));
				SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(""));

				view.update(ID_PUSH);
			}
			break;

			case ID_TOP:
			{
				if (!model.isEmpty())
				{
					SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(to_wstring(model.top()).c_str()));
				}
				else
				{
					SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(""));
				}

				UpdateWindow(hWnd);
			}
			break;

			case ID_SIZE:
			{
				SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(to_wstring(model.size()).c_str()));

				UpdateWindow(hWnd);
			}
			break;

			case ID_ISEMPTY:
			{
				SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(to_wstring(model.isEmpty()).c_str()));

				UpdateWindow(hWnd);
			}
			break;

			case ID_SUM:
			{
				if (!model.isEmpty())
				{
					StackVisitor<T> visitor;
					model.accept(visitor);

					SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(to_wstring(visitor.getValue()).c_str()));
				}
				else
				{
					SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(to_wstring(0).c_str()));
				}

				UpdateWindow(hWnd);
			}
			break;

			case ID_POP:
			{
				if(!model.isEmpty())
				{
					model.pop();

					SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(""));

					view.update(ID_POP);
				}
			}
			break;

			case ID_CLEAR:
			{
				model.clear();

				SendMessage(OutputEdit, WM_SETTEXT, 0, LPARAM(""));

				view.update(ID_CLEAR);
			}
			break;

			default:
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			}
		}
		break;

		case WM_SIZE:
		{
			UpdateWindow(hWnd);
		}
		break;

		case WM_PAINT:
		{
			view.update(0);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}

		return 0;
	}

};
