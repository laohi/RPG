#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer()
{
	memset(m_arrEquip, 0, sizeof(m_arrEquip));
}

CPlayer::CPlayer(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
	memset(m_arrEquip, 0, sizeof(m_arrEquip));
	m_pPet = nullptr;
}

CPlayer::~CPlayer()
{
	CC_SAFE_DELETE(m_pPet)
}

void CPlayer::initWithData(SRoleDt* pData)
{
	m_nID = pData->m_nID;
	m_strName = pData->m_strName;
	m_nHP = pData->m_nHP;
	m_nMP = pData->m_nMP;
	m_nAtk = pData->m_nAtk;
	m_nDef = pData->m_nDef;
	m_nMoney = pData->m_nMoney;
	m_strPic = pData->m_strPic;
}

void CPlayer::update()
{
	m_nRowBk = m_nRow;
	m_nColBk = m_nCol;

	// ���װ���˳�����ҳ���Ϊ�գ��򴴽�һ������
	if (m_arrEquip[3] && !m_pPet)
	{
		m_pPet = new CPet(m_nRowBk, m_nColBk);
	}

	// ���ж���˳���������ÿ�
	if (!m_arrEquip[3])
	{
		delete m_pPet;
		m_pPet = nullptr;
	}

	// ����ƶ�
	if (KEY_DOWN(VK_UP))
	{
		m_nRow--;
		// ���ó���λ��
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nRow++;
		// ���ó���λ��
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_nCol--;
		// ���ó���λ��
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_nCol++;
		// ���ó���λ��
		setPetPos(m_nRowBk, m_nColBk);
	}

	// ��ȡ��ǰ��ͼ����
	SMapDt* pCurMapDt = CGameMgr::getInstance()->getGameMap()->getCurMapDt();

	// ���ײǽ����
	if (pCurMapDt->m_arrMap[m_nRow][m_nCol] == 1)
	{
		// ��ԭ���λ��
		m_nRow = m_nRowBk;
		m_nCol = m_nColBk;
		// ��ԭ����λ��
		setPetPosBak();
	}

	// �����������
	if (pCurMapDt->m_arrMap[m_nRow][m_nCol] > 1000)
	{
		// ��ȡ��һ�ŵ�ͼ��ID
		int nMapID = pCurMapDt->m_arrMap[m_nRow][m_nCol];
		// ���ݵ�ͼID��ȡ��һ�ŵ�ͼ������
		SMapDt* pNextMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(nMapID));
		// ���µ�ͼ����
		CGameMgr::getInstance()->getGameMap()->setCurMapDt(pNextMapDt);
		// ��������µ�λ��
		m_nRow = pNextMapDt->m_nPlayerRow;
		m_nCol = pNextMapDt->m_nPlayerCol;
		// ���ó���λ��
		setPetPos(m_nRow + 1, m_nCol);
		system("cls");
	}

	// ���뱳��
	if (KEY_DOWN(VK_B))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_BAG);
		// �������Ϊ�գ�������õ�װ����
		if (m_vecBag.empty())
		{
			CGameMgr::getInstance()->getBag()->setIsEditEquip(true);
		}
		system("cls");
	}

	// ��ȡ��ǰ��ͼ
	CGameMap* pGameMap = CGameMgr::getInstance()->getGameMap();

	// ����ƶ�����NPC����
	CNpc* pNpc = CGameMgr::getInstance()->getGameMap()->getNpcMgr()->isExist(m_nRow, m_nCol, pGameMap->getCurMapDt()->m_nID);
	if (pNpc)
	{
		if (pNpc->getType() == 1)
		{
			// ��ԭ���λ��
			m_nRow = m_nRowBk;
			m_nCol = m_nColBk;
			// ��ԭ����λ��
			setPetPosBak();
			// ��ʼ���̵꣬������Ʒ
			CGameMgr::getInstance()->getStore()->initItemWithNpcID(pNpc->getID());
			CGameMgr::getInstance()->setGameScene(E_GAME_STORE);
			system("cls");
		}
	}

	// ����ƶ��������˴���
	CEnemy* pEnemy = pGameMap->getEnemyMgr()->isExist(m_nRow, m_nCol, pGameMap->getCurMapDt()->m_nID);
	if (pEnemy)
	{
		// ��ԭ���λ��
		m_nRow = m_nRowBk;
		m_nCol = m_nColBk;
		// ��ԭ����λ��
		setPetPosBak();
		// ����ս��
		CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE);
		// ��ʼ��ս������
		CGameMgr::getInstance()->getBattle()->initEnemy(pEnemy);
		system("cls");
	}
}

