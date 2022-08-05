#include "stdafx.h"
#include "SelectRole.h"

CSelectRole::CSelectRole()
{
	m_nSelectIndex = 0;
	m_vecRoles = CDataMgr::getInstance()->getDtMgr("RoleDtMgr")->getAllDatas();
}

CSelectRole::~CSelectRole()
{
}

void CSelectRole::update()
{
	int iRoleCount = (int)m_vecRoles.size();
	// 选择角色
	if (KEY_DOWN(VK_UP))
	{
		m_nSelectIndex = (m_nSelectIndex + iRoleCount - 1) % iRoleCount;
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nSelectIndex = (m_nSelectIndex + 1) % iRoleCount;
	}

	if (KEY_DOWN(VK_RETURN))
	{
		// 根据选择的玩家初始化玩家数据
		SRoleDt* pRoleDt = static_cast<SRoleDt*>(m_vecRoles[m_nSelectIndex]);
		// 加载初始地图
		SMapDt* m_pCurMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(1001));
		// 初始化玩家
		CGameMgr::getInstance()->getGameMap()->init();
		CGameMgr::getInstance()->getGameMap()->getPlayer()->initWithData(pRoleDt);
		// 初始化敌人
		CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->createEnemy();
		// 进入地图
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		// 重置索引位置
		m_nSelectIndex = 0;
		system("cls");
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		// 返回菜单
		CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		// 重置索引位置
		m_nSelectIndex = 0;
		system("cls");
	}
}

void CSelectRole::render()
{
	cout << "--------------------【 角  色 】--------------------\n\n";
	cout << "        " << "名字\t" << "血量\t" << "蓝量\t" << "攻击\t" << "防御" << endl;
	for (unsigned int i = 0; i < m_vecRoles.size(); i++)
	{
		SRoleDt* pRoleDt = static_cast<SRoleDt*>(m_vecRoles[i]);
		if (i == m_nSelectIndex)
		{
			cout << "    ->  ";
		}
		else
		{
			cout << "        ";
		}
		cout << pRoleDt->m_strName << "\t";
		cout << pRoleDt->m_nHP << "\t";
		cout << pRoleDt->m_nMP << "\t";
		cout << pRoleDt->m_nAtk << "\t";
		cout << pRoleDt->m_nDef << endl;
	}
}
