#include "stdafx.h"
#include "EnemyMgr.h"

CEnemyMgr::CEnemyMgr()
{
}

CEnemyMgr::~CEnemyMgr()
{
	for (unsigned int i = 0; i < m_vecEnemys.size(); i++)
	{
		delete m_vecEnemys[i];
		m_vecEnemys[i] = nullptr;
	}
	m_vecEnemys.clear();
}

void CEnemyMgr::createEnemy()
{
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getDtMgr("EnemyDtMgr")->getAllDatas();
	// 如果容器不为空，清空容器
	if (!vecDatas.empty())
	{
		for (unsigned int i = 0; i < m_vecEnemys.size(); i++)
		{
			delete m_vecEnemys[i];
			m_vecEnemys[i] = nullptr;
		}
		m_vecEnemys.clear();
	}
	for (SBaseDt* pData : vecDatas)
	{
		SEnemyDt* pEnemyDt = static_cast<SEnemyDt*>(pData);
		CEnemy* pEnemy = new CEnemy(pEnemyDt);
		m_vecEnemys.push_back(pEnemy);
	}
}

CEnemy* CEnemyMgr::isExist(int nRow, int nCol, int nMapID)
{
	for (CEnemy* pEnemy : m_vecEnemys)
	{
		if (pEnemy->isExist(nRow, nCol, nMapID))
		{
			return pEnemy;
		}
	}
	return nullptr;
}

CEnemy* CEnemyMgr::getEnemyByID(int nID)
{
	for (CEnemy* pEnemy : m_vecEnemys)
	{
		if (pEnemy->getID() == nID)
		{
			return pEnemy;
		}
	}
	return nullptr;
}

void CEnemyMgr::removeEnemyByID(int nID)
{
	for (unsigned int i = 0; i < m_vecEnemys.size(); i++)
	{
		if (m_vecEnemys[i]->getID() == nID)
		{
			m_vecEnemys.erase(m_vecEnemys.begin() + i);
			return;
		}
	}
}

void CEnemyMgr::createRoundEnemy(int nEnemyID)
{
	// 获取敌人数据
	SEnemyDt* pEnemyDt = static_cast<SEnemyDt*>(CDataMgr::getInstance()->getDtMgr("EnemyDtMgr")->getDataByID(nEnemyID));
	// 获取当前地图
	CGameMap* pGameMap = CGameMgr::getInstance()->getGameMap();
	// 获取当前地数据
	SMapDt* pMapDt = pGameMap->getCurMapDt();
	// 随机生成行列
	int nRow = 0;
	int nCol = 0;

	CNpc* pNpc;
	CEnemy* pEnemy;
	bool bPlayer;

	do {
		// 随机生成行列
		nRow = rand() % (pMapDt->m_nRowCount - 3) + 1;
		nCol = rand() % (pMapDt->m_nColCount - 3) + 1;
		// 判断这个位置，是否有NPC、敌人、玩家
		pNpc = pGameMap->getNpcMgr()->isExist(nRow, nCol, pMapDt->m_nID);
		pEnemy = pGameMap->getEnemyMgr()->isExist(nRow, nCol, pMapDt->m_nID);
		bPlayer = pGameMap->getPlayer()->isExist(nRow, nCol);
		// 如果存在的话，重新生成位置
	} while (pNpc || pEnemy || bPlayer);

	// 创建新的敌人
	CEnemy* pNewEnemy = new CEnemy(pEnemyDt);
	// 设置新的位置
	pNewEnemy->setPosition(nRow, nCol);
	// 添加到容器
	m_vecEnemys.push_back(pNewEnemy);
}
