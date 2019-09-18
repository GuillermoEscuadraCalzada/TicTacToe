#include "stdafx.h"
#include "TicTacToe.h"
#include <string>
#include <windowsx.h>
#include "Minion.h"
#include "Sword.h"
#include "Shield.h"
#include "Key.h"
#include <sstream>
#include "Boss.h"
#include "Player.h"
#include <iterator>


#include "Sword.h"
#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
const int CELL_SIZE = 100;
HICON hIcon1, hIcon2;
HWND  TextBox, History;
Player player;

char textReaded[20];

using std::map; using std::pair;
string diccionario(string, HWND); void particionDeString(map< string, map<int, string> >, string, vector<string>, HWND); void switchActions(int, int, HWND);

forward_list<Door> doorForwardList; //contenedor de las puertas
vector<Enemy*> enemyVectors; vector<Items*> itemsVectors;


map<int, Room> roomMap = {
	{0,
		Room(doorForwardList = {Door(11,true),
								Door(5,false)},
			 itemsVectors = { new Sword("Espada de Madera",5) }) },
	{1,
		Room(doorForwardList = {Door(4, true),
								Door(8, true) },
			 itemsVectors = {new Sword("Espada de Diamante", 15), new Shield("Escudo de madera", 12)}) },
	{2,
		Room(doorForwardList = {Door(7,false),
								Door(5, true)},
			 itemsVectors = { new Key("Llave de la mente", 19), new HealthPotion("Pocion Chica", 10)}) },
	{3,
		Room(doorForwardList = {Door(14,true)},
			 itemsVectors = {new HealthPotion("Pocion Mediana", 18)})},
	{4,
		Room(doorForwardList = {Door(1,true), Door(6, true), Door(16,true), Door(18,false)})},
	{5,
		Room(doorForwardList = {Door(2,false),
								Door(11, true),
								Door(20, false)},
			 enemyVectors = {new Minion("Meat Boy", 3,1,1), new Minion("Mirage", 4,2,1)})},
	{6,
		Room(doorForwardList = {Door(4, true),
								Door(11, true),
								Door(14, false)},
			itemsVectors = {new Key("Llave de la vida", 9)})},
	{7,
		Room(doorForwardList = {Door(5,true), Door(2,false), Door(12, true)})},
	{8,
		Room(doorForwardList = {Door(13, true), Door(1, true), Door(15, false)},
			 itemsVectors = {new Shield("Escudo de plata", 7)})},
	{9,
		Room(doorForwardList = {Door(16, true), Door(17, true)},
			 enemyVectors = {new Boss("Vladimir", 30, 13, 10)})},
	{10,
		Room(doorForwardList = {Door(15,true)},
			 itemsVectors = {new Sword("Espada de hule", 20), new HealthPotion("Beauty Potion", 20)})},
	{11,
		Room(doorForwardList = {Door(0,true), Door(6,true)})},
	{12,
		Room(doorForwardList = {Door(7, true), Door(13, true)},
			 itemsVectors = {new Sword("Espada de titanio", 8), new HealthPotion("Pocion rejuvenecedora", 50)})},
	{13,
		Room(doorForwardList = {Door(12, true), Door(19, false), Door(8, true)},
			 enemyVectors = {new Boss("Gate Keeper", 50, 25, 40)},
			 itemsVectors = {new Key("Llave blanca", 15)}, "Bienvenido al cuarto del terror!")},
	{14,
		Room(doorForwardList = {Door(6, false), Door(16, true), Door(3, true)})},
	{15,
		Room(doorForwardList = {Door(8, false), Door(10, true)},
			enemyVectors = {new Minion("Sparda", 15, 10, 6)})},
	{16,
		Room(doorForwardList = {Door(4, true), Door(9, true), Door(14, true)},
			 itemsVectors = {new Sword("Espada de diamantina", 15), new Key("Pase de Temporada", 14)})},
	{17,
		Room(doorForwardList = {Door(20, false), Door(9, true)},
			 itemsVectors = {new Shield("Escudo de piedra", 30), new Key("Llave bonita", 8)})},
	{18,
		Room(doorForwardList = {Door(5, true), Door(4, true)}, itemsVectors = {new Shield("Silla defensiva", 6)})},
	{19,
		Room(doorForwardList = {Door(13, true)}, enemyVectors = {new FinalBoss("Diosito", 50, 28, 60)})},
	{20,
		Room(doorForwardList = {Door(17, true)},
			 itemsVectors = {new Sword("Cuchillo de cocina", 30)})},
	{21,
		Room(doorForwardList = {Door(0, true)}, itemsVectors = {new Shield("Bote de basura", 50)})}
};



