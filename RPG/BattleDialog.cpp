#include "stdafx.h"
#include "BattleDialog.h"

CBattleDialog::CBattleDialog()
{
}

CBattleDialog::~CBattleDialog()
{
	CC_SAFE_DELETE(m_pPlayer)
	CC_SAFE_DELETE(m_pEnemy)
}

void CBattleDialog::init(CEnemy* pEnemy, int nType)
{
	m_pEnemy = pEnemy;
	m_nType = nType;
	m_pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	operateHandle();
}

void CBattleDialog::init(CEnemy* pEnemy, SItemDt* pItem, int nType)
{
	m_pEnemy = pEnemy;
	m_pItem = pItem;
	m_nType = nType;
	m_pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	operateHandle();
}

void CBattleDialog::init(CEnemy* pEnemy, SSkillDt* pSkill, int nType)
{
	m_pEnemy = pEnemy;
	m_pSkill = pSkill;
	m_nType = nType;
	m_pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
	operateHandle();
}

void CBattleDialog::update()
{
	if (KEY_DOWN(VK_RETURN))
	{
		// 逃跑成功
		if (m_nType == E_BATTLE_EXIT && m_bIsExitSuccess)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
			system("cls");
			return;
		}

		// 战斗结果判断
		if (m_pPlayer->getHP() <= 0)// 玩家失败
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		}
		else if (m_pEnemy->getHP() <= 0)// 玩家胜利
		{
			// 加钱
			m_pPlayer->setMoney(m_pPlayer->getMoney() + m_pEnemy->getMoney());

			// 删除敌人
			CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->removeEnemyByID(m_pEnemy->getID());
			// 在新的地点创建敌人
			CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->createRoundEnemy(m_pEnemy->getID());
			// 返回地图
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		}
		else// 继续战斗
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE);
		}
		system("cls");
	}
}

void CBattleDialog::render()
{
	string strPlayerName = m_pPlayer->getName();
	string strEnemyName = m_pEnemy->getName();

	// 操作判断
	if (m_nType == E_BATTLE_ATK)// 普通攻击
	{
		cout << strPlayerName << " 使用普通攻击，" << strEnemyName << " 扣了 " << m_nPlayerAtk << " 点血。" << endl;
		cout << strEnemyName << " 使用普通攻击，" << strPlayerName << " 扣了 " << m_nEnemyAtk << " 点血。" << endl;
	}
	else if (m_nType == E_BATTLE_SKILL)// 技能攻击
	{
		// 判断蓝量是否足够使用该技能
		if (m_bIsEnableSkill)
		{
			cout << strPlayerName << " 使用了技能 " << m_pSkill->m_strName << "，加了 " << m_pSkill->m_nHP << " 点血，" << strEnemyName << " 扣了 " << m_nPlayerAtk << " 点血。" << endl;
			cout << strEnemyName << " 使用普通攻击，" << strPlayerName << " 扣了 " << m_nEnemyAtk << " 点血。" << endl;
		}
		else
		{
			cout << "蓝量不足，无法使用技能！";
		}
	}
	else if (m_nType == E_BATTLE_ITEM)// 使用道具
	{
		cout << strPlayerName << " 使用了道具 " << m_pItem->m_strName <<"，加了 " << m_pItem->m_nHP << " 点血，加了 " << m_pItem->m_nMP << " 点蓝。" << endl;
		cout << strEnemyName << " 使用普通攻击，" << strPlayerName << " 扣了 " << m_nEnemyAtk << " 点血。" << endl;
	}
	else if (m_nType == E_BATTLE_EXIT)// 逃跑
	{
		if (m_bIsExitSuccess)// 逃跑成功
		{
			cout << "逃跑成功！三十六计，走为上计~" << endl;
		}
		else// 逃跑失败
		{
			cout << "逃跑失败！" << endl;
			cout << strEnemyName << " 使用普通攻击，" << strPlayerName << " 扣了 " << m_nEnemyAtk << " 点血。" << endl;
		}
	}

	// 战斗结果判断
	if (m_pPlayer->getHP() <= 0)// 玩家失败
	{
		cout << "\n失败乃成功之母，请再接再厉！" << endl;
	}
	else if (m_pEnemy->getHP() <= 0)// 玩家胜利
	{
		cout << "\n恭喜你，胜利了！" << endl;
		cout << "获得 " << m_pEnemy->getMoney() << " 金钱。" << endl;
	}
	
}

void CBattleDialog::operateHandle()
{
	// 操作判断
	if (m_nType == E_BATTLE_ATK)// 普通攻击
	{
		m_nPlayerAtk = atkHandler(m_pPlayer->getAtk(), m_pEnemy->getDef());
		m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
	}
	else if (m_nType == E_BATTLE_SKILL)// 技能攻击
	{
		// 判断蓝量是否足够使用该技能
		m_bIsEnableSkill = m_pPlayer->getMP() - m_pSkill->m_nMP > 0;
		if (m_bIsEnableSkill)
		{
			m_pPlayer->setHP(m_pPlayer->getHP() + m_pSkill->m_nHP);
			m_pPlayer->setMP(m_pPlayer->getMP() - m_pSkill->m_nMP);
			m_nPlayerAtk = m_pSkill->m_nAtk;
			m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
		}
		else
		{
			m_nPlayerAtk = 0;
			m_nEnemyAtk = 0;
		}
	}
	else if (m_nType == E_BATTLE_ITEM)// 使用道具
	{
		m_nPlayerAtk = 0;
		m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
		// 使用道具
		CGameMgr::getInstance()->getGameMap()->getPlayer()->useItem(m_pItem);
		// 从背包移除该道具
		CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItemFromBagByID(m_pItem->m_nID);
	}
	else if (m_nType == E_BATTLE_EXIT)// 逃跑
	{
		int nSuccess = rand() % 30 + 70;
		if (nSuccess > 80)// 逃跑成功
		{
			m_bIsExitSuccess = true;
			return;
		}
		else// 逃跑失败
		{
			m_bIsExitSuccess = false;
			m_nPlayerAtk = 0;
			m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
		}
	}

	// 设置玩家、敌人的血量
	m_pPlayer->setHP(m_pPlayer->getHP() - m_nEnemyAtk);
	m_pEnemy->setHP(m_pEnemy->getHP() - m_nPlayerAtk);
}

int CBattleDialog::atkHandler(int nAtk, int nDef)
{
	return (int)((nAtk * nAtk / (nAtk + nDef)) * ((rand() % 30 + 80) / 100.0));
}
