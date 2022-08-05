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
	// ��ȡ���
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// ��ȡ��ұ���
	vector<SItemDt*> vecBag = pPlayer->getBag();

	if (m_bIsEditEquip)
	{
		// ѡ��װ����װ������
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
					// �رձ༭װ��
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
					// �رձ༭װ��
					m_bIsEditEquip = false;
				}
			}
		}

		SItemDt* pItemDt = pPlayer->getEquipByIndex(m_nSelectIndex);

		// ����װ��
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
		// ѡ����Ʒ��������
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
				// �����༭װ��
				m_bIsEditEquip = true;
			}
		}

		// ������Ʒ
		if (KEY_DOWN(VK_BACK))
		{
			if (vecBag.empty())
			{
				return;
			}

			// ����Ǯ�������
			pPlayer->setMoney(pPlayer->getMoney() + vecBag[m_nSelectIndex]->m_nMoney);
			// ����װ��������Ʒ�Ƴ�����
			if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
			{
				pPlayer->removeItemFromBag(m_nSelectIndex);
				m_nSelectIndex--;
			}
			else
			{
				pPlayer->removeItemFromBag(m_nSelectIndex);
				// ��������һ��װ�������ù�굽װ����
				if (pPlayer->getBag().size() == 0)
				{
					m_bIsEditEquip = true;
				}
			}

			system("cls");
		}

		// װ����ʹ����Ʒ
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

			// ���ڵ��ߣ����ܴ���װ����
			if (vecBag[m_nSelectIndex]->m_nType >= 10)
			{
				// ʹ�õ���
				if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
				{
					pPlayer->useItem(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// �������Ʒֻ��һ����������-1
					m_nSelectIndex--;
				}
				else
				{
					pPlayer->useItem(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// ��������һ��װ�������ù�굽װ����
					if (pPlayer->getBag().size() == 0)
					{
						m_bIsEditEquip = true;
					}
				}
			}
			else
			{
				// ��װ��
				if (vecBag[m_nSelectIndex]->m_nCount == 1 && m_nSelectIndex > 0)
				{
					pPlayer->addItemToEquip(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// �������Ʒֻ��һ����������-1
					m_nSelectIndex--;
				}
				else
				{
					pPlayer->addItemToEquip(vecBag[m_nSelectIndex]);
					pPlayer->removeItemFromBag(m_nSelectIndex);
					// ��������һ��װ�������ù�굽װ����
					if (pPlayer->getBag().size() == 0)
					{
						m_bIsEditEquip = true;
					}
				}
			}

			system("cls");
		}
	}

	// �˳�����
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
	// ��ȡ��ǰ���
	CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();

	// ��Ⱦ�������״̬
	cout << "--------------------�� ״  ̬ ��--------------------\n\n";
	cout << "    " << "����\t" << "Ѫ��\t" << "����\t" << "����\t" << "����\t" << "��Ǯ\t" << endl;
	cout << "    ";
	cout << pPlayer->getName() << "\t";
	cout << pPlayer->getHP() << "\t";
	cout << pPlayer->getMP() << "\t";
	cout << pPlayer->getAtk() << "\t";
	cout << pPlayer->getDef() << "\t";
	cout << pPlayer->getMoney() << endl;

	// ��ȡ��ǰ��ұ���
	vector<SItemDt*> vecBag = pPlayer->getBag();

	// ��Ⱦ����
	cout << "\n\n--------------------�� ��  �� ��--------------------\n\n";
	if (vecBag.empty())
	{
		cout << "                      ����Ϊ��" << endl;
	}
	else
	{
		cout << "    " << "��Ʒ\t" << "Ѫ��\t" << "����\t" << "����\t" << "����\t" << "����" << endl;
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

	// ��Ⱦװ����
	cout << "\n\n--------------------�� װ  �� ��--------------------\n\n";
	cout << "    \t\t" << "װ��\t" << "Ѫ��\t" << "����\t" << "����\t" << "����\t" << endl;
	string arrEquipTitle[4] = { "����", "����", "Ь��", "����" };
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
			cout << "��\t0\t0\t0\t0" << endl;
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
