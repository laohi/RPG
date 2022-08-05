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

	// 如果装备了宠物，并且宠物为空，则创建一个宠物
	if (m_arrEquip[3] && !m_pPet)
	{
		m_pPet = new CPet(m_nRowBk, m_nColBk);
	}

	// 如果卸载了宠物，将宠物置空
	if (!m_arrEquip[3])
	{
		delete m_pPet;
		m_pPet = nullptr;
	}

	// 玩家移动
	if (KEY_DOWN(VK_UP))
	{
		m_nRow--;
		// 设置宠物位置
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nRow++;
		// 设置宠物位置
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_LEFT))
	{
		m_nCol--;
		// 设置宠物位置
		setPetPos(m_nRowBk, m_nColBk);
	}
	else if (KEY_DOWN(VK_RIGHT))
	{
		m_nCol++;
		// 设置宠物位置
		setPetPos(m_nRowBk, m_nColBk);
	}

	// 获取当前地图数据
	SMapDt* pCurMapDt = CGameMgr::getInstance()->getGameMap()->getCurMapDt();

	// 玩家撞墙处理
	if (pCurMapDt->m_arrMap[m_nRow][m_nCol] == 1)
	{
		// 还原玩家位置
		m_nRow = m_nRowBk;
		m_nCol = m_nColBk;
		// 还原宠物位置
		setPetPosBak();
	}

	// 玩家碰传送门
	if (pCurMapDt->m_arrMap[m_nRow][m_nCol] > 1000)
	{
		// 获取下一张地图的ID
		int nMapID = pCurMapDt->m_arrMap[m_nRow][m_nCol];
		// 根据地图ID获取下一张地图的数据
		SMapDt* pNextMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(nMapID));
		// 更新地图数据
		CGameMgr::getInstance()->getGameMap()->setCurMapDt(pNextMapDt);
		// 设置玩家新的位置
		m_nRow = pNextMapDt->m_nPlayerRow;
		m_nCol = pNextMapDt->m_nPlayerCol;
		// 设置宠物位置
		setPetPos(m_nRow + 1, m_nCol);
		system("cls");
	}

	// 进入背包
	if (KEY_DOWN(VK_B))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_BAG);
		// 如果背包为空，光标设置到装备栏
		if (m_vecBag.empty())
		{
			CGameMgr::getInstance()->getBag()->setIsEditEquip(true);
		}
		system("cls");
	}

	// 获取当前地图
	CGameMap* pGameMap = CGameMgr::getInstance()->getGameMap();

	// 玩家移动碰到NPC处理
	CNpc* pNpc = CGameMgr::getInstance()->getGameMap()->getNpcMgr()->isExist(m_nRow, m_nCol, pGameMap->getCurMapDt()->m_nID);
	if (pNpc)
	{
		if (pNpc->getType() == 1)
		{
			// 还原玩家位置
			m_nRow = m_nRowBk;
			m_nCol = m_nColBk;
			// 还原宠物位置
			setPetPosBak();
			// 初始化商店，重置物品
			CGameMgr::getInstance()->getStore()->initItemWithNpcID(pNpc->getID());
			CGameMgr::getInstance()->setGameScene(E_GAME_STORE);
			system("cls");
		}
	}

	// 玩家移动碰到敌人处理
	CEnemy* pEnemy = pGameMap->getEnemyMgr()->isExist(m_nRow, m_nCol, pGameMap->getCurMapDt()->m_nID);
	if (pEnemy)
	{
		// 还原玩家位置
		m_nRow = m_nRowBk;
		m_nCol = m_nColBk;
		// 还原宠物位置
		setPetPosBak();
		// 进入战斗
		CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE);
		// 初始化战斗场景
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
	// 增加玩家属性
	useItem(pItem);
}

void CPlayer::useItem(SItemDt* pItem)
{
	// 增加玩家属性
	m_nHP += pItem->m_nHP;
	m_nMP += pItem->m_nMP;
	m_nAtk += pItem->m_nAtk;
	m_nDef += pItem->m_nDef;
}

void CPlayer::addItemToEquip(SItemDt* pEquip)
{
	if (m_arrEquip[pEquip->m_nType])
	{
		// 先把装备还回去，再穿新装备
		removeItemFromEquip(pEquip->m_nType);
		m_arrEquip[pEquip->m_nType] = nullptr;
	}
	m_arrEquip[pEquip->m_nType] = pEquip;

	// 增加玩家属性
	useItem(pEquip);
}

void CPlayer::removeItemFromEquip(int nIndex)
{
	if (nIndex < 0 || nIndex > 3)
	{
		return;
	}

	SItemDt* pEquip = m_arrEquip[nIndex];

	// 减去玩家属性
	m_nHP -= pEquip->m_nHP;
	// 判断血量，如果减去装备的属性，小于0，则将血量设为1
	if (m_nHP <= 0)
	{
		// m_nHP = 1;
		// 不允许卸下装备
		return;
	}
	// 判断蓝量，如果减去装备的属性，小于0，则将蓝量设为0
	m_nMP -= pEquip->m_nMP;
	if (m_nMP < 0)
	{
		m_nHP = 0;
	}
	m_nAtk -= pEquip->m_nAtk;
	m_nDef -= pEquip->m_nDef;

	// 返回到背包
	addItemToBag(m_arrEquip[nIndex]);
	// 将装备栏清掉
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
