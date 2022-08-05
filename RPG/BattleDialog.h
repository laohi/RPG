#pragma once

// ս���Ի�
class CBattleDialog
{
public:
	CBattleDialog();

	~CBattleDialog();

	// ���ݳ�ʼ����nType����������
	void init(CEnemy* pEnemy, int nType);

	// ���ݳ�ʼ����pItem:���ߣ�nType����������
	void init(CEnemy* pEnemy, SItemDt* pItem, int nType);

	// ���ݳ�ʼ����pSkill:���ܣ�nType����������
	void init(CEnemy* pEnemy, SSkillDt* pSkill, int nType);

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

private:
	/* �������� */
	void operateHandle();

	/* ��Ѫ���� */
	int atkHandler(int nAtk, int nDef);

	/* ��� */
	CPlayer* m_pPlayer;

	/* ���� */
	CEnemy* m_pEnemy;

	/* �Ի����� */
	int m_nType;

	/* ���˵Ĺ��� */
	int m_nEnemyAtk;

	/* ��ҵĹ��� */
	int m_nPlayerAtk;

	/* ���� */
	SItemDt* m_pItem;

	/* ���� */
	SSkillDt* m_pSkill;

	/* �Ƿ��ܹ�ʹ�ü��� */
	bool m_bIsEnableSkill;

	/* �Ƿ����ܳɹ� */
	bool m_bIsExitSuccess;
};
