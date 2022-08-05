#include "stdafx.h"
#include "GameMap.h"

CGameMap::CGameMap()
{
	init();
	// ��ʼ��NPC������
	m_pNpcMgr = new CNpcMgr();
	// ����NPC
	m_pNpcMgr->createNpc();

	// ��ʼ�����˹�����
	m_pEnemyMgr = new CEnemyMgr();
	// ��������
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
	// ���س�ʼ��ͼ
	m_pCurMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(1001));
	// ��ʼ�����
	m_pPlayer = new CPlayer(m_pCurMapDt->m_nPlayerRow, m_pCurMapDt->m_nPlayerCol);
}

void CGameMap::update()
{
	// ���ز˵�
	if (KEY_DOWN(VK_ESCAPE))
	{
		//CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		//system("cls");
	}

	// ������ݸ���
	m_pPlayer->update();
}

void CGameMap::render()
{
	cout << "��ǰλ�ã�" << m_pCurMapDt->m_strName << endl;
	// ��Ⱦ��ͼ
	for (int i = 0; i < m_pCurMapDt->m_nRowCount; i++)
	{
		for (int j = 0; j < m_pCurMapDt->m_nColCount; j++)
		{
			CNpc* pNpc = m_pNpcMgr->isExist(i, j, m_pCurMapDt->m_nID);
			CEnemy* pEnemy = m_pEnemyMgr->isExist(i, j, m_pCurMapDt->m_nID);

			if (1 == m_pCurMapDt->m_arrMap[i][j])
			{
				cout << "��";
			}
			else if (m_pCurMapDt->m_arrMap[i][j] > 1000)
			{
				cout << "��";
			}
			else if (m_pPlayer->isExist(i, j))
			{
				cout << m_pPlayer->getPic();
			}
			else if (m_pPlayer->getPet() && m_pPlayer->getPet()->isExist(i, j))
			{
				cout << "��";
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