bool CPlayer::isExist(int nRow, int nCol)
{
	if (nRow == m_nRow && nCol == m_nCol)
	{
		return true;
	}
	return false;
}

vector<SItemDt*> CPlayer::getBag()
{
	return m_vecBag;
}

void CPlayer::addItemToBag(SItemDt* pItem)
{
	if (!pItem)
	{
		return;
	}
	for (SItemDt* pData : m_vecBag)
	{
		if (pData->m_nID == pItem->m_nID)
		{
			pData->m_nCount++;
			return;
		}
	}
	pItem->m_nCount = 1;
	m_vecBag.push_back(pItem);
}

void CPlayer::removeItemFromBag(int nIndex)
{
	int nCount = (int)m_vecBag.size() - 1;
	if (nIndex < 0 || nIndex > nCount)
	{
		return;
	}
	if (m_vecBag[nIndex]->m_nCount > 1)
	{
		m_vecBag[nIndex]->m_nCount--;
	}
	else
	{
		m_vecBag.erase(m_vecBag.begin() + nIndex);
	}
}

void CPlayer::removeItemFromBagByID(int nID)
{
	if (m_vecBag.empty())
	{
		return;
	}
	for (int i = 0; i < (int)m_vecBag.size(); i++)
	{
		if (m_vecBag[i]->m_nID == nID)
		{
			removeItemFromBag(i);
			return;
		}
	}
}

void CPlayer::useItem(int nIndex)
{
	SItemDt* pItem = m_vecBag[nIndex];
	// �����������
	useItem(pItem);
}

void CPlayer::useItem(SItemDt* pItem)
{
	// �����������
	m_nHP += pItem->m_nHP;
	m_nMP += pItem->m_nMP;
	m_nAtk += pItem->m_nAtk;
	m_nDef += pItem->m_nDef;
}

void CPlayer::addItemToEquip(SItemDt* pEquip)
{
	if (m_arrEquip[pEquip->m_nType])
	{
		// �Ȱ�װ������ȥ���ٴ���װ��
		removeItemFromEquip(pEquip->m_nType);
		m_arrEquip[pEquip->m_nType] = nullptr;
	}
	m_arrEquip[pEquip->m_nType] = pEquip;

	// �����������
	useItem(pEquip);
}

void CPlayer::removeItemFromEquip(int nIndex)
{
	if (nIndex < 0 || nIndex > 3)
	{
		return;
	}

	SItemDt* pEquip = m_arrEquip[nIndex];

	// ��ȥ�������
	m_nHP -= pEquip->m_nHP;
	// �ж�Ѫ���������ȥװ�������ԣ�С��0����Ѫ����Ϊ1
	if (m_nHP <= 0)
	{
		// m_nHP = 1;
		// ������ж��װ��
		return;
	}
	// �ж������������ȥװ�������ԣ�С��0����������Ϊ0
	m_nMP -= pEquip->m_nMP;
	if (m_nMP < 0)
	{
		m_nHP = 0;
	}
	m_nAtk -= pEquip->m_nAtk;
	m_nDef -= pEquip->m_nDef;

	// ���ص�����
	addItemToBag(m_arrEquip[nIndex]);
	// ��װ�������
	m_arrEquip[nIndex] = nullptr;
}

SItemDt* CPlayer::getEquipByIndex(int nIndex)
{
	if (nIndex < 0 || nIndex > 3)
	{
		return nullptr;
	}
	return m_arrEquip[nIndex];
}

void CPlayer::setPetPos(int nRow, int nCol)
{
	if (m_pPet)
	{
		m_pPet->setPos(nRow, nCol);
	}
}

void CPlayer::setPetPosBak()
{
	if (m_pPet)
	{
		m_pPet->setPosBak();
	}
}
