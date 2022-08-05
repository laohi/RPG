#pragma once
#include "DataBase.h"

// 数据管理者管理类
class CDataMgr
{
public:
	~CDataMgr();

	// 获取数据管理者管理类
	static CDataMgr* getInstance();

	// 添加数据管理者
	void addDtMgr(string strName, CBaseDtMgr* pDtMgr);

	// 根据名字获取数据管理者
	CBaseDtMgr* getDtMgr(string strName);

private:
	CDataMgr() {}

	/* 数据管理者管理类（单例） */
	static CDataMgr* m_psInstance;

	/* 保存所有的数据管理者 */
	map<string, CBaseDtMgr*> m_mapDtMgrs;
};
