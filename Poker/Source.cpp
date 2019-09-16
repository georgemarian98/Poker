#include <wchar.h>
#include <windows.h>
#include <set>
#include <map>
#include "Poker.h"
using namespace std;

#pragma warning(disable : 4996)

int main( )
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 10;                   // Width of each character in the font
	cfi.dwFontSize.Y = 16;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Terminal"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	srand(time(NULL));

	for(int i = 0; i < 10; i++){
		Poker joc(5);
		joc.run( );

	}

	return 0;
}