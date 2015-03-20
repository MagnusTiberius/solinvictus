#define _WIN32_WINNT 0x0500
#define WINVER 0x0500
#define WIN32_LEAN_AND_MEAN

#include "platform.h"

#include <GL/glew.h>
#include <GL/wglew.h>

//#include "x360pad.h"
#include <windows.h>
#include <stdio.h>
#include "debug_print.h"

typedef struct _WinData
{
	HINSTANCE	m_hInst;	//application handle instance
	HDC			m_hDC;		// Private GDI Device Context
	HGLRC		m_hRC;		// Permanent Rendering Context
	HWND		m_hWnd;		// Holds Our Window Handle
	LARGE_INTEGER m_freqPerformance;
	LARGE_INTEGER m_countPerformance;
	LARGE_INTEGER m_oldCountPerformance;
	FILE* m_debugStream;
	//CX360PadManager m_padManager;

}WinData;


CPlatform winPlatform;
PIXELFORMATDESCRIPTOR pfd;	
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int DefineAndSetPixelFormat(PIXELFORMATDESCRIPTOR* pfd, HDC hdc, int clrBits, int alphaBits, int dphBits, int stnBits)
{
	int pixelFormat;
	ZeroMemory(pfd, sizeof(pfd));
    pfd->nSize = sizeof(pfd);
    pfd->nVersion = 1;
    pfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_TYPE_RGBA;
    pfd->iPixelType = PFD_TYPE_RGBA;
    pfd->cColorBits = clrBits;
	pfd->cAlphaBits = alphaBits;
    pfd->cDepthBits = dphBits;
    pfd->cStencilBits = stnBits;
    pfd->iLayerType = PFD_MAIN_PLANE;
    pixelFormat = ChoosePixelFormat(hdc, pfd);
	return SetPixelFormat(hdc, pixelFormat, pfd);
}

int GetBetterFormat(HDC hdc, CPlatform::MultiSample ms, int clrBits, int alphaBits, int dphBits, int stnBits)
{
	int pixelAttribs[] =
    {
        WGL_SAMPLES_ARB, int(ms), //ois it ok to cast like this?
        WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, clrBits,
        WGL_ALPHA_BITS_ARB, alphaBits,
        WGL_DEPTH_BITS_ARB, dphBits,
        WGL_STENCIL_BITS_ARB, stnBits,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        0
    };
	int* sampleCount = pixelAttribs + 1;
    int* useSampleBuffer = pixelAttribs + 3;
    int pixelFormat = -1;
	unsigned int numFormats;		

	if(ms == CPlatform::MS_0)
		pixelAttribs[3] = GL_FALSE;

	if(!wglChoosePixelFormatARB)
		wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC) wglGetProcAddress("wglChoosePixelFormatARB");

    if (!wglChoosePixelFormatARB)
	{
		d_printf("Couldn't find wglChoosePixelFormatARB\n");
		return -1;
	}
	else
	{
        // Try fewer and fewer samples per pixel till we find one that is supported:
		if(*sampleCount>0)
		{
			while (pixelFormat <=0 && *sampleCount >= 0)
			{
				wglChoosePixelFormatARB(hdc, pixelAttribs, 0, 1, &pixelFormat, &numFormats);
				(*sampleCount)--;
				if (*sampleCount < 0 && pixelFormat <=0)
					d_printf("Couldn't find a suitable MSAA format\n");			
			}
			if (pixelFormat != -1)
				d_printf("MSAA samples : %d\n", *sampleCount);//*binds tighter than +1					
		}
		else
			wglChoosePixelFormatARB(hdc, pixelAttribs, 0, 1, &pixelFormat, &numFormats);
	}
	if(pixelFormat < 0)
		d_printf("Couldn't find a suitable Pixel format\n");			

	return pixelFormat;

}

HGLRC CreateOpenGLContext(HDC hdc, unsigned int mjr, unsigned int mnr)
{
	HGLRC hrc;
	char* pGLQuery = NULL;
	int contextAttribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, mjr,
		WGL_CONTEXT_MINOR_VERSION_ARB, mnr,
		//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
		0
	};
	//see what version we have
	pGLQuery = (char*)(glGetString(GL_VERSION));
	d_printf("Original GL_VERSION : %s\n", pGLQuery);	
	pGLQuery = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	d_printf("Original GLSL : %s\n", pGLQuery);

	//if InitGLFunctions didn't give us the funtion below, get it from the context
	if(!wglCreateContextAttribsARB)//PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress("wglCreateContextAttribsARB");
	//try and make the context we want 
	//http://www.opengl.org/registry/specs/ARB/wgl_create_context.txt  2nd parameter is for sharing...hmmm
    hrc = wglCreateContextAttribsARB(hdc, 0, contextAttribs);    
	return hrc;
}
/*
Create an OpenGL compatible widnows context

-RegisterClassExA
-CreateWindowExA
 maybe use W suffix not A? see http://msdn.microsoft.com/en-us/library/windows/desktop/ms633587(v=vs.85).aspx

*/
LPCWSTR className = L"Welford App";