BOOL GetGameBoardRect(HWND hwnd, RECT* pRect) {
	RECT rc;
	if (GetClientRect(hwnd, &rc)) {
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		pRect->left = (width - CELL_SIZE * 3) / 2;
		pRect->top = (height - CELL_SIZE * 3) / 2;
		pRect->right = pRect->left + CELL_SIZE * 3;
		pRect->bottom = pRect->top + CELL_SIZE * 3;
	
	}
	return TRUE;
}

void DrawLine(HDC hdc, int x1, int y1, int x2, int y2) {

	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
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

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TICTACTOE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TICTACTOE));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



string diccionario(string sentence, HWND hWnd)
{
	//MessageBoxA(hWnd, "Escribe lo que quieras hacer", "Acciones", MB_OK);
		//El usuario escribe una palabra, dicha palabra se buscará dentro del mapa	

		//se ingresa una palabra para despues buscarlo en el mapa

		map< string, map<int, string> > dictionaryMap
		{
		{"abrir", {pair<int,string>(0,"puerta"),
					pair<int,string>(1,"inventario"),
				   pair<int,string>(2,"estadisticas")} },

		{"recoger", {pair<int,string>(10,"espada"),
					 pair<int,string>(11,"escudo"),
					 pair<int,string>(12,"llave"),
					 pair<int, string>(13,"pocion")}},

		{"desbloquear",{pair<int,string>(30,"puerta"),
						pair<int, string>(31,"cuarto"),
						pair<int,string>(32,"recamara"),
						pair<int,string>(33,"habitacion")}},

		{"quiero",{pair<int,string>(40, "curarme"), pair<int,string>(41,"curar")}},

		{"revelar", {pair<int,string>(50,"cuarto"),
					 pair<int,string>(51, "recamara"),
					 pair<int,string>(52,"habitacion")}},

		{"tirar", {pair<int,string>(60,"espada"),
				   pair<int,string>(61,"escudo"),
				   pair<int,string>(62,"llave"),
				   pair<int,string>(63, "pocion")}},

		{"crear",{pair<int, string>(70, "objeto")}},

		{"ver",{pair<int,string>(71, "recetario")}}
		};

		vector<string> vectorForNumbers{
		"0", "1", "2", "3", "4", "5", "6", "7","8","9","10","11","12","13","14","15","16","17","18","19","20"
		};

		particionDeString(dictionaryMap, sentence, vectorForNumbers, hWnd);

	return sentence;
}

void particionDeString(map<string, map<int, string>> verbMap, string search, vector<string> vectorNumber, HWND hWnd)
{

	int numberForSwitch;
	int number = 0;
	std::for_each(search.begin(), search.end(), [](char& c) {
		c = ::tolower(c);
		}); //Todas las palabras del string las convierte en minúsculas.

	string insert = search; //insert toma todo lo que "search" contenga.
	string charDelete = " "; //será el limitador del string, al momento de llegar a un espacio, se detendrá el loop.
	string token; //será una bandera o una meta que obtendrá la palabra antes del espacio.
	size_t positionInString = 0; //posición del string.
	vector<string> stringVector; //vector en donde se ingresarán las palabras del string.
	vector<string> ::iterator numberIt = vectorNumber.begin();

	/*	positionInString buscará llegar hasta el espacio.
		token tomará toda la palabra, después en "stringVector.push_back(token)" guardará dicha palabra.
		insert.erase eliminará lo que ya se ingresó y reiniciará el ciclo.*/
	while (positionInString != string::npos) {
		positionInString = insert.find(charDelete);
		token = insert.substr(0, positionInString);
		stringVector.push_back(token);
		insert.erase(0, positionInString + charDelete.length());
	}

	vector<string> ::iterator secondStringIterator; //Este iterador recorre el vector de strings una segunda vez
	vector<string> ::iterator thirdStringIterator;

	/*Este ciclo sacará los números del string.*/
	for (numberIt; numberIt != vectorNumber.end(); numberIt++)
		for (thirdStringIterator = stringVector.begin(); thirdStringIterator != stringVector.end(); thirdStringIterator++)
			if (*thirdStringIterator == *numberIt)
				number = std::stoi(*thirdStringIterator);

	/*	El primer iterador (firstMapIterator) buscará la primera palabra en el diccionario.
		firstStringIterator buscará dentro del vector de Strings. El if verá si entre estos dos iteradores hay algo de igualdad, en caso de ser cierto lo imprime
		sólo para confirmar.

		secondMapIterator buscará la siguiente palabra dentro de la segunda parte del mapa.
		secondStringIterator reiniciará la busqueda del vector de strings para volver a encontrar una similitud con el iterador anterior. Si se cumple, se imprime.
		Después, se toma el entero del contenedor (map<int,string>), lo guardará e ingresará en el switch. */

	for (map< string, map<int, string>> ::iterator _firstMapIterator = verbMap.begin(); _firstMapIterator != verbMap.end(); _firstMapIterator++)
		for (vector<string> ::iterator _firstStringIterator = stringVector.begin(); _firstStringIterator != stringVector.end(); _firstStringIterator++)
			if (*_firstStringIterator == _firstMapIterator->first) {
				cout << *_firstStringIterator << "\n";
				for (map<int, string> ::iterator _secondMapIterator = _firstMapIterator->second.begin(); _secondMapIterator != _firstMapIterator->second.end(); _secondMapIterator++)
					for (secondStringIterator = stringVector.begin(); secondStringIterator != stringVector.end(); secondStringIterator++)

						if (*secondStringIterator == _secondMapIterator->second) { //Si la segunda palabra del mapa es igual al vector de strings, se imprime.
							cout << *secondStringIterator << "\n";
							numberForSwitch = _secondMapIterator->first;

							cout << number << "\n\n";
							try {
								switchActions(numberForSwitch, number, hWnd);

							}
							catch (std::bad_alloc& e) {
								cout << "Bad_Alloc: " << e.what() << "\n\n";

							}
							catch (std::exception& e) {
								cout << "Exception caught: " << e.what() << "\n\n";
							}
						}
			}
}

