#pragma once
#include "DataBase.h"

// 加载游戏数据（代理类）
class CLoad
{
public:
	CLoad() {}

	~CLoad() {}

	// 加载游戏数据
	static void loadGameData();
};

// 角色数据
struct SRoleDt :public SBaseDt
{
	SRoleDt()
	{
		m_nHP = 0;
		m_nMP = 0;
		m_nAtk = 0;
		m_nDef = 0;
		m_nMoney = 0;
		m_strPic = "";
	}

	/* 血量 */
	int m_nHP;

	/* 蓝量 */
	int m_nMP;

	/* 攻击力 */
	int m_nAtk;

	/* 防御力 */
	int m_nDef;

	/* 金钱 */
	int m_nMoney;

	/* 渲染图片 */
	string m_strPic;
};

// 角色数据管理者
class CRoleDtMgr :public CBaseDtMgr
{
public:
	CRoleDtMgr() {}

	~CRoleDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);
};

// 地图数据
struct SMapDt :public SBaseDt
{
	SMapDt()
	{
		m_nRowCount = 0;
		m_nColCount = 0;
		m_nPlayerRow = 0;
		m_nPlayerCol = 0;
		memset(m_arrMap, 0, sizeof(m_arrMap));
	}

	/* 总行数 */
	int m_nRowCount;

	/* 总列数 */
	int m_nColCount;

	/* 玩家初始化行 */
	int m_nPlayerRow;

	/* 玩家初始化列 */
	int m_nPlayerCol;

	/* 地图数据 */
	int m_arrMap[100][100];
};

// 地图数据管理者
class CMapDtMgr :public CBaseDtMgr
{
public:
	CMapDtMgr() {}
	~CMapDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);
};

// NPC数据
struct SNpcDt :public SBaseDt
{
	SNpcDt()
	{
		m_strPic = "";
		m_nRow = 0;
		m_nCol = 0;
		m_nMapID = 0;
		m_nType = 0;
	}

	/* 渲染图片 */
	string m_strPic;

	/* NPC所在行 */
	int m_nRow;

	/* NPC所在列 */
	int m_nCol;

	/* 所属地图ID */
	int m_nMapID;

	/* NPC类型 */
	int m_nType;
};

// NPC数据管理者
class CNpcDtMgr :public CBaseDtMgr
{
public:
	CNpcDtMgr() {}
	~CNpcDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);
};

// 装备、道具数据
struct SItemDt :public SBaseDt
{
	SItemDt()
	{
		m_nHP = 0;
		m_nMP = 0;
		m_nAtk = 0;
		m_nDef = 0;
		m_nMoney = 0;
		m_nNpcID = 0;
		m_nType = 0;
		m_nCount = 0;
	}

	/* 血量 */
	int m_nHP;

	/* 蓝量 */
	int m_nMP;

	/* 攻击力 */
	int m_nAtk;

	/* 防御力 */
	int m_nDef;

	/* 金钱 */
	int m_nMoney;

	/* 所属NPC ID */
	int m_nNpcID;

	/* 类型 */
	int m_nType;

	/* 数量 */
	int m_nCount;
};

// 装备、道具数据管理者
class CItemDtMgr :public CBaseDtMgr
{
public:
	CItemDtMgr() {}
	~CItemDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);
};

// 敌人数据
struct SEnemyDt :public SBaseDt
{
	SEnemyDt()
	{
		m_strPic = "";
		m_nHP = 0;
		m_nMP = 0;
		m_nAtk = 0;
		m_nDef = 0;
		m_nRow = 0;
		m_nCol = 0;
		m_nMapID = 0;
		m_nMoney = 0;
	}

	/* 渲染图片 */
	string m_strPic;

	/* 血量 */
	int m_nHP;

	/* 蓝量 */
	int m_nMP;

	/* 攻击力 */
	int m_nAtk;

	/* 防御力 */
	int m_nDef;

	/* 敌人所在行 */
	int m_nRow;

	/* 敌人所在列 */
	int m_nCol;

	/* 所属地图ID */
	int m_nMapID;

	/* 掉落金币 */
	int m_nMoney;
};

// 敌人数据管理者
class CEnemyDtMgr :public CBaseDtMgr
{
public:
	CEnemyDtMgr() {}
	~CEnemyDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);
};

// 技能数据
struct SSkillDt :public SBaseDt
{
	SSkillDt()
	{
		m_nHP = 0;
		m_nAtk = 0;
		m_nMP = 0;
		memset(m_arrRoles, 0, sizeof(m_arrRoles));
	}

	/* 加血量 */
	int m_nHP;

	/* 技能伤害 */
	int m_nAtk;

	/* 消耗的蓝量 */
	int m_nMP;

	/* 拥有该技能的角色数 */
	int m_nRoleCount;

	/* 拥有技能的角色 */
	int m_arrRoles[100];
};

// 技能数据管理者
class CSkillDtMgr :public CBaseDtMgr
{
public:
	CSkillDtMgr() {}
	~CSkillDtMgr() {}

	// 加载数据
	virtual void loadData(const string& strPath);

	// 根据角色ID获取对应的技能
	vector<SSkillDt*> getSkillByRoleID(int nRoleID);
};
