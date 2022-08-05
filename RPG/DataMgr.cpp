#include "stdafx.h"
#include "DataMgr.h"

CDataMgr* CDataMgr::m_psInstance = nullptr;

CDataMgr::~CDataMgr()
{
	map<string, CBaseDtMgr*>::iterator iterator = m_mapDtMgrs.begin();
	for (; iterator != m_mapDtMgrs.end(); iterator++)
	{
		if (iterator->second)
		{
			delete iterator->second;
			iterator->second = nullptr;
		}
	}
	m_mapDtMgrs.clear();
}

CDataMgr* CDataMgr::getInstance()
{
	if (!m_psInstance)
	{
		m_psInstance = new CDataMgr();
	}
	return m_psInstance;
}

void CDataMgr::addDtMgr(string strName, CBaseDtMgr* pDtMgr)
{
	if (strName.empty() || !pDtMgr)
	{
		return;
	}
	m_mapDtMgrs.insert(pair<string, CBaseDtMgr*>(strName, pDtMgr));
}

CBaseDtMgr* CDataMgr::getDtMgr(string strName)
{
	return m_mapDtMgrs.at(strName);
}
