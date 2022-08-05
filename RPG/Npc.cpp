#include "stdafx.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::CNpc(SNpcDt* pData)
{
	m_nID = pData->m_nID;
	m_strName = pData->m_strName;
	m_strPic = pData->m_strPic;
	m_nRow = pData->m_nRow;
	m_nCol = pData->m_nCol;
	m_nMapID = pData->m_nMapID;
	m_nType = pData->m_nType;
}

CNpc::~CNpc()
{
}

bool CNpc::isExist(int nRow, int nCol, int nMapID)
{
	if (nRow == m_nRow && nCol == m_nCol && nMapID == m_nMapID)
	{
		return true;
	}
	return false;
}
