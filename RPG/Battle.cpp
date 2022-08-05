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
	// ��ȡ��ǰ���
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// ���ܡ���������
	int nIndexCount = 0;
	// ����
	vector<SItemDt*> vecItems;
	// ����
	vector<SSkillDt*> vecSkills;

	// �ж��Ǽ��ܣ����ǵ���
	if (m_nOperateIndex == E_BATTLE_SKILL)// ����
	{
		// ��ȡ��������
		vecSkills = static_cast<CSkillDtMgr*>(CDataMgr::getInstance()->getDtMgr("SkillDtMgr"))->getSkillByRoleID(pPlayer->getID());
		nIndexCount = (int)vecSkills.size();
	}
	else if (m_nOperateIndex == E_BATTLE_ITEM)// ����
	{
		// ��ȡ��������
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

	// �����˵�
	if (m_bOpenSecondMenu)
	{
		// �����˵���������0���ܲ���
		if (nIndexCount > 0)
		{
			// �����˵�ѡ�����
			if (KEY_DOWN(VK_UP))
			{
				m_nSecondIndex = (m_nSecondIndex + nIndexCount - 1) % nIndexCount;
			}
			else if (KEY_DOWN(VK_DOWN))
			{
				m_nSecondIndex = (m_nSecondIndex + 1) % nIndexCount;
			}
		}
		
		// ʹ�ü��ܡ�����
		if (KEY_DOWN(VK_RETURN))
		{
			// �ж��Ǽ��ܣ����ǵ��߶����˵�
			if (m_nOperateIndex == E_BATTLE_SKILL)// ���ܶ����˵�
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, vecSkills[m_nSecondIndex], E_BATTLE_SKILL);
			}
			else if (m_nOperateIndex == E_BATTLE_ITEM && !vecItems.empty())// ���߶����˵�
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				// �жϵ�ǰ�����Ƿ�Ϊ���һ�����ǵĻ�����-1
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
		
		// �˳������˵�
		if (KEY_DOWN(VK_ESCAPE))
		{
			m_bOpenSecondMenu = false;
			m_nSecondIndex = 0;
			system("cls");
		}
	}
	// һ���˵�
	else
	{
		// һ���˵�ѡ��
		if (KEY_DOWN(VK_UP))
		{
			m_nOperateIndex = (m_nOperateIndex + 3) % 4;
		}
		else if (KEY_DOWN(VK_DOWN))
		{
			m_nOperateIndex = (m_nOperateIndex + 1) % 4;
		}

		// һ���˵���ȷ�ϲ���
		if (KEY_DOWN(VK_RETURN))
		{
			// ��ͨ����
			if (m_nOperateIndex == E_BATTLE_ATK)
			{
				CGameMgr::getInstance()->setGameScene(E_GAME_BATTLE_DIALOG);
				CGameMgr::getInstance()->getBattleDialog()->init(m_pEnemy, E_BATTLE_ATK);
				system("cls");
			}
			// �򿪼��ܶ����˵����򿪵��߶����˵�
			else if (m_nOperateIndex == E_BATTLE_SKILL || m_nOperateIndex == E_BATTLE_ITEM)
			{
				m_bOpenSecondMenu = true;
				system("cls");
			}
			// ����
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
	// ��ȡ��ǰ���
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// ��Ⱦ��ҡ���������״̬
	cout << "--------------------�� ״  ̬ ��--------------------\n\n";
	cout << "\t  " << pPlayer->getName() << "\t\t  " << m_pEnemy->getName() << "\n\n";
	cout << "\tѪ��\t" << pPlayer->getHP() << "\t\tѪ��\t" << m_pEnemy->getHP() << endl;
	cout << "\t����\t" << pPlayer->getMP() << "\t\t����\t" << m_pEnemy->getMP() << endl;
	cout << "\t����\t" << pPlayer->getAtk() << "\t\t����\t" << m_pEnemy->getAtk() << endl;
	cout << "\t����\t" << pPlayer->getDef() << "\t\t����\t" << m_pEnemy->getDef() << endl;

	// ��Ⱦ�����˵�
	cout << "\n--------------------�� ��  �� ��--------------------\n\n";
	string arrOperate[4] = { "����", "����", "����", "����" };
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

	// �Ƿ���Ⱦ�����˵�
	if (m_bOpenSecondMenu)
	{
		// �ж��Ǽ��ܣ����ǵ��߶����˵�
		if (m_nOperateIndex == E_BATTLE_SKILL)// ���ܶ����˵�
		{
			cout << "\n--------------------�� ��  �� ��--------------------\n\n";
			cout << "      \t" << " ��  �� \t" << "Ѫ��\t" << "�˺�\t" << "����\n\n";
			vector<SSkillDt*> vecSkills = static_cast<CSkillDtMgr*>(CDataMgr::getInstance()->getDtMgr("SkillDtMgr"))->getSkillByRoleID(pPlayer->getID());
			// �жϼ����Ƿ�Ϊ��
			if (vecSkills.empty())
			{
				cout << "                      ����Ϊ��" << endl;
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
		else if (m_nOperateIndex == E_BATTLE_ITEM)// ���߶����˵�
		{
			cout << "\n--------------------�� ��  �� ��--------------------\n\n";
			cout << "      \t" << "����\t" << "Ѫ��\t" << "����\t" << "����\n\n";
			vector<SItemDt*> vecItems = pPlayer->getBag();
			// �жϵ����Ƿ�Ϊ��
			if (vecItems.empty())
			{
				cout << "                      ����Ϊ��" << endl;
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
