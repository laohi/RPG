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
	// ѡ���ɫ
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
		// ����ѡ�����ҳ�ʼ���������
		SRoleDt* pRoleDt = static_cast<SRoleDt*>(m_vecRoles[m_nSelectIndex]);
		// ���س�ʼ��ͼ
		SMapDt* m_pCurMapDt = static_cast<SMapDt*>(CDataMgr::getInstance()->getDtMgr("MapDtMgr")->getDataByID(1001));
		// ��ʼ�����
		CGameMgr::getInstance()->getGameMap()->init();
		CGameMgr::getInstance()->getGameMap()->getPlayer()->initWithData(pRoleDt);
		// ��ʼ������
		CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->createEnemy();
		// �����ͼ
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		// ��������λ��
		m_nSelectIndex = 0;
		system("cls");
	}
	else if (KEY_DOWN(VK_ESCAPE))
	{
		// ���ز˵�
		CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		// ��������λ��
		m_nSelectIndex = 0;
		system("cls");
	}
}

void CSelectRole::render()
{
	cout << "--------------------�� ��  ɫ ��--------------------\n\n";
	cout << "        " << "����\t" << "Ѫ��\t" << "����\t" << "����\t" << "����" << endl;
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
