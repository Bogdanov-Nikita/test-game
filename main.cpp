#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include "Specification.h"
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")


#define WINDOW_CAPTION		"Game in the game \"Nightmare Realm\""	//Заголовок окна
#define WIN_CAPTION			L"Победа!"			//Заголовок диалогового окна при победе
#define WIN_MSG				L"Поздравляем с Победой!"//Сообщение при победе
#define CLASS_NAME			"Game"				//Имя класса
#define BACKGROUND_COLOR	0xE0E0E0			//фон
#define GRID_COLOR			0x000000			//сетка игрового поля
#define FIELD_COLOR_1		0xFFEB3B			//фишка 1
#define FIELD_COLOR_2		0xFFA726			//фишка 2
#define FIELD_COLOR_3		0xE64A19			//фишка 3
#define FIELD_COLOR_4		0x424242			//блоки
#define FIELD_COLOR_5		BACKGROUND_COLOR	//свободные поля
#define FIELD_CHIP_1_ID		02					//фишка 1
#define FIELD_CHIP_2_ID		0x3					//фишка 2
#define FIELD_CHIP_3_ID		0x4					//фишка 3
#define FIELD_BLOCK_ID		0x1					//блоки
#define FIELD_FREE_ID		0x5					//свободные поля

Specification gameRules;
Array2D Map;
//Загрузка игровой карты и правил
VOID OnLoad(){
	//Specification
	int blockMapId = 1;
    int gameChipsMapId[] = {2,3,4};
    int emptyFieldMapId = 5;
    int gameChipOderId[] = { 2, -1, 3, -1 ,4};
	gameRules = Specification(blockMapId,emptyFieldMapId, 
		gameChipOderId, sizeof(gameChipOderId)/sizeof(int),
		gameChipsMapId, sizeof(gameChipsMapId)/sizeof(int));
	//Game Map
	int a1[] = {2,1,3,1,4},
		a2[] = {5,2,3,5,4},
		a3[] = {2,1,3,1,4},
		a4[] = {2,5,3,5,4},
		a5[] = {2,1,3,1,4};
	int *m[] =	{ a1, a2, a3, a4, a5};
	int size[] = {
		sizeof(a1)/sizeof(int),
		sizeof(a2)/sizeof(int), 
		sizeof(a3)/sizeof(int), 
		sizeof(a4)/sizeof(int), 
		sizeof(a5)/sizeof(int)};
	Map = Array2D(m,5,size);
}

VOID OnPaint(HDC hdc){
	//расположение клеткок (активные области для мышки)
	int x = 50;
	int y =	100;
	int width = 100;
	int height = 100;
	int dimX = -1;
	int dimY = -1;
	int currentX = x;
	int currentY = y;
	//расположение фигурок
	int xGameChip = 55;
	int yGameChip =	105;
	int widthGameChip = 90;
	int heightGameChip = 90;
	int dimXGameChip = 9;
	int dimYGameChip = 9;
	int currentXGameChip = xGameChip;
	int currentYGameChip = yGameChip;
	int roundX = 30;
	int roundY = 30;

	HGDIOBJ originalPen = NULL;
    HGDIOBJ originalBrush = NULL;
    originalPen = SelectObject(hdc,GetStockObject(DC_PEN));
	originalBrush = SelectObject(hdc, GetStockObject(DC_BRUSH));

	for(size_t i = 0; i < Map.getLength(); i++){
		for(size_t j = 0; j < Map.getLineLength(i); j++){

			SetDCPenColor(hdc, GRID_COLOR);
			SetDCBrushColor(hdc, BACKGROUND_COLOR);
			Rectangle(hdc, currentX, currentY, currentX + width, currentY + height);

			SetDCPenColor(hdc, BACKGROUND_COLOR);
			switch(Map.getValue(i,j)) {
				case FIELD_CHIP_1_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_1);
					break;
				case FIELD_CHIP_2_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_2);
					break;
				case FIELD_CHIP_3_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_3);
					break;
				case FIELD_BLOCK_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_4);
					break;
				case FIELD_FREE_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_5);
					break;
			}
			
			RoundRect(hdc, 
				currentXGameChip, currentYGameChip, 
				currentXGameChip + widthGameChip, 
				currentYGameChip + heightGameChip, 
				roundX, roundY);

			currentXGameChip = currentXGameChip + widthGameChip + dimXGameChip;
			currentYGameChip = currentYGameChip;

			currentX = currentX + width + dimX;
			currentY = currentY;
		}
		currentXGameChip = xGameChip;
		currentYGameChip = currentYGameChip + heightGameChip + dimYGameChip;

		currentX = x;
		currentY = currentY + height + dimY;
	}


	currentXGameChip = xGameChip;
	currentYGameChip = yGameChip - 100;


	for(size_t i = 0; i < gameRules.gameChipOderId.size();i++){
		switch(gameRules.gameChipOderId[i]) {
				case FIELD_CHIP_1_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_1);
					break;
				case FIELD_CHIP_2_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_2);
					break;
				case FIELD_CHIP_3_ID:
					SetDCBrushColor(hdc, FIELD_COLOR_3);
					break;
		}if(gameRules.gameChipOderId[i] != NULL_VALUE){
			RoundRect(hdc, 
				currentXGameChip, currentYGameChip, 
				currentXGameChip + widthGameChip, 
				currentYGameChip + heightGameChip, 
				roundX, roundY);
		}
		currentXGameChip = currentXGameChip + widthGameChip + dimXGameChip;
		currentYGameChip = currentYGameChip;
	}
    SelectObject(hdc,originalPen);
	SelectObject(hdc,originalBrush);
}

