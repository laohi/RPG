#pragma once
#include "Npc.h"

// NPC������
class CNpcMgr
{
public:
	CNpcMgr();

	~CNpcMgr();

	// ��������NPC
	void createNpc();

	// �ڵ�ͼĳ��ĳ���Ƿ����
	CNpc* isExist(int nRow, int nCol, int nMapID);

private:
	/* �������е�NPC */
	vector<CNpc*> m_vecNpcs;
};