void switchActions(int numberForFunction, int numberForDoors, HWND hWnd)
{
	switch (numberForFunction) {
	case 0:
		player.openDoor(roomMap, player.getCurrentRoom(), numberForDoors, hWnd);
		break;


	case 1:
		player.openInventory();
		break;


	case 2:
		player.openStats(hWnd);
		break;


	case 10:
		player.pickUpSword(roomMap, player.getCurrentRoom());
		break;


	case 11:
		player.pickUpShield(roomMap, player.getCurrentRoom());
		break;


	case 12:
		player.pickUpKey(roomMap, player.getCurrentRoom());
		break;


	case 13:
		player.pickUpPotion(roomMap, player.getCurrentRoom());
		break;


	case 30:
		player.unlockDoor(roomMap, player.getCurrentRoom(), numberForDoors, hWnd);
		break;


	case 31:
		player.unlockDoor(roomMap, player.getCurrentRoom(), numberForDoors, hWnd);
		break;


	case 32:
		player.unlockDoor(roomMap, player.getCurrentRoom(), numberForDoors, hWnd);
		break;


	case 33:
		player.unlockDoor(roomMap, player.getCurrentRoom(), numberForDoors, hWnd);
		break;

		
	case 40: 
		player.heal(hWnd, TextBox);
		break;

	case 50:
		player.revealCurrentRoom(roomMap, player.getCurrentRoom(), hWnd);
		break;

	case 51:player.revealCurrentRoom(roomMap, player.getCurrentRoom(), hWnd);
		break;


	case 52: player.revealCurrentRoom(roomMap, player.getCurrentRoom(), hWnd);
		break;


	case 60:
		player.dropSword(roomMap, player.getCurrentRoom());
		break;


	case 61:
		player.dropShield(roomMap, player.getCurrentRoom());
		break;

	case 62:
		player.dropKey(roomMap, player.getCurrentRoom());
		break;


	case 63:
		player.dropPotion(roomMap, player.getCurrentRoom());
		break;

	case 70:
		player.crafting(TextBox, hWnd);
		break;


	case 71:
		player.recipeBook(hWnd);
		break;
	}
}

//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TICTACTOE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hbrBackground  = (HBRUSH)(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TICTACTOE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}



int GetCellNumberFromPoint(HWND hwnd, int x, int y){
	RECT rc;
	POINT pt = { x,y };

	if (GetGameBoardRect(hwnd, &rc)) {
		if (PtInRect(&rc, pt)) {
			x = pt.x - rc.left;
			y = pt.y - rc.top;
			int colum = x / CELL_SIZE;
			int row = y / CELL_SIZE;

			return colum + row * 3;
		}
	}
	return -1;
}

BOOL GetCEellRect(HWND hWnd, int index, RECT* pRect) {
	RECT rcBoard;
	SetRectEmpty(pRect);
	if (index < 0 || index > 8) return false;
	if (GetGameBoardRect(hWnd, &rcBoard)) {
		
		int y = index / 3;
		int x = index % 3;

		pRect->left = rcBoard.left + x * CELL_SIZE;
		pRect->top  = rcBoard.top + y * CELL_SIZE;
		pRect->right = pRect->left + CELL_SIZE;
		pRect->bottom = pRect->top + CELL_SIZE;
		return TRUE;
	}
	return FALSE;
}

