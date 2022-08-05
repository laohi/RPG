#pragma once
#include "Enemy.h"

// ���˹�����
class CEnemyMgr
{
public:
	CEnemyMgr();

	~CEnemyMgr();

	// �������е���
	void createEnemy();

	// �ڵ�ͼĳ��ĳ���Ƿ����
	CEnemy* isExist(int nRow, int nCol, int nMapID);

	/* ����ID��ȡ���� */
	CEnemy* getEnemyByID(int nID);

	/* ����ID�Ƴ����� */
	void removeEnemyByID(int nID);

	/* ���ݵ�ͼID�������ĳ�ֵ��� */
	void createRoundEnemy(int nEnemyID);

private:
	/* �������еĵ��� */
	vector<CEnemy*> m_vecEnemys;
};
