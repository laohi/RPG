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
	E_GAME_MENU,			// ��Ϸ�˵�
	E_GAME_SELECT,			// ��ɫѡ��
	E_GAME_MAP,				// ��Ϸ��ͼ
	E_GAME_STORE,			// ��Ϸ�̵�
	E_GAME_BAG,				// ��Ϸ����
	E_GAME_BATTLE,			// ս������
	E_GAME_BATTLE_DIALOG	// ս������
};

// ��Ϸ������
class CGameMgr
{
public:
	~CGameMgr();

	// ��ȡ��Ϸ������
	static CGameMgr* getInstance();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

	/* ��Ϸ���� */
	CC_SYNTHESIZE(int, m_nGameScene, GameScene)

	/* ��Ϸ��ͼ */
	CC_SYNTHESIZE_READONLY(CGameMap*, m_pGameMap, GameMap)

	/* ��Ϸ�̵� */
	CC_SYNTHESIZE_READONLY(CStore*, m_pStore, Store)

	/* ��Ϸ���� */
	CC_SYNTHESIZE_READONLY(CBag*, m_pBag, Bag)

	/* ��Ϸ���� */
	CC_SYNTHESIZE_READONLY(CBattle*, m_pBattle, Battle)

	/* ս���Ի� */
	CC_SYNTHESIZE_READONLY(CBattleDialog*, m_pBattleDialog, BattleDialog)

private:
	CGameMgr();

	/* ��Ϸ�����ߣ������� */
	static CGameMgr* m_psInstance;

	/* ��Ϸ�˵� */
	CGameMenu* m_pGameMenu;

	/* ѡ���ɫ */
	CSelectRole* m_pSelectRole;
};
