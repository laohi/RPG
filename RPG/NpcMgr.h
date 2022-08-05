#pragma once
#include "Npc.h"

// NPC管理者
class CNpcMgr
{
public:
	CNpcMgr();

	~CNpcMgr();

	// 创建所有NPC
	void createNpc();

	// 在地图某行某列是否存在
	CNpc* isExist(int nRow, int nCol, int nMapID);

private:
	/* 保存所有的NPC */
	vector<CNpc*> m_vecNpcs;
};