bool CPlatform::Create(wchar_t* title, int glMajor, int glMinor, int width, int height, int clrBits, int alphaBits, int dphBits, int stnBits,  MultiSample ms)
{	
	WinData* pData = NULL;
	if(m_pData == NULL)
		return false;
	else
		pData = (WinData*)m_pData;
	
		
	pData->m_hInst = GetModuleHandle(0); //http://msdn.microsoft.com/en-us/library/windows/desktop/ms683199(v=vs.85).aspx
	DWORD dwStyle = WS_SYSMENU | WS_POPUP | WS_CAPTION;// | WS_THICKFRAME;
    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;// Window Extended Style http://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
	HGLRC	tempContext;	//we set up the window first before we can get our final rendering context in GL3.0+
    RECT rect;    	
	int windowWidth, windowHeight, windowLeft, windowTop;

    WNDCLASSEXW wc = {				//http://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
		sizeof(WNDCLASSEX), 
		CS_CLASSDC,					// see http://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
		WndProc,					//windows procedure
		0L, 
		0L,
		pData->m_hInst,					//windows instance
		LoadIcon(NULL, IDI_WINLOGO),//icon
		LoadCursor(NULL, IDC_ARROW),//cursor
		0,							//background
		0,							//menu name
		className,					//class name
		0 };						//wclass icon	

	//setup
	m_size.x = width;
	m_size.y = height;

    RegisterClassExW(&wc);
    SetRect(&rect, 0, 0, m_size.x, m_size.y);	//http://msdn.microsoft.com/en-us/library/windows/desktop/ms632667(v=vs.85).aspx

	//adjust the size of the windwwo to allow for borders etc
    AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
    windowWidth = rect.right - rect.left;
    windowHeight = rect.bottom - rect.top;
    windowLeft = GetSystemMetrics(SM_CXSCREEN) / 2 - windowWidth / 2;
    windowTop = GetSystemMetrics(SM_CYSCREEN) / 2 - windowHeight / 2;

	//create the window
    pData->m_hWnd = CreateWindowExW(dwExStyle, className, title, dwStyle, windowLeft, windowTop, windowWidth, windowHeight, 0, 0, 0, 0);
    pData->m_hDC = GetDC(pData->m_hWnd); // what is a device context http://msdn.microsoft.com/en-us/library/dd162467(v=vs.85).aspx

	//set the pixel format, this is really temporary until we get them using GetBetterFormat
    DefineAndSetPixelFormat(&pfd, pData->m_hDC, clrBits, alphaBits, dphBits, stnBits);

	//get gl context, we may change this later
    tempContext = wglCreateContext(pData->m_hDC);
    wglMakeCurrent(pData->m_hDC, tempContext);

	//GLenum a = glGetError();
	//geta  better version of the pixel format?
    int pixelFormat = GetBetterFormat(pData->m_hDC, ms, clrBits, alphaBits, dphBits, stnBits);
	if(pixelFormat >= 0)
	{
		// Win32 allows the pixel format to be set only once per app, so destroy and re-create the app:
		DestroyWindow(pData->m_hWnd);
		pData->m_hWnd = CreateWindowExW(0, className, title, dwStyle, windowLeft, windowTop, windowWidth, windowHeight, 0, 0, 0, 0);
		SetWindowPos(pData->m_hWnd, HWND_TOP, windowLeft, windowTop, windowWidth, windowHeight, 0);
		pData->m_hDC = GetDC(pData->m_hWnd);
		SetPixelFormat(pData->m_hDC, pixelFormat, &pfd);
		tempContext = wglCreateContext(pData->m_hDC);
		wglMakeCurrent(pData->m_hDC, tempContext);
	}

	//VSync?
    if (!true)
		wglSwapIntervalEXT(0);

	GLenum err = glewInit();
	pData->m_hRC = CreateOpenGLContext(pData->m_hDC, glMajor, glMinor);
	if(pData->m_hRC != NULL){
		wglMakeCurrent(0, 0);
		wglMakeCurrent(pData->m_hDC, pData->m_hRC);
		wglDeleteContext(tempContext);
	}
	else{
		pData->m_hRC = tempContext;
	}

	char* pGLQuery = (char*)(glGetString(GL_VERSION));
	d_printf("Change to Version GL_VERSION : %s\n", pGLQuery);
	pGLQuery = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	d_printf("GLSL : %s\n", pGLQuery);
	

	ShowWindow(pData->m_hWnd,SW_SHOW);			// Show The Window
	SetForegroundWindow(pData->m_hWnd);			// Slightly Higher Priority
	SetFocus(pData->m_hWnd);					// Sets Keyboard Focus To The Window	

	return true;
}
void CPlatform::Close(void)
{
	WinData* pData = NULL;
	if(m_pData == NULL)
		return;
	else
		pData = (WinData*)m_pData;

	UnregisterClassW(className, pData->m_hInst);	
}

