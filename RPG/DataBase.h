#pragma once

// 数据基类
struct SBaseDt
{
	SBaseDt()
	{
		m_nID = 0;
		m_strName = "";
	}

	virtual ~SBaseDt() {}

	/* 数据ID */
	int m_nID;

	/* 数据名称 */
	string m_strName;
};

// 数据管理者基类
class CBaseDtMgr
{
public:
	CBaseDtMgr() {}

	virtual ~CBaseDtMgr();

	// 加载数据
	virtual void loadData(const string& strPath) = 0;

	// 根据ID获取数据
	SBaseDt* getDataByID(int nID);

	// 获取全部数据
	vector<SBaseDt*> getAllDatas();

	// 获取数据的总条数
	int getDataSize();

protected:
	/* 保存所有的数据 */
	vector<SBaseDt*> m_vecDatas;
};
