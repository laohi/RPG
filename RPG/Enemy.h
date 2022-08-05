#pragma once

// ����
class CEnemy
{
public:
	CEnemy();

	CEnemy(SEnemyDt* pData);

	~CEnemy();

	// �ڵ�ͼĳ��ĳ���Ƿ����
	bool isExist(int nRow, int nCol, int nMapID);

	// ���õ��˵�λ��
	void setPosition(int nRow, int nCol);

	/* ����ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* �������� */
	CC_SYNTHESIZE_READONLY(string, m_strName, Name)

	/* ��ȾͼƬ */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* ����Ѫ�� */
	CC_SYNTHESIZE(int, m_nHP, HP)

	/* �������� */
	CC_SYNTHESIZE_READONLY(int, m_nMP, MP)

	/* ���˹����� */
	CC_SYNTHESIZE_READONLY(int, m_nAtk, Atk)

	/* ���˷����� */
	CC_SYNTHESIZE_READONLY(int, m_nDef, Def)

	/* ���˵����Ǯ */
	CC_SYNTHESIZE_READONLY(int, m_nMoney, Money)

private:
	/* ���������� */
	int m_nRow;

	/* ���������� */
	int m_nCol;

	/* ������ͼID */
	int m_nMapID;
};