//------------------------------------------------------------------------
//
// Update the time values
//
//------------------------------------------------------------------------
static float CalculateDT(LARGE_INTEGER& freqPerformance, LARGE_INTEGER& countPerformance, LARGE_INTEGER& oldCountPerformance)
{
	int i=0;
	//get the time elapsed since the last frame-------
	//QueryPerformanceFrequency(&freqPerformance);
	QueryPerformanceCounter(&countPerformance);
	
	float dt = (float)(countPerformance.QuadPart - oldCountPerformance.QuadPart)  /(float)freqPerformance.QuadPart;

	if(dt > 0.1f || dt < 0.0f)//
	{
		dt = 0;
		//QueryPerformanceFrequency(&freqPerformance);
		QueryPerformanceCounter(&countPerformance);
		oldCountPerformance = countPerformance;
	}
	oldCountPerformance = countPerformance;
	return dt;
}

/*
static void ButtonInput(const Button360& src, Button& dst)
{
	dst.ClearStatus();
	if(src.press)
		dst.SetPress();
	if(src.click)
		dst.SetToggle();
}


static void GamePadInput(const CX360Pad& src, Gamepad& dst)
{
	dst.leftStick.x = src.left_thumb.x;
	dst.leftStick.y = src.left_thumb.y;
	dst.rightStick.x = src.right_thumb.x;
	dst.rightStick.y = src.right_thumb.y;	
	dst.leftTrigger = src.L_TRIG.Get();
	dst.rightTrigger = src.R_TRIG.Get();

	ButtonInput(src.DP_UP, dst.d_up);
	ButtonInput(src.DP_DOWN, dst.d_down);
	ButtonInput(src.DP_LEFT, dst.d_left);
	ButtonInput(src.DP_RIGHT, dst.d_right);

	ButtonInput(src.Y, dst.fb_up);
	ButtonInput(src.A, dst.fb_down);
	ButtonInput(src.X, dst.fb_left);
	ButtonInput(src.Y, dst.fb_right);

	ButtonInput(src.START, dst.start);
	ButtonInput(src.SELECT, dst.select);	
}*/

void CPlatform::Tick(void)
{
	WinData* pData = NULL;
	if(m_pData == NULL)
		return;
	else
		pData = (WinData*)m_pData;

	for(unsigned int i=0;i<KB_MAX;i++)
		GetKeyboard().keys[i].UnsetToggle();

	//Time Management
	m_dt = CalculateDT(pData->m_freqPerformance, pData->m_countPerformance, pData->m_oldCountPerformance);

	//Handle Messages
	MSG		msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))	
	{
		if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			m_quit = true;
		else									// If Not, Deal With Window Messages
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}				
	}

	//and position
	POINT mousePos;
	GetCursorPos(&mousePos);
	if(ScreenToClient(pData->m_hWnd, &mousePos))
	{
		//delta mouse position
		m_mouse.dx = m_mouse.px - mousePos.x;
		m_mouse.dy = m_mouse.py - (m_size.y - mousePos.y);
		//current position
		m_mouse.px = mousePos.x;
		m_mouse.py = m_size.y - mousePos.y;
	}
	else
		m_mouse.px = m_mouse.py = 0;
	
	//GamePad
	/*
	pData->m_padManager.Poll();
	pData->m_padManager.UpdatePads();	
	GamePadInput(pData->m_padManager.GetPad(0), m_gamepad);	
	*/
}

void CPlatform::UpdateBuffers(void)
{
	WinData* pData = NULL;
	if(m_pData == NULL)
		return;
	else
		pData = (WinData*)m_pData;
	SwapBuffers(pData->m_hDC);		
}