/*  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)

  PROPÓSITO: Procesa mensajes de la ventana principal.

  WM_COMMAND  - procesar el menú de aplicaciones
  WM_PAINT    - Pintar la ventana principal
  WM_DESTROY  - publicar un mensaje de salida y volver*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	player.setCurrentRoom(0);
	player.setCurrentHealth(30);
	player.setMaximumHealth(50);
	player.setDamage(2);
	player.itemsVector.push_back(Sword("Espada de diamante", 5));
	player.itemsVector.push_back(Sword("Espada de madera", 5));
	player.potionVector.push_back(HealthPotion("Pocion", 5));
	switch (message)
	{
	case WM_CREATE: {
		//creacion de botones
		hIcon1 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_TICTACTOE));
		hIcon2 = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
		TextBox = CreateWindowA("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 10, 10, 400, 20, hWnd, NULL, NULL, NULL);
		History = CreateWindowA("STATIC","", WS_BORDER | WS_CHILD | WS_VISIBLE, 800, 10, 200, 500, hWnd, NULL, NULL, NULL);
		

		CreateWindowA("BUTTON", "OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 420, 10, 70, 20, hWnd, (HMENU)1, NULL, NULL);

		CreateWindowA("BUTTON", "ATACAR Minion", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 40, 150, 50, hWnd, (HMENU)2, NULL, NULL);
		CreateWindowA("BUTTON", "ATACAR Jefe", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 80, 150, 50, hWnd, (HMENU)3, NULL, NULL);
		CreateWindowA("BUTTON", "ATACAR Jefe Final", WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 120, 150, 50, hWnd, (HMENU)4, NULL, NULL);
		break;
	}


	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Analizar las selecciones de menú:
		switch (wmId)
		{
		case 1: {
			int length = GetWindowTextLength(TextBox) + 1;
			GetWindowTextA(TextBox, textReaded, length);
			MessageBeep(MB_ICONASTERISK);
			diccionario(textReaded, hWnd);
			SetWindowTextA(History, textReaded);
			break;
		}

		case 2: {
			player.fightingMinions(roomMap, player.getCurrentRoom(), hWnd);
			

			break;

		}

		case 3: {
			player.fightingBosses(roomMap, player.getCurrentRoom());
			break;
		}


		case 4: {
			player.fightingFinalBoss(roomMap, player.getCurrentRoom());
			break;
		}



		case ID_FILE_NEW_GAME: {
			MessageBoxA(hWnd, "Estas seguro", "Si", MB_YESNO | MB_ICONQUESTION);

			break;
		}


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

	case WM_LBUTTONDOWN: { //acciones con el mouse izquierdo
		HDC hdc = GetDC(hWnd);
		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		int index = GetCellNumberFromPoint(hWnd, xPos, yPos);
		
		if (hdc) {

			if (index != -1){
				RECT rcCell;
				if (GetCEellRect(hWnd, index, &rcCell)) {
					//FillRect(hdc, &rcCell, (HBRUSH)GetStockBrush(BLACK_BRUSH));
					DrawIcon(hdc, rcCell.left + (CELL_SIZE / 2) - 16, rcCell.top + (CELL_SIZE / 2) - 12, hIcon1);
					DrawIcon(hdc, rcCell.left + (CELL_SIZE / 2) - 16, rcCell.top + (CELL_SIZE/2) - 12, hIcon2);
				}
			}
		}
		break;
	}


	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* pMinMx = (MINMAXINFO*)lParam;
		pMinMx->ptMinTrackSize.x = CELL_SIZE * 5;
		pMinMx->ptMinTrackSize.y = CELL_SIZE * 5;
	}
	break;

    case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rc;
		if (GetGameBoardRect(hWnd, &rc)) {
			RECT rcClient;
			if (GetClientRect(hWnd, &rcClient)) {
				const WCHAR szText[] = L"Holi";
				SetBkMode(hdc, TRANSPARENT);
				SetTextColor(hdc, RGB(30, 150, 62));
				TextOut(hdc, rcClient.right - 100, 200, szText, ARRAYSIZE(szText));
			}
			FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
			//Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
		}


		for (int i = 1; i < 3; i++) {
			DrawLine(hdc, rc.left + CELL_SIZE * i, rc.top, rc.left + CELL_SIZE * i, rc.bottom);
			DrawLine(hdc, rc.left, rc.top + CELL_SIZE * i, rc.right, rc.top + CELL_SIZE * i);
		}
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DestroyIcon(hIcon1);
		DestroyIcon(hIcon2);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
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
