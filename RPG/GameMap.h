#pragma once
#include "Player.h"
#include "NpcMgr.h"
#include "EnemyMgr.h"

// ��Ϸ��ͼ
class CGameMap
{
public:
	CGameMap();

	~CGameMap();

	// ���ݳ�ʼ��
	void init();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

	/* ��ǰ��ͼ���� */
	CC_SYNTHESIZE(SMapDt*, m_pCurMapDt, CurMapDt)

	/* ��� */
	CC_SYNTHESIZE_READONLY(CPlayer*, m_pPlayer, Player)

	/* NPC������ */
	CC_SYNTHESIZE_READONLY(CNpcMgr*, m_pNpcMgr, NpcMgr)

	/* NPC������ */
	CC_SYNTHESIZE_READONLY(CEnemyMgr*, m_pEnemyMgr, EnemyMgr)

private:
};
