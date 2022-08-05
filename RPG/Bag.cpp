#include "stdafx.h"
#include "Bag.h"

CBag::CBag()
{
	m_nSelectIndex = 0;
	m_bIsEditEquip = false;
}

CBag::~CBag()
{
}

void CBag::update()
{
	// 获取玩家
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// 获取玩家背包
	vector<SItemDt*> vecBag = pPlayer->getBag();

	if (m_bIsEditEquip)
	{
		// 选择装备（装备栏）
		if (KEY_DOWN(VK_UP))
		{
			m_nSelectIndex--;
			if (m_nSelectIndex < 0)
			{
				if (vecBag.empty())
				{
					m_nSelectIndex = 3;
				}
				else
				{
					m_nSelectIndex = (int)vecBag.size() - 1;
					// 关闭编辑装备
					m_bIsEditEquip = false;
				}
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nSelectIndex++;
			if (m_nSelectIndex > 3)
			{
				if (vecBag.empty())
				{
					m_nSelectIndex = 0;
				}
				else
				{
					m_nSelectIndex = 0;
					// 关闭编辑装备
					m_bIsEditEquip = false;
				}
			}
		}

		SItemDt* pItemDt = pPlayer->getEquipByIndex(m_nSelectIndex);

		// 脱下装备
		if (KEY_DOWN(VK_RETURN))
		{
			if (!pItemDt)
			{
				return;
			}
			pPlayer->removeItemFromEquip(m_nSelectIndex);
			system("cls");
		}
	}
	else
	{
		// 选择物品（背包）
		if (KEY_DOWN(VK_UP))
		{
			m_nSelectIndex--;
			if (m_nSelectIndex < 0)
			{
				m_nSelectIndex = 3;
				m_bIsEditEquip = true;
			}
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nSelectIndex++;
			if (m_nSelectIndex > (int)vecBag.size() - 1)
			{
				m_nSelectIndex = 0;
				// 开启编辑装备
				m_bIsEditEquip = true;
			}
		}

		// 出售物品
		if (KEY_DOWN(VK_BACK))
		{
			if (vecBag.empty())
			{
				return;
			}

			// 将金钱返回玩家
			pPlayer->setMoney(pPlayer->getMoney() + vecBag[m_nSelectIndex]->m_nMoney);
			// 卖出装备，将物品移出背包
			if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
			{
				pPlayer->removeItemFromBag(m_nSelectIndex);
				m_nSelectIndex--;
			}
			else
			{
				pPlayer->removeItemFromBag(m_nSelectIndex);
				// 如果是最后一个装备，则让光标到装备栏
				if (pPlayer->getBag().size() == 0)
				{
					m_bIsEditEquip = true;
				}
			}

			system("cls");
		}

		// 装备、使用物品
		if (KEY_DOWN(VK_RETURN))
		{
			if (vecBag.empty())
			{
				return;
			}
			if (m_nSelectIndex < 0 || m_nSelectIndex >(int)vecBag.size() - 1)
			{
				return;
			}

			// 属于道具，不能穿到装备栏
			if (vecBag[m_nSelectIndex]->m_nType >= 10)
			{
				// 使用道具
				if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
				{
					pPlayer->useItem(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// 如果该物品只有一个，让索引-1
					m_nSelectIndex--;
				}
				else
				{
					pPlayer->useItem(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// 如果是最后一个装备，则让光标到装备栏
					if (pPlayer->getBag().size() == 0)
					{
						m_bIsEditEquip = true;
					}
				}
			}
			else
			{
				// 穿装备
				if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
				{
					pPlayer->addItemToEquip(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// 如果该物品只有一个，让索引-1
					m_nSelectIndex--;
				}
				else
				{
					pPlayer->addItemToEquip(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// 如果是最后一个装备，则让光标到装备栏
					if (pPlayer->getBag().size() == 0)
					{
						m_bIsEditEquip = true;
					}
				}
			}

			system("cls");
		}
	}

	// 退出背包
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		m_nSelectIndex = 0;
		m_bIsEditEquip = false;
		system("cls");
	}
}

void CBag::render()
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
			if (i == m_nSelectIndex && !m_bIsEditEquip)
			{
				cout << "->  ";
			}
			else
			{
				cout << "    ";
			}
			cout << vecBag[i]->m_strName << "\t";
			cout << "+" << vecBag[i]->m_nHP << "\t";
			cout << "+" << vecBag[i]->m_nMP << "\t";
			cout << "+" << vecBag[i]->m_nAtk << "\t";
			cout << "+" << vecBag[i]->m_nDef << "\t";
			cout << vecBag[i]->m_nCount << endl;
		}
	}

	// 渲染装备栏
	cout << "\n\n--------------------【 装  备 】--------------------\n\n";
	cout << "    \t\t" << "装备\t" << "血量\t" << "蓝量\t" << "攻击\t" << "防御\t" << endl;
	string arrEquipTitle[4] = { "武器", "防具", "鞋子", "宠物" };
	for (int i = 0; i < 4; i++)
	{
		SItemDt* pEquip = pPlayer->getEquipByIndex(i);

		if (i == m_nSelectIndex && m_bIsEditEquip)
		{
			cout << "->  " << arrEquipTitle[i] << "\t";
		}
		else
		{
			cout << "    " << arrEquipTitle[i] << "\t";
		}

		if (!pEquip)
		{
			cout << "空\t0\t0\t0\t0" << endl;
		}
		else
		{
			cout << pEquip->m_strName << "\t";
			cout << "+" << pEquip->m_nHP << "\t";
			cout << "+" << pEquip->m_nMP << "\t";
			cout << "+" << pEquip->m_nAtk << "\t";
			cout << "+" << pEquip->m_nDef << endl;
		}
	}
}
