#pragma once

enum
{
	E_MENU_START,		// ��ʼ��Ϸ
	E_MENU_SET,			// ��Ϸ����
	E_MENU_EXIT			// �˳���Ϸ
};

// ��Ϸ�˵�
class CGameMenu
{
public:
	CGameMenu();

	~CGameMenu();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

private:
	/* �˵�״̬ */
	int m_nMenuState;
};
