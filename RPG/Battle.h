#pragma once

enum
{
	E_BATTLE_ATK,
	E_BATTLE_SKILL,
	E_BATTLE_ITEM,
	E_BATTLE_EXIT
};

// ս������
class CBattle
{
public:
	CBattle();

	~CBattle();

	// ���ݳ�ʼ��
	void initEnemy(CEnemy* pEnemy);

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

	/* ���� */
	CC_SYNTHESIZE_READONLY(CEnemy*, m_pEnemy, Enemy);

private:
	/* һ���������� */
	int m_nOperateIndex;

	/* �򿪶����˵� */
	bool m_bOpenSecondMenu;

	/* �������� */
	int m_nSecondIndex;
};
