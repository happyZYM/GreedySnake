#ifndef SCREEN
#define SCREEN
#include<windows.h>
#include<cstdio>
#include<conio.h>
inline void SetLetter(int n)
{
	SetConsoleOutputCP(n);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);        
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); 
CONSOLE_SCREEN_BUFFER_INFO bInfo;
	INPUT_RECORD	mouseRec;
	DWORD			res;
	COORD			crPos, crHome = {0, 0};
void gotoxy(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void SetScreenSize(int x,int y)
{
	char str[50];
	sprintf(str,"mode con cols=%d lines=%d",x,y);
	system(str);
}
void SetColor(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void SetColor(bool fred,bool fgreen,bool fblue,bool bred,bool bgreen,bool bblue)
{
	SetConsoleTextAttribute(
	GetStdHandle(STD_OUTPUT_HANDLE),
	FOREGROUND_INTENSITY
	|FOREGROUND_RED*fred
	|FOREGROUND_GREEN*fgreen
	|FOREGROUND_BLUE*fblue
	|BACKGROUND_RED*bred
	|BACKGROUND_GREEN*bgreen
	|BACKGROUND_BLUE*bblue
	);
}
void SetTitle(char *str)
{
	SetConsoleTitle(str);
}
//keyhited:kbhit()

bool double_click()
{
	ReadConsoleInput(hIn, &mouseRec, 1, &res);
	return (
	mouseRec.EventType == MOUSE_EVENT
	&&mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED
	&&mouseRec.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK);
}
bool left_click()
{
	return (
	mouseRec.EventType == MOUSE_EVENT
	&&mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED);
}
bool right_click()
{
	return (
	mouseRec.EventType == MOUSE_EVENT
	&&mouseRec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED);
}
int mpX()
{
	ReadConsoleInput(hIn, &mouseRec, 1, &res);
	crPos = mouseRec.Event.MouseEvent.dwMousePosition;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	return crPos.X;
}
int mpY()
{
	ReadConsoleInput(hIn, &mouseRec, 1, &res);
	crPos = mouseRec.Event.MouseEvent.dwMousePosition;
	GetConsoleScreenBufferInfo(hOut, &bInfo);
	return crPos.Y;
}
void finish_handle()
{
	CloseHandle(hOut);
	CloseHandle(hIn);
}
void hm()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;//¸³1ÎªÏÔÊ¾£¬¸³0ÎªÒþ²Ø
    SetConsoleCursorInfo(hOut,&cci);
}
void sm()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=1;//¸³1ÎªÏÔÊ¾£¬¸³0ÎªÒþ²Ø
    SetConsoleCursorInfo(hOut,&cci);
}
#endif
