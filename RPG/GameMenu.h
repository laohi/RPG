#pragma once

enum
{
	E_MENU_START,		// 开始游戏
	E_MENU_SET,			// 游戏设置
	E_MENU_EXIT			// 退出游戏
};

// 游戏菜单
class CGameMenu
{
public:
	CGameMenu();

	~CGameMenu();

	// 数据更新
	void update();

	// 数据渲染
	void render();

private:
	/* 菜单状态 */
	int m_nMenuState;
};
