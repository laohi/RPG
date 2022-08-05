#include "stdafx.h"
#include "GameMap.h"

CGameMap::CGameMap()
{
	init();
	// 初始化NPC管理者
	m_pNpcMgr = new CNpcMgr();
	// 创建NPC
	m_pNpcMgr->createNpc();

	// 初始化敌人管理者
	m_pEnemyMgr = new CEnemyMgr();
	// 创建敌人
	//m_pEnemyMgr->createEnemy();
}

CGameMap::~CGameMap()
{
	CC_SAFE_DELETE(m_pCurMapDt)
	CC_SAFE_DELETE(m_pPlayer)
	CC_SAFE_DELETE(m_pNpcMgr)
	CC_SAFE_DELETE(m_pEnemyMgr)
}

void CGameMap::init()
{
	// 加载初始地图
	m_pCurMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(1001));
	// 初始化玩家
	m_pPlayer = new CPlayer(m_pCurMapDt->m_nPlayerRow, m_pCurMapDt->m_nPlayerCol);
}

void CGameMap::update()
{
	// 返回菜单
	if (KEY_DOWN(VK_ESCAPE))
	{
		//CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		//system("cls");
	}

	// 玩家数据更新
	m_pPlayer->update();
}

void CGameMap::render()
{
	cout << "当前位置：" << m_pCurMapDt->m_strName << endl;
	// 渲染地图
	for (int i = 0; i < m_pCurMapDt->m_nRowCount; i++)
	{
		for (int j = 0; j < m_pCurMapDt->m_nColCount; j++)
		{
			CNpc* pNpc = m_pNpcMgr->isExist(i, j, m_pCurMapDt->m_nID);
			CEnemy* pEnemy = m_pEnemyMgr->isExist(i, j, m_pCurMapDt->m_nID);

			if (1 == m_pCurMapDt->m_arrMap[i][j])
			{
				cout << "■";
			}
			else if (m_pCurMapDt->m_arrMap[i][j] > 1000)
			{
				cout << "※";
			}
			else if (m_pPlayer->isExist(i, j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (m_pPlayer->getPet() && m_pPlayer->getPet()->isExist(i, j))
			{
				cout << "Ж";
			}
			else if (pNpc)
			{
				cout << pNpc->getPic();
			}
			else if (pEnemy)
			{
				cout << pEnemy->getPic();
			}
			else if (0 == m_pCurMapDt->m_arrMap[i][j])
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
}
