#pragma once
#include "Player.h"
#include "NpcMgr.h"
#include "EnemyMgr.h"

// 游戏地图
class CGameMap
{
public:
	CGameMap();

	~CGameMap();

	// 数据初始化
	void init();

	// 数据更新
	void update();

	// 数据渲染
	void render();

	/* 当前地图数据 */
	CC_SYNTHESIZE(SMapDt*, m_pCurMapDt, CurMapDt)

	/* 玩家 */
	CC_SYNTHESIZE_READONLY(CPlayer*, m_pPlayer, Player)

	/* NPC管理者 */
	CC_SYNTHESIZE_READONLY(CNpcMgr*, m_pNpcMgr, NpcMgr)

	/* NPC管理者 */
	CC_SYNTHESIZE_READONLY(CEnemyMgr*, m_pEnemyMgr, EnemyMgr)

private:
};