void CPlatform::ShowDebugConsole(void)
{
	WinData* pData = NULL;
	if(m_pData == NULL)
		return;
	else
		pData = (WinData*)m_pData;

	//display the debug console or not
	if(m_showingDebugConsole == false)
	{
		if(AllocConsole())
		{
			//see : http://comsci.liu.edu/~murali/win32gui/Win32Apps.htm
			m_showingDebugConsole = true;
			freopen_s(&pData->m_debugStream,"CONOUT$", "wt", stdout);
			SetConsoleTitleW(L"Debug Console\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
			d_printf("Test Print\n");
		}
	}	
}
void CPlatform::HideDebugConsole(void)
{
	WinData* pData = NULL;
	if(m_pData == NULL)
		return;
	else
		pData = (WinData*)m_pData;

	if(m_showingDebugConsole == true)
	{
		if(FreeConsole())
		{
			m_showingDebugConsole = false;
			fclose(pData->m_debugStream);
		}
	}
}

static void ConsoleInput(const char c){	}
static void ConsoleKeyInput(const unsigned int k){	}

CPlatform::CPlatform()
{
	WinData* pData = NULL;
	pData = new WinData;
	m_pData = (void*)pData;
	
	pData->m_hDC = NULL;
	pData->m_hRC = NULL;
	pData->m_hWnd = NULL;
	pData->m_hInst = NULL;	
	m_quit = false;
	//time management
	m_dt = 0.0f;
	//clear memory
	memset(&m_mouse, NULL, sizeof(SMouse));
	memset(&m_keyboard, NULL, sizeof(Keyboard));
	memset(&m_gamepad, NULL, sizeof(Gamepad));	
	m_showingDebugConsole = false;
	//pData->m_padManager.Initialise();	

	//set console callback
	m_pConsoleCallback = ConsoleInput;
	m_pConsoleKeyCallback = ConsoleKeyInput;

	//only need to get once
	QueryPerformanceFrequency(&pData->m_freqPerformance);
}

CPlatform::~CPlatform()
{
	Close();
	if(m_pData)
		delete m_pData;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Button tmp;
	unsigned int key_idx = 0;
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)
			{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
				return 0;
			}
			break;
		}
		//WINDOW
		case WM_MOVE:
		{
			winPlatform.GetPosition().x= LOWORD(lParam);
			winPlatform.GetPosition().y = HIWORD(lParam);
			return 0;
		}
		case WM_SIZE:								// Resize The OpenGL Window
		{
			winPlatform.GetSize().x = LOWORD(lParam);
			winPlatform.GetSize().y = HIWORD(lParam);
			return 0;
		}
		//MOUSE
		case WM_MOUSEMOVE:
		case WM_MOUSEWHEEL:
		case WM_MBUTTONDOWN: 
		case WM_MBUTTONUP:
			break;
		case WM_LBUTTONDOWN:
			winPlatform.GetMouse().lmb = true;	break;
		case WM_RBUTTONDOWN:
			winPlatform.GetMouse().rmb  = true; break;
		case WM_LBUTTONUP:
			winPlatform.GetMouse().lmb  = false; break;
		case WM_RBUTTONUP:
			winPlatform.GetMouse().rmb  = false; break;
		//Characters
		case WM_CHAR:
			//d_printf("ascii : %d\n", wParam);
			winPlatform.ConsoleInputCallback(wParam);
			break;
		//KEYS
		case WM_KEYDOWN:
			//d_printf("key w : %d\n", wParam); //MS virtual keyboard
			//OEM scan line
			/*{
				int a = (lParam>>16)&255;
				d_printf("key l : %d\n", a);
			}*/
			{
				if(wParam == VK_ESCAPE){
                    PostQuitMessage(0);
				}
			}
			if(wParam < KB_MAX)
			{
				key_idx = ms_to_keymap[wParam];
				tmp = winPlatform.GetKeyboard().keys[key_idx];		//store old state
				winPlatform.GetKeyboard().keys[key_idx].ClearStatus();
				winPlatform.GetKeyboard().keys[key_idx].SetPress();
				if(tmp.IsPressed() == false)
					winPlatform.GetKeyboard().keys[key_idx].SetToggle();			
				//set the keypress to the console
				winPlatform.ConsoleKeyCallback(key_idx);
			}
			break;			
		case WM_KEYUP: 
			if(wParam < KB_MAX)
			{
				key_idx = ms_to_keymap[wParam];
				tmp = winPlatform.GetKeyboard().keys[key_idx];
				winPlatform.GetKeyboard().keys[key_idx].ClearStatus();			
				if(tmp.IsPressed() == true)
					winPlatform.GetKeyboard().keys[key_idx].SetToggle();
			}
			break;
		//Window
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	}
	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void CPlatform::Quit(void)const{
	ExitProcess( 0 );
}

//---------------
//change this to support multiple instances?
//---------------
CPlatform* GetPlatform(void)
{
	return &winPlatform;
}

extern int PlatformMain(void);

int WINAPI WinMain(	HINSTANCE	hInstance,	HINSTANCE	hPrevInstance,	LPSTR lpCmdLine, int nCmdShow){
	return PlatformMain();
}
