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
	// ���������Ϊ�գ��������
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
	// ��ȡ��������
	SEnemyDt* pEnemyDt = static_cast<SEnemyDt*>(CDataMgr::getInstance()->getDtMgr("EnemyDtMgr")->getDataByID(nEnemyID));
	// ��ȡ��ǰ��ͼ
	CGameMap* pGameMap = CGameMgr::getInstance()->getGameMap();
	// ��ȡ��ǰ������
	SMapDt* pMapDt = pGameMap->getCurMapDt();
	// �����������
	int nRow = 0;
	int nCol = 0;

	CNpc* pNpc;
	CEnemy* pEnemy;
	bool bPlayer;

	do {
		// �����������
		nRow = rand() % (pMapDt->m_nRowCount - 3) + 1;
		nCol = rand() % (pMapDt->m_nColCount - 3) + 1;
		// �ж����λ�ã��Ƿ���NPC�����ˡ����
		pNpc = pGameMap->getNpcMgr()->isExist(nRow, nCol, pMapDt->m_nID);
		pEnemy = pGameMap->getEnemyMgr()->isExist(nRow, nCol, pMapDt->m_nID);
		bPlayer = pGameMap->getPlayer()->isExist(nRow, nCol);
		// ������ڵĻ�����������λ��
	} while (pNpc || pEnemy || bPlayer);

	// �����µĵ���
	CEnemy* pNewEnemy = new CEnemy(pEnemyDt);
	// �����µ�λ��
	pNewEnemy->setPosition(nRow, nCol);
	// ��ӵ�����
	m_vecEnemys.push_back(pNewEnemy);
}
