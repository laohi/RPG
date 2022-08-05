#include "stdafx.h"
#include "Battle.h"

CBattle::CBattle()
{
	m_nOperateIndex = E_BATTLE_ATK;
	m_bOpenSecondMenu = false;
	m_nSecondIndex = 0;
}

CBattle::~CBattle()
{
	CC_SAFE_DELETE(m_pEnemy)
}

void CBattle::initEnemy(CEnemy* pEnemy)
{
	m_pEnemy = pEnemy;
	m_bOpenSecondMenu = false;
	m_nOperateIndex = E_BATTLE_ATK;
	m_nSecondIndex = 0;
}

void CBattle::update()
{
	// 获取当前玩家
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// 技能、道具数量
	int nIndexCount = 0;
	// 道具
	vector<SItemDt*> vecItems;
	// 技能
	vector<SSkillDt*> vecSkills;

	// 判断是技能，还是道具
	if (m_nOperateIndex == E_BATTLE_SKILL)// 技能
	{
		// 获取技能数量
		vecSkills = static_cast<CSkillDtMgr*>(CDataMgr::getInstance()->getDtMgr("SkillDtMgr"))->getSkillByRoleID(pPlayer->getID());
		nIndexCount = (int)vecSkills.size();
	}
	else if (m_nOperateIndex == E_BATTLE_ITEM)// 道具
	{
		// 获取道具数量
		vector<SItemDt*> vecAllItems = pPlayer->getBag();
		for (SItemDt* pItem : vecAllItems)
		{
			if (pItem->m_nType >= 10)
			{
				vecItems.push_back(pItem);
				nIndexCount++;
			}
		}
	}

	// 二级菜单
	if (m_bOpenSecondMenu)
	{
		// 二级菜单数量大于0才能操作
		if (nIndexCount > 0)
		{
			// 二级菜单选择操作
			if (KEY_DOWN(VK_UP))
			{
				m_nSecondIndex = (m_nSecondIndex + nIndexCount - 1) % nIndexCount;
			}
			else if (KEY_DOWN(VK_DOWN))
			{
				m_nSecondIndex = (m_nSecondIndex + 1) % nIndexCount;
			}
		}
		
		// 使用技能、道具
		if (KEY_DOWN(VK_RETURN))
		{
			// 判断是技能，还是道具二级菜单
			if (m_nOperateIndex == E_BATTLE_SKILL)// 技能二级菜单
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, vecSkills[m_nSecondIndex], E_BATTLE_SKILL);
			}
			else if (m_nOperateIndex == E_BATTLE_ITEM && !vecItems.empty())// 道具二级菜单
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				// 判断当前道具是否为最后一个，是的话索引-1
				if (vecItems[m_nSecondIndex]->m_nCount == 1 && m_nSecondIndex > 0)
				{
					m_nSecondIndex--;
					CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, vecItems[m_nSecondIndex+1], E_BATTLE_ITEM);
				}
				else
				{
					CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, vecItems[m_nSecondIndex], E_BATTLE_ITEM);
				}
			}
			system("cls");
		}
		
		// 退出二级菜单
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bOpenSecondMenu = false;
			m_nSecondIndex = 0;
			system("cls");
		}
	}
	// 一级菜单
	else
	{
		// 一级菜单选择
		if (KEY_DOWN(VK_UP))
		{
			m_nOperateIndex = (m_nOperateIndex + 3) % 4;
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nOperateIndex = (m_nOperateIndex + 1) % 4;
		}

		// 一级菜单，确认操作
		if (KEY_DOWN(VK_RETURN))
		{
			// 普通攻击
			if (m_nOperateIndex == E_BATTLE_ATK)
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, E_BATTLE_ATK);
				system("cls");
			}
			// 打开技能二级菜单，打开道具二级菜单
			else if (m_nOperateIndex == E_BATTLE_SKILL || m_nOperateIndex == E_BATTLE_ITEM)
			{
				m_bOpenSecondMenu = true;
				system("cls");
			}
			// 逃跑
			else if (m_nOperateIndex == 3)
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, E_BATTLE_EXIT);
				m_nOperateIndex = 0;
				system("cls");
			}
		}
	}
	
}

void CBattle::render()
{
	// 获取当前玩家
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// 渲染玩家、敌人属性状态
	cout << "--------------------【 状  态 】--------------------\n\n";
	cout << "\t  " << pPlayer->getName() << "\t\t  " << m_pEnemy->getName() << "\n\n";
	cout << "\t血量\t" << pPlayer->getHP() << "\t\t血量\t" << m_pEnemy->getHP() << endl;
	cout << "\t蓝量\t" << pPlayer->getMP() << "\t\t蓝量\t" << m_pEnemy->getMP() << endl;
	cout << "\t攻击\t" << pPlayer->getAtk() << "\t\t攻击\t" << m_pEnemy->getAtk() << endl;
	cout << "\t防御\t" << pPlayer->getDef() << "\t\t防御\t" << m_pEnemy->getDef() << endl;

	// 渲染操作菜单
	cout << "\n--------------------【 操  作 】--------------------\n\n";
	string arrOperate[4] = { "攻击", "技能", "道具", "逃跑" };
	for (int i = 0; i < 4; i++)
	{
		if (i == m_nOperateIndex)
		{
			cout << "    ->\t";
		}
		else
		{
			cout << "      \t";
		}
		cout << arrOperate[i] << endl;
	}

	// 是否渲染二级菜单
	if (m_bOpenSecondMenu)
	{
		// 判断是技能，还是道具二级菜单
		if (m_nOperateIndex == E_BATTLE_SKILL)// 技能二级菜单
		{
			cout << "\n--------------------【 技  能 】--------------------\n\n";
			cout << "      \t" << " 名  字 \t" << "血量\t" << "伤害\t" << "蓝量\n\n";
			vector<SSkillDt*> vecSkills = static_cast<CSkillDtMgr*>(CDataMgr::getInstance()->getDtMgr("SkillDtMgr"))->getSkillByRoleID(pPlayer->getID());
			// 判断技能是否为空
			if (vecSkills.empty())
			{
				cout << "                      技能为空" << endl;
			}
			else
			{
				for (int i = 0; i < (int)vecSkills.size(); i++)
				{
					if (m_nSecondIndex == i)
					{
						cout << "    ->\t";
					}
					else
					{
						cout << "      \t";
					}
					cout << vecSkills[i]->m_strName << "\t";
					cout << "+" << vecSkills[i]->m_nHP << "\t";
					cout << vecSkills[i]->m_nAtk << "\t";
					cout << "-" << vecSkills[i]->m_nMP << endl;
				}
			}
		}
		else if (m_nOperateIndex == E_BATTLE_ITEM)// 道具二级菜单
		{
			cout << "\n--------------------【 道  具 】--------------------\n\n";
			cout << "      \t" << "名字\t" << "血量\t" << "蓝量\t" << "数量\n\n";
			vector<SItemDt*> vecItems = pPlayer->getBag();
			// 判断道具是否为空
			if (vecItems.empty())
			{
				cout << "                      道具为空" << endl;
			}
			else
			{
				int nItemIndex = -1;
				for (SItemDt* pItem : vecItems)
				{
					if (pItem->m_nType >= 10)
					{
						nItemIndex++;
						if (m_nSecondIndex == nItemIndex)
						{
							cout << "    ->\t";
						}
						else
						{
							cout << "      \t";
						}
						cout << pItem->m_strName << "\t";
						cout << "+" << pItem->m_nHP << "\t";
						cout << "+" << pItem->m_nMP << "\t";
						cout << pItem->m_nCount << endl;
					}
				}
			}
		}
	}
}
