#include "stdafx.h"
#include "GameMgr.h"

CGameMgr* CGameMgr::m_psInstance = nullptr;

CGameMgr::CGameMgr()
{
	m_nGameScene = E_GAME_MENU;
	m_pGameMenu = new CGameMenu();
	m_pSelectRole = new CSelectRole();
	m_pGameMap = new CGameMap();
	m_pBag = new CBag();
	m_pStore = new CStore();
	m_pBattle = new CBattle();
	m_pBattleDialog = new CBattleDialog();
}

CGameMgr::~CGameMgr()
{
	CC_SAFE_DELETE(m_pGameMenu)
	CC_SAFE_DELETE(m_pSelectRole)
	CC_SAFE_DELETE(m_pGameMap)
	CC_SAFE_DELETE(m_pBag)
	CC_SAFE_DELETE(m_pStore)
	CC_SAFE_DELETE(m_pBattle)
	CC_SAFE_DELETE(m_pBattleDialog)
}

CGameMgr* CGameMgr::getInstance()
{
	if (!m_psInstance)
	{
		m_psInstance = new CGameMgr();
	}
	return m_psInstance;
}

void CGameMgr::update()
{
	if (m_nGameScene == E_GAME_MENU)
	{
		m_pGameMenu->update();
	}
	else if (m_nGameScene == E_GAME_SELECT)
	{
		m_pSelectRole->update();
	}
	else if (m_nGameScene == E_GAME_MAP)
	{
		m_pGameMap->update();
	}
	else if (m_nGameScene == E_GAME_BAG)
	{
		m_pBag->update();
	}
	else if (m_nGameScene == E_GAME_STORE)
	{
		m_pStore->update();
	}
	else if (m_nGameScene == E_GAME_BATTLE)
	{
		m_pBattle->update();
	}
	else if (m_nGameScene == E_GAME_BATTLE_DIALOG)
	{
		m_pBattleDialog->update();
	}
}

void CGameMgr::render()
{
	if (m_nGameScene == E_GAME_MENU)
	{
		m_pGameMenu->render();
	}
	else if (m_nGameScene == E_GAME_SELECT)
	{
		m_pSelectRole->render();
	}
	else if (m_nGameScene == E_GAME_MAP)
	{
		m_pGameMap->render();
	}
	else if (m_nGameScene == E_GAME_BAG)
	{
		m_pBag->render();
	}
	else if (m_nGameScene == E_GAME_STORE)
	{
		m_pStore->render();
	}
	else if (m_nGameScene == E_GAME_BATTLE)
	{
		m_pBattle->render();
	}
	else if (m_nGameScene == E_GAME_BATTLE_DIALOG)
	{
		m_pBattleDialog->render();
	}
}