POINT from;
POINT to;
int selectedBlock = 0;

VOID gameLogicStep(HWND hWnd){
	//механика игры
	//if(!(from.x != 0 && from.y != 0 && to.x != 0 && to.y != 0)){
        //1. Проверка на возможность хода
        if(gameRules.isCanMove(from, to, Map)){
            //2. Выполнение хода
            if(Map.excangeValue(from, to)){
                //3. Проверка на завершеность (выйграли и затем выход)
                if(gameRules.isGamePass(Map)){
					InvalidateRect(hWnd, NULL, TRUE);
					//Победное сообщение
					MessageBox(hWnd,(LPCWSTR)WIN_CAPTION, (LPCWSTR)WIN_MSG, MB_OK);
					SendMessage(hWnd,WM_CLOSE,NULL,NULL);
				}
				InvalidateRect(hWnd, NULL, TRUE);
            }else{
            /*error*/
            }
        }
    //}
}

VOID OnInput(HWND hWnd){
	POINT cursorPoint;
	RECT windowRect;
	GetCursorPos(&cursorPoint);
	GetWindowRect(hWnd,&windowRect);
	//Вычисляем положение куросра относительно окна
	int positionX = cursorPoint.x - windowRect.left - 10;	//корректировка X
	int positionY = cursorPoint.y - windowRect.top - 30;	//корректировка Y

	int x = 50;
	int y =	100;
	int width = 100;
	int height = 100;
	int dimX = -1;
	int dimY = -1;
	int currentX = x;
	int currentY = y;

	int flagOut = 1;

	//Проверка на попадения в квадрат
	for(size_t i = 0; i < Map.getLength(); i++){
		for(size_t j = 0; j < Map.getLineLength(i); j++){
			if(
				(positionX >= currentX) &&
				(positionY >= currentY) && 
				(positionX < (currentX + width)) && 
				(positionY < (currentY + height))
				){
			selectedBlock++;
			flagOut = 0;
				switch(selectedBlock){
					case 1:
						from.x = i;
						from.y = j;
						break;
					case 2:
						to.x = i;
						to.y = j;
						selectedBlock = 0;
						gameLogicStep(hWnd);
					break;
				}
				break;
			}
			currentX = currentX + width + dimX;
			currentY = currentY;
		}
		currentX = x;
		currentY = currentY + height + dimY;
	}
	if(flagOut == 1){
		selectedBlock = 0;
	}
	flagOut = 1;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow){
   HWND                hWnd;
   MSG                 msg;
   WNDCLASS            wndClass;
   GdiplusStartupInput gdiplusStartupInput;
   ULONG_PTR           gdiplusToken;
   
   OnLoad();
   // Инициализация GDI+.
   GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
   
   wndClass.style          = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc    = WndProc;
   wndClass.cbClsExtra     = 0;
   wndClass.cbWndExtra     = 0;
   wndClass.hInstance      = hInstance;
   wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground  = CreateSolidBrush(BACKGROUND_COLOR);
   wndClass.lpszMenuName   = NULL;
   wndClass.lpszClassName  = TEXT(CLASS_NAME);
   
   RegisterClass(&wndClass);
   
   hWnd = CreateWindow(
      TEXT(CLASS_NAME),			// window class name
      TEXT(WINDOW_CAPTION),		// window caption
      WS_OVERLAPPEDWINDOW,      // window style
      CW_USEDEFAULT,            // initial x position
      CW_USEDEFAULT,            // initial y position
      CW_USEDEFAULT,            // initial x size
      CW_USEDEFAULT,            // initial y size
      NULL,                     // parent window handle
      NULL,                     // window menu handle
      hInstance,                // program instance handle
      NULL);                    // creation parameters
      
   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while(GetMessage(&msg, NULL, 0, 0)){
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   
   GdiplusShutdown(gdiplusToken);
   return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch(message){
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			OnPaint(ps.hdc);
			EndPaint(hWnd, &ps);
			return 0;
		case WM_LBUTTONDOWN:			
			OnInput(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
} // WndProc