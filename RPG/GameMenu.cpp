#include "stdafx.h"
#include "GameMenu.h"

CGameMenu::CGameMenu()
{
	m_nMenuState = E_MENU_START;
}

CGameMenu::~CGameMenu()
{
}

void CGameMenu::update()
{
	// �˵�ѡ��
	if (KEY_DOWN(VK_UP))
	{
		m_nMenuState = (m_nMenuState + 2) % 3;
	}
	else if (KEY_DOWN(VK_DOWN))
	{
		m_nMenuState = (m_nMenuState + 1) % 3;
	}

	if (KEY_DOWN(VK_RETURN))
	{
		// ��ʼ��Ϸ
		if (m_nMenuState == E_MENU_START)
		{
			// �����ɫѡ�����
			CGameMgr::getInstance()->setGameScene(E_GAME_SELECT);
			system("cls");
		}
		// �˳���Ϸ
		else if (m_nMenuState == E_MENU_EXIT)
		{
			exit(0);
		}
	}
}

void CGameMenu::render()
{
	cout << "����������������������������������" << endl;
	cout << "��                              ��" << endl;
	cout << "��  �������� �������� ��������  ��" << endl;
	cout << "��  ��    �� ��    �� ��        ��" << endl;
	cout << "��  �������� �������� ��        ��" << endl;
	cout << "��  ����     ��       ��  ����  ��" << endl;
	cout << "��  ��  ��   ��       ��    ��  ��" << endl;
	cout << "��  ��    �� ��       ��������  ��" << endl;
	cout << "��                              ��" << endl;
	cout << "��         ��  Ϸ  ��  ��       ��" << endl;
	

	if (m_nMenuState == E_MENU_START)
	{
		cout << "��         -> ��Ϸ��ʼ          ��" << endl;
		cout << "��            ��Ϸ����          ��" << endl;
		cout << "��            ��Ϸ�˳�          ��" << endl;
	}
	else if (m_nMenuState == E_MENU_SET)
	{
		cout << "��            ��Ϸ��ʼ          ��" << endl;
		cout << "��         -> ��Ϸ����          ��" << endl;
		cout << "��            ��Ϸ�˳�          ��" << endl;
	}
	else if (m_nMenuState == E_MENU_EXIT)
	{
		cout << "��            ��Ϸ��ʼ          ��" << endl;
		cout << "��            ��Ϸ����          ��" << endl;
		cout << "��         -> ��Ϸ�˳�          ��" << endl;
	}

	cout << "��                              ��" << endl;
	cout << "����������������������������������" << endl;
}
