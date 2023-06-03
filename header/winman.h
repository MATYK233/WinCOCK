#include <windows.h>
#include <winuser.h>

LRESULT CALLBACK WindowProcessMessage(HWND, UINT, WPARAM, LPARAM);
int Register(HINSTANCE HIn,const char * WndClassName);
int quit = 1;





int main()
{
    HMODULE HIn=GetModuleHandle(NULL);

    HWND Hw;
    DWORD TCount;
    const char * deez_nuts = "MyWin";
    const char * WndName = "deez/nuts";
    
    

    if(!Register(HIn,deez_nuts)) return 0;

    Hw=CreateWindowEx(WS_EX_TOPMOST,deez_nuts,WndName,WS_BORDER,
                      0,0,640,480,
                      GetDesktopWindow(),NULL,HIn,NULL);

    if(Hw==NULL) return 0;

	ShowWindow(Hw,SW_SHOW); UpdateWindow(Hw); SetFocus(Hw);

    while(quit) {
        MSG message;
        while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }



        
        // Do game updates here
    }
    
    return 0;

}




LRESULT CALLBACK WindowProcessMessage(HWND window_handle, UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
	case WM_QUIT:
	case WM_DESTROY: {
	    quit = 0;
	} break;
	
	default: { // Message not handled; pass on to default message handling function
	    return DefWindowProc(window_handle, message, wParam, lParam);
	} break;
    }
    return 0;


}

int Register(HINSTANCE HIn, const char * WndClassName )
{
    WNDCLASSEX Wc;

    Wc.cbSize=sizeof(WNDCLASSEX);
    Wc.style=0;
    Wc.lpfnWndProc=WindowProcessMessage;
    Wc.cbClsExtra=0;
    Wc.cbWndExtra=0;
    Wc.hInstance=HIn;
    Wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
    Wc.hCursor=LoadCursor(NULL,IDC_ARROW);
    Wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
    Wc.lpszMenuName=NULL;
    Wc.lpszClassName=WndClassName;
    Wc.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

    return RegisterClassEx(&Wc);
}
