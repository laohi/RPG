#include "stdafx.h"
#include "DataClass.h"

void CLoad::loadGameData()
{
	// 角色
	CRoleDtMgr* pRoleDtMgr = new CRoleDtMgr();
	pRoleDtMgr->loadData("./data/roleDt.txt");
	CDataMgr::getInstance()->addDtMgr("RoleDtMgr", pRoleDtMgr);
	// 地图
	CMapDtMgr* pMapDtMgr = new CMapDtMgr();
	pMapDtMgr->loadData("./data/mapDt.txt");
	CDataMgr::getInstance()->addDtMgr("MapDtMgr", pMapDtMgr);
	// NPC
	CNpcDtMgr* pNpcDtMgr = new CNpcDtMgr();
	pNpcDtMgr->loadData("./data/npcDt.txt");
	CDataMgr::getInstance()->addDtMgr("NpcDtMgr", pNpcDtMgr);
	// 装备、道具
	CItemDtMgr* pItemDtMgr = new CItemDtMgr();
	pItemDtMgr->loadData("./data/itemDt.txt");
	CDataMgr::getInstance()->addDtMgr("ItemDtMgr", pItemDtMgr);
	// 敌人
	CEnemyDtMgr* pEnemyDtMgr = new CEnemyDtMgr();
	pEnemyDtMgr->loadData("./data/enemyDt.txt");
	CDataMgr::getInstance()->addDtMgr("EnemyDtMgr", pEnemyDtMgr);
	// 技能
	CSkillDtMgr* pSkillDtMgr = new CSkillDtMgr();
	pSkillDtMgr->loadData("./data/skillDt.txt");
	CDataMgr::getInstance()->addDtMgr("SkillDtMgr", pSkillDtMgr);
}

void CRoleDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int iCount = 0;
		inFile >> iCount;
		for (int i = 0; i < iCount; i++)
		{
			SRoleDt* pData = new SRoleDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_nHP >> pData->m_nMP;
			inFile >> pData->m_nAtk >> pData->m_nDef;
			inFile >> pData->m_nMoney >> pData->m_strPic;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

void CMapDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SMapDt* pData = new SMapDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_nRowCount >> pData->m_nColCount;
			inFile >> pData->m_nPlayerRow >> pData->m_nPlayerCol;
			for (int nRow = 0; nRow < pData->m_nRowCount; nRow++)
			{
				for (int nCol = 0; nCol < pData->m_nColCount; nCol++)
				{
					inFile >> pData->m_arrMap[nRow][nCol];
				}
			}
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

void CNpcDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SNpcDt* pData = new SNpcDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_strPic;
			inFile >> pData->m_nRow >> pData->m_nCol;
			inFile >> pData->m_nMapID >> pData->m_nType;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

void CItemDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SItemDt* pData = new SItemDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_nHP >> pData->m_nMP;
			inFile >> pData->m_nAtk >> pData->m_nDef;
			inFile >> pData->m_nMoney;
			inFile >> pData->m_nNpcID >> pData->m_nType;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

void CEnemyDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SEnemyDt* pData = new SEnemyDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_strPic;
			inFile >> pData->m_nHP >> pData->m_nMP;
			inFile >> pData->m_nAtk >> pData->m_nDef;
			inFile >> pData->m_nRow >> pData->m_nCol;
			inFile >> pData->m_nMapID >> pData->m_nMoney;
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

void CSkillDtMgr::loadData(const string& strPath)
{
	fstream inFile(strPath);
	if (inFile)
	{
		string str = "";
		getline(inFile, str);
		int nCount = 0;
		inFile >> nCount;
		for (int i = 0; i < nCount; i++)
		{
			SSkillDt* pData = new SSkillDt();
			inFile >> pData->m_nID >> pData->m_strName;
			inFile >> pData->m_nHP >> pData->m_nAtk >> pData->m_nMP;
			inFile >> pData->m_nRoleCount;
			for (int i = 0; i < pData->m_nRoleCount; i++)
			{
				inFile >> pData->m_arrRoles[i];
			}
			m_vecDatas.push_back(pData);
		}
	}
	inFile.close();
}

vector<SSkillDt*> CSkillDtMgr::getSkillByRoleID(int nRoleID)
{
	vector<SSkillDt*> vecSkills;
	for (SBaseDt* pData : m_vecDatas)
	{
		SSkillDt* pSkillData = static_cast<SSkillDt*>(pData);
		for (int i = 0; i < pSkillData->m_nRoleCount; i++)
		{
			if (pSkillData->m_arrRoles[i] == nRoleID)
			{
				vecSkills.push_back(pSkillData);
			}
		}
	}
	return vecSkills;
}
