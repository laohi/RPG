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
		// ���ܳɹ�
		if (m_nType == E_BATTLE_EXIT && m_bIsExitSuccess)
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
			system("cls");
			return;
		}

		// ս������ж�
		if (m_pPlayer->getHP() <= 0)// ���ʧ��
		{
			CGameMgr::getInstance()->setGameScene(E_GAME_MENU);
		}
		else if (m_pEnemy->getHP() <= 0)// ���ʤ��
		{
			// ��Ǯ
			m_pPlayer->setMoney(m_pPlayer->getMoney() + m_pEnemy->getMoney());

			// ɾ������
			CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->removeEnemyByID(m_pEnemy->getID());
			// ���µĵص㴴������
			CGameMgr::getInstance()->getGameMap()->getEnemyMgr()->createRoundEnemy(m_pEnemy->getID());
			// ���ص�ͼ
			CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		}
		else// ����ս��
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

	// �����ж�
	if (m_nType == E_BATTLE_ATK)// ��ͨ����
	{
		cout << strPlayerName << " ʹ����ͨ������" << strEnemyName << " ���� " << m_nPlayerAtk << " ��Ѫ��" << endl;
		cout << strEnemyName << " ʹ����ͨ������" << strPlayerName << " ���� " << m_nEnemyAtk << " ��Ѫ��" << endl;
	}
	else if (m_nType == E_BATTLE_SKILL)// ���ܹ���
	{
		// �ж������Ƿ��㹻ʹ�øü���
		if (m_bIsEnableSkill)
		{
			cout << strPlayerName << " ʹ���˼��� " << m_pSkill->m_strName << "������ " << m_pSkill->m_nHP << " ��Ѫ��" << strEnemyName << " ���� " << m_nPlayerAtk << " ��Ѫ��" << endl;
			cout << strEnemyName << " ʹ����ͨ������" << strPlayerName << " ���� " << m_nEnemyAtk << " ��Ѫ��" << endl;
		}
		else
		{
			cout << "�������㣬�޷�ʹ�ü��ܣ�";
		}
	}
	else if (m_nType == E_BATTLE_ITEM)// ʹ�õ���
	{
		cout << strPlayerName << " ʹ���˵��� " << m_pItem->m_strName <<"������ " << m_pItem->m_nHP << " ��Ѫ������ " << m_pItem->m_nMP << " ������" << endl;
		cout << strEnemyName << " ʹ����ͨ������" << strPlayerName << " ���� " << m_nEnemyAtk << " ��Ѫ��" << endl;
	}
	else if (m_nType == E_BATTLE_EXIT)// ����
	{
		if (m_bIsExitSuccess)// ���ܳɹ�
		{
			cout << "���ܳɹ�����ʮ���ƣ���Ϊ�ϼ�~" << endl;
		}
		else// ����ʧ��
		{
			cout << "����ʧ�ܣ�" << endl;
			cout << strEnemyName << " ʹ����ͨ������" << strPlayerName << " ���� " << m_nEnemyAtk << " ��Ѫ��" << endl;
		}
	}

	// ս������ж�
	if (m_pPlayer->getHP() <= 0)// ���ʧ��
	{
		cout << "\nʧ���˳ɹ�֮ĸ�����ٽ�������" << endl;
	}
	else if (m_pEnemy->getHP() <= 0)// ���ʤ��
	{
		cout << "\n��ϲ�㣬ʤ���ˣ�" << endl;
		cout << "��� " << m_pEnemy->getMoney() << " ��Ǯ��" << endl;
	}
	
}

void CBattleDialog::operateHandle()
{
	// �����ж�
	if (m_nType == E_BATTLE_ATK)// ��ͨ����
	{
		m_nPlayerAtk = atkHandler(m_pPlayer->getAtk(), m_pEnemy->getDef());
		m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
	}
	else if (m_nType == E_BATTLE_SKILL)// ���ܹ���
	{
		// �ж������Ƿ��㹻ʹ�øü���
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
	else if (m_nType == E_BATTLE_ITEM)// ʹ�õ���
	{
		m_nPlayerAtk = 0;
		m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
		// ʹ�õ���
		CGameMgr::getInstance()->getGameMap()->getPlayer()->useItem(m_pItem);
		// �ӱ����Ƴ��õ���
		CGameMgr::getInstance()->getGameMap()->getPlayer()->removeItemFromBagByID(m_pItem->m_nID);
	}
	else if (m_nType == E_BATTLE_EXIT)// ����
	{
		int nSuccess = rand() % 30 + 70;
		if (nSuccess > 80)// ���ܳɹ�
		{
			m_bIsExitSuccess = true;
			return;
		}
		else// ����ʧ��
		{
			m_bIsExitSuccess = false;
			m_nPlayerAtk = 0;
			m_nEnemyAtk = atkHandler(m_pEnemy->getAtk(), m_pPlayer->getDef());
		}
	}

	// ������ҡ����˵�Ѫ��
	m_pPlayer->setHP(m_pPlayer->getHP() - m_nEnemyAtk);
	m_pEnemy->setHP(m_pEnemy->getHP() - m_nPlayerAtk);
}

int CBattleDialog::atkHandler(int nAtk, int nDef)
{
	return (int)((nAtk * nAtk / (nAtk + nDef)) * ((rand() % 30 + 80) / 100.0));
}
