// RPG.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "stdafx.h"
#include "DataClass.h"

// 光标移动
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOuput, coord);
}

int main()
{
	// 隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

	srand((unsigned int)time(nullptr));

	// 加载游戏数据
	CLoad::loadGameData();

	while (true)
	{
		// 游戏数据更新
		CGameMgr::getInstance()->update();
		// 游戏数据渲染
		CGameMgr::getInstance()->render();

		gotoxy(0, 0);
		Sleep(66);
	}
	return 0;
}
