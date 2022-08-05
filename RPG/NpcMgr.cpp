#include "stdafx.h"
#include "NpcMgr.h"

CNpcMgr::CNpcMgr()
{
}

CNpcMgr::~CNpcMgr()
{
}

void CNpcMgr::createNpc()
{
	vector<SBaseDt*> vecDatas = CDataMgr::getInstance()->getDtMgr("NpcDtMgr")->getAllDatas();
	for (SBaseDt* pData : vecDatas)
	{
		SNpcDt* pNpcDt = static_cast<SNpcDt*>(pData);
		CNpc* pNpc = new CNpc(pNpcDt);
		m_vecNpcs.push_back(pNpc);
	}
}

CNpc* CNpcMgr::isExist(int nRow, int nCol, int nMapID)
{
	for (CNpc* pNpc : m_vecNpcs)
	{
		if (pNpc->isExist(nRow, nCol, nMapID))
		{
			return pNpc;
		}
	}
	return nullptr;
}
