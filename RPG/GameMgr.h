#pragma once
#include "GameMenu.h"
#include "SelectRole.h"
#include "GameMap.h"
#include "Bag.h"
#include "Store.h"
#include "Battle.h"
#include "BattleDialog.h"

enum
{
	E_GAME_MENU,			// 游戏菜单
	E_GAME_SELECT,			// 角色选择
	E_GAME_MAP,				// 游戏地图
	E_GAME_STORE,			// 游戏商店
	E_GAME_BAG,				// 游戏背包
	E_GAME_BATTLE,			// 战斗场景
	E_GAME_BATTLE_DIALOG	// 战斗场景
};

// 游戏管理者
class CGameMgr
{
public:
	~CGameMgr();

	// 获取游戏管理者
	static CGameMgr* getInstance();

	// 数据更新
	void update();

	// 数据渲染
	void render();

	/* 游戏场景 */
	CC_SYNTHESIZE(int, m_nGameScene, GameScene)

	/* 游戏地图 */
	CC_SYNTHESIZE_READONLY(CGameMap*, m_pGameMap, GameMap)

	/* 游戏商店 */
	CC_SYNTHESIZE_READONLY(CStore*, m_pStore, Store)

	/* 游戏背包 */
	CC_SYNTHESIZE_READONLY(CBag*, m_pBag, Bag)

	/* 游戏背包 */
	CC_SYNTHESIZE_READONLY(CBattle*, m_pBattle, Battle)

	/* 战斗对话 */
	CC_SYNTHESIZE_READONLY(CBattleDialog*, m_pBattleDialog, BattleDialog)

private:
	CGameMgr();

	/* 游戏管理者（单例） */
	static CGameMgr* m_psInstance;

	/* 游戏菜单 */
	CGameMenu* m_pGameMenu;

	/* 选择角色 */
	CSelectRole* m_pSelectRole;
};
