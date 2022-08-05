#include "stdafx.h"
#include "Store.h"

CStore::CStore()
{
	m_nSelectIndex = 0;
}

CStore::~CStore()
{
}

void CStore::update()
{
	// 商品总条数
	int nItemCount = (int)m_vecItems.size();

	// 挑选商品
	if (KEY_DOWN(VK_UP))
	{
		m_nSelectIndex = (m_nSelectIndex + nItemCount - 1) % nItemCount;
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nSelectIndex = (m_nSelectIndex + 1) % nItemCount;
	}

	// 购买商品
	if (KEY_DOWN(VK_RETURN))
	{
		if (m_vecItems.empty())
		{
			return;
		}
		if (m_nSelectIndex < 0 || m_nSelectIndex >(int)m_vecItems.size() - 1)
		{
			return;
		}

		// 获取玩家
		CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
		// 购买的物品
		SItemDt* pItem = m_vecItems[m_nSelectIndex];
		int nMoney = pPlayer->getMoney() - pItem->m_nMoney;
		// 判断金钱是否足够
		if (nMoney < 0)
		{
			return;
		}
		// 扣钱
		pPlayer->setMoney(nMoney);
		// 将购买的物品添加到背包
		pPlayer->addItemToBag(pItem);

		system("cls");
	}

	// 退出商店
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		system("cls");
	}
}

void CStore::render()
{
	// 获取当前玩家
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// 渲染玩家属性状态
	cout << "--------------------【 状  态 】--------------------\n\n";
	cout << "    " << "名字\t" << "血量\t" << "蓝量\t" << "攻击\t" << "防御\t" << "金钱\t" << endl;
	cout << "    ";
	cout << pPlayer->getName() << "\t";
	cout << pPlayer->getHP() << "\t";
	cout << pPlayer->getMP() << "\t";
	cout << pPlayer->getAtk() << "\t";
	cout << pPlayer->getDef() << "\t";
	cout << pPlayer->getMoney() << endl;

	// 渲染商店
	cout << "\n\n--------------------【 商  店 】--------------------\n\n";
	cout << "    " << "商品\t" << "血量\t" << "蓝量\t" << "攻击\t" << "防御\t" << "金币" << endl;
	for (unsigned int i = 0; i < m_vecItems.size(); i++)
	{
		if (i == m_nSelectIndex)
		{
			cout << "->  ";
		}
		else
		{
			cout << "    ";
		}
		cout << m_vecItems[i]->m_strName << "\t";
		cout << "+" << m_vecItems[i]->m_nHP << "\t";
		cout << "+" << m_vecItems[i]->m_nMP << "\t";
		cout << "+" << m_vecItems[i]->m_nAtk << "\t";
		cout << "+" << m_vecItems[i]->m_nDef << "\t";
		cout << m_vecItems[i]->m_nMoney << endl;
	}

	// 获取当前玩家背包
	vector<SItemDt*> vecBag = pPlayer->getBag();

	// 渲染背包
	cout << "\n\n--------------------【 背  包 】--------------------\n\n";
	if (vecBag.empty())
	{
		cout << "                      背包为空" << endl;
	}
	else
	{
		cout << "    " << "物品\t" << "血量\t" << "蓝量\t" << "攻击\t" << "防御\t" << "数量" << endl;
		for (unsigned int i = 0; i < vecBag.size(); i++)
		{
			cout << "    ";
			cout << vecBag[i]->m_strName << "\t";
			cout << "+" << vecBag[i]->m_nHP << "\t";
			cout << "+" << vecBag[i]->m_nMP << "\t";
			cout << "+" << vecBag[i]->m_nAtk << "\t";
			cout << "+" << vecBag[i]->m_nDef << "\t";
			cout << vecBag[i]->m_nCount << endl;
		}
	}
}

void CStore::initItemWithNpcID(int nNpcID)
{
	// 清空之前商店物品
	m_vecItems.clear();

	// 拿到所有的商品
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getDtMgr("ItemDtMgr")->getAllDatas();

	for (SBaseDt* pData : vecDatas)
	{
		SItemDt* pItemDt = static_cast<SItemDt*>(pData);
		if (pItemDt->m_nNpcID == nNpcID)
		{
			m_vecItems.push_back(pItemDt);
		}
	}

	// 重置索引位置
	if (!m_vecItems.empty())
	{
		m_nSelectIndex = 0;
	}
}
