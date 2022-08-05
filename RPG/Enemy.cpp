#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy()
{
}

CEnemy::CEnemy(SEnemyDt* pData)
{
	m_nID = pData->m_nID;
	m_strName = pData->m_strName;
	m_strPic = pData->m_strPic;
	m_nHP = pData->m_nHP;
	m_nMP = pData->m_nMP;
	m_nAtk = pData->m_nAtk;
	m_nDef = pData->m_nDef;
	m_nRow = pData->m_nRow;
	m_nCol = pData->m_nCol;
	m_nMapID = pData->m_nMapID;
	m_nMoney = pData->m_nMoney;
}

CEnemy::~CEnemy()
{
}

bool CEnemy::isExist(int nRow, int nCol, int nMapID)
{
	if (nRow == m_nRow && nCol == m_nCol && nMapID == m_nMapID)
	{
		return true;
	}
	return false;
}

void CEnemy::setPosition(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
}
