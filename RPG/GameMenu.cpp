#include "stdafx.h"
#include "GameMenu.h"

CGameMenu::CGameMenu()
{
	m_nMenuState = E_MENU_START;
}

CGameMenu::~CGameMenu()
{
}

void CGameMenu::update()
{
	// 菜单选择
	if (KEY_DOWN(VK_UP))
	{
		m_nMenuState = (m_nMenuState + 2) % 3;
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nMenuState = (m_nMenuState + 1) % 3;
	}

	if (KEY_DOWN(VK_RETURN))
	{
		// 开始游戏
		if (m_nMenuState == E_MENU_START)
		{
			// 进入角色选择界面
			CGameMgr::getInstance()->setGameScene(E_GAME_SELECT);
			system("cls");
		}
		// 退出游戏
		else if (m_nMenuState == E_MENU_EXIT)
		{
			exit(0);
		}
	}
}

void CGameMenu::render()
{
	cout << "■■■■■■■■■■■■■■■■■" << endl;
	cout << "■                              ■" << endl;
	cout << "■  ■■■■ ■■■■ ■■■■  ■" << endl;
	cout << "■  ■    ■ ■    ■ ■        ■" << endl;
	cout << "■  ■■■■ ■■■■ ■        ■" << endl;
	cout << "■  ■■     ■       ■  ■■  ■" << endl;
	cout << "■  ■  ■   ■       ■    ■  ■" << endl;
	cout << "■  ■    ■ ■       ■■■■  ■" << endl;
	cout << "■                              ■" << endl;
	cout << "■         游  戏  菜  单       ■" << endl;
	

	if (m_nMenuState == E_MENU_START)
	{
		cout << "■         -> 游戏开始          ■" << endl;
		cout << "■            游戏设置          ■" << endl;
		cout << "■            游戏退出          ■" << endl;
	}
	else if (m_nMenuState == E_MENU_SET)
	{
		cout << "■            游戏开始          ■" << endl;
		cout << "■         -> 游戏设置          ■" << endl;
		cout << "■            游戏退出          ■" << endl;
	}
	else if (m_nMenuState == E_MENU_EXIT)
	{
		cout << "■            游戏开始          ■" << endl;
		cout << "■            游戏设置          ■" << endl;
		cout << "■         -> 游戏退出          ■" << endl;
	}

	cout << "■                              ■" << endl;
	cout << "■■■■■■■■■■■■■■■■■" << endl;
}
