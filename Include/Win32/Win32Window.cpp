/*
�o�O�@�ӱM�����͵��������O�A���U���o�ˡA�B�z�T������ơA���ݱq�~�����ѵ�ToCreateWindow�A�_�h�|�ϥιw�]����ơC
LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
ToCreateWindow���e������ƬO�ΨӴy�z�������A�Ĥ����N�O�n���W�������, �O�o�n�x�s�^�Ǫ�HWND����X�C
GetHandle�u��o��̫�@�ӵ���������X�C
�`�N�I�I�I�b�L���j�餤���ݦۦ�I�sHandlePeekMessage�ӳB�z�T���C
GetMouseState�i�H��o�ƹ����A�C
*/

#include "Win32Window.h"


Win32Window::Win32Window(void)
{
	m_hInstance = GetModuleHandle(NULL);
}

HWND Win32Window::ToCreateWindow(int x, int y, int width, int height, const wchar_t *title, LRESULT (_stdcall *wndporc)(HWND, UINT, WPARAM, LPARAM)/*= &Win32Window::Proc*/)
{
	WNDCLASS	window_class;
	memset(&window_class, 0, sizeof(WNDCLASS));
	// `�]�w�������A`
	window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	// `�]�w�T���B�z�禡��WndProc`
	window_class.lpfnWndProc = wndporc;
	// `���o�ثe���檺�{��`
	window_class.hInstance = m_hInstance;
	// `�ϥΤ��w���ƹ����`
	window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
	// `�I���]���¦�, ��꦳�S���]���S�t.`
	window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// `���w�@�ӵ��U�����ɨϥΪ��W�r`
	window_class.lpszClassName = title;
	// `��@�~�t�ε��U�@�ӷs������`
	if (RegisterClass(&window_class) == 0)
	{
		return false;
	}
	// `�p���������u�|�������I��, ���n�ɭn�W�[�����j�p.`
	RECT window_rect;
	SetRect(&window_rect, x, y, x+width, y+height);
	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, FALSE); //WS_POPUPWINDOW�O��ؽu����
	
	// `�ǳƤu�@����, �}�Ҥ@�ӵ���.`
	HWND window_handle = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, //WS_EX_TOPMOST
		title,
		title,
		WS_OVERLAPPEDWINDOW,
		window_rect.left,	// x
		window_rect.top,	// y
		window_rect.right - window_rect.left,	// width
		window_rect.bottom - window_rect.top,	// height
		NULL,
		NULL,
		window_class.hInstance,
		NULL
		);
	if (window_handle == NULL)
		return false;
	m_hWnd = window_handle;	
	return window_handle;
}

MSG Win32Window::HandlePeekMessage()
{
	MSG msg;
	// �D�T���j��:
	if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
	{
		// `���T������, �N�⥦�e���T���B�z�禡.`
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg;
}

HWND Win32Window::GetHandle(void)
{
	return m_hWnd;
}
HINSTANCE Win32Window::GetInstance(void)
{
	return m_hInstance;
}
void Win32Window::GetMouseState(int &x, int &y, int button[3])
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
	x = p.x;
	y = p.y;
	button[0] = GetKeyState(VK_LBUTTON) & 0x80 ? 1 : 0;
	button[1] = GetKeyState(VK_MBUTTON) & 0x80 ? 1 : 0;
	button[2] = GetKeyState(VK_RBUTTON) & 0x80 ? 1 : 0;
}

void Win32Window::ToShow(void)
{
	// `��ܵ���`
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	SetActiveWindow(m_hWnd);
}
void Win32Window::ToHide(void)
{
	// `��ܵ���`
	ShowWindow(m_hWnd, SW_HIDE);
	SetActiveWindow(m_hWnd);
}

void Win32Window::ToMove( UINT x, UINT y, UINT nWidth, UINT nHeight, bool bRepaint /*= true*/ )
{
	MoveWindow(m_hWnd , x, y, nWidth, nHeight, bRepaint);
}

RECT Win32Window::GetRect( void )
{
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	return rect;
}