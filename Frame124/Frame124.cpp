// Frame124.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Frame124.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND	g_hWnd;
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRAME124, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRAME124));

    MSG msg;
	msg.message = WM_NULL;

    // 기본 메시지 루프입니다.
	// GetMessage : 종료 메시지를 읽으면 false, 메세지를 읽어오면 true 반환
	// 메세지가 없으면 블로킹 상태에 빠지게 된다.

	CMainGame		MainGame;
	MainGame.Initialize();

	// GetTickCount(); -> 운영체제가 시작된 후로 흐른 시간을 정수 형태로 반환

	DWORD dwOldTime = GetTickCount();



    while (WM_QUIT != msg.message)
    {
		// PeekMessage : 메세지를 읽어오면 true 반환, 읽은 메세지가 없으면 FALSE 반환
		// 마지막 인자값 : PM_REMOVE, PM_NOREMOVE
		
		// PM_REMOVE : 메세지를 읽어옴과 동시에 메세지 큐에서 제거한다.
		// PM_NOREMOVE : 메세지 큐에 메세지가 존재하는지만 파악한다. 메세지를 읽어오려면 GetMessage를 다시 호출해야 한다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 단축키 검사 함수
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				// 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 만들어주는 함수
				TranslateMessage(&msg);
				// 시스템 메세지 큐에서 꺼낸 메세지를 프로그램에서 처리(WndProc)하도록 전달하는 함수
				DispatchMessage(&msg);
			}
		}
		else
		{

			if (dwOldTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				dwOldTime = GetTickCount();
			}	
		}		
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//

// 창 스타일을 디자인하는 함수
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRAME124));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT		rc = { 0,0, WINCX, WINCY };
   
   // 최종적인 윈도우 렉트 창 설정 = rc 사이즈 + 윈도우 기본 창 사이즈 + 메뉴 바 크기 고려
   AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

   // 3인자 : 만들고자 하는 윈도우 창 스타일을 지정
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,			// 생성하는 창의 LEFT, TOP 좌표
	  rc.right - rc.left, 
	   rc.bottom - rc.top,			// 생성하는 창의 가로, 세로 사이즈
	   nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT	rc = { 100, 100, 200, 200 };


    switch (message)
    {
	//case WM_CREATE:
	//	SetTimer(hWnd, 0, 0, 0);
	//	// 2인자 : 타이머의 id번호, 1개 밖에 없어서 0번
	//	// 3인자 : 타이머 주기, 1000 / 1초
	//	// 4인자 : 주기적으로 WM_TIMER 메세지를 발생 시킴
	//	break;

	//case WM_TIMER:
	//	InvalidateRect(hWnd, 0, TRUE);
	//	// 윈도우 화면 창을 갱신하는 함수, 이 함수가 호출되면 WM_PAINT 메세지가 발생
	//	// 2인자 : 윈도우 안에서 갱신할 렉트 범위를 지정, null인 경우 전체영역에 적용
	//	// 3인자 : 갱신되는 상태 유무 확인
	//	break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다.
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다.

			/*MoveToEx(hdc, 100, 100, NULL);
			LineTo(hdc, 200, 100);
			LineTo(hdc, 200, 200);
			LineTo(hdc, 100, 200);
			LineTo(hdc, 100, 100);*/

			/*Rectangle(hdc, 100, 100, 200, 200);
			Ellipse(hdc, 300, 300, 400, 400);*/

			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

            EndPaint(hWnd, &ps);
        }
        break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;	
		}
		break;

    case WM_DESTROY:
		//KillTimer(hWnd, 0); // settimer로 발생한 타이머를 삭제하는 용도
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
