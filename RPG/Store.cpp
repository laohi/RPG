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
	// ��Ʒ������
	int nItemCount = (int)m_vecItems.size();

	// ��ѡ��Ʒ
	if (KEY_DOWN(VK_UP))
	{
		m_nSelectIndex = (m_nSelectIndex + nItemCount - 1) % nItemCount;
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nSelectIndex = (m_nSelectIndex + 1) % nItemCount;
	}

	// ������Ʒ
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

		// ��ȡ���
		CPlayer* pPlayer = CGameMgr::getInstance()->getGameMap()->getPlayer();
		// �������Ʒ
		SItemDt* pItem = m_vecItems[m_nSelectIndex];
		int nMoney = pPlayer->getMoney() - pItem->m_nMoney;
		// �жϽ�Ǯ�Ƿ��㹻
		if (nMoney < 0)
		{
			return;
		}
		// ��Ǯ
		pPlayer->setMoney(nMoney);
		// ���������Ʒ��ӵ�����
		pPlayer->addItemToBag(pItem);

		system("cls");
	}

	// �˳��̵�
	if (KEY_DOWN(VK_ESCAPE))
	{
		CGameMgr::getInstance()->setGameScene(E_GAME_MAP);
		system("cls");
	}
}

void CStore::render()
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

	// ��Ⱦ�̵�
	cout << "\n\n--------------------�� ��  �� ��--------------------\n\n";
	cout << "    " << "��Ʒ\t" << "Ѫ��\t" << "����\t" << "����\t" << "����\t" << "���" << endl;
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
	// ���֮ǰ�̵���Ʒ
	m_vecItems.clear();

	// �õ����е���Ʒ
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getDtMgr("ItemDtMgr")->getAllDatas();

	for (SBaseDt* pData : vecDatas)
	{
		SItemDt* pItemDt = static_cast<SItemDt*>(pData);
		if (pItemDt->m_nNpcID == nNpcID)
		{
			m_vecItems.push_back(pItemDt);
		}
	}

	// ��������λ��
	if (!m_vecItems.empty())
	{
		m_nSelectIndex = 0;
	}
}
