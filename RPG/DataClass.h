#pragma once
#include "DataBase.h"

// ������Ϸ���ݣ������ࣩ
class CLoad
{
public:
	CLoad() {}

	~CLoad() {}

	// ������Ϸ����
	static void loadGameData();
};

// ��ɫ����
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

	/* Ѫ�� */
	int m_nHP;

	/* ���� */
	int m_nMP;

	/* ������ */
	int m_nAtk;

	/* ������ */
	int m_nDef;

	/* ��Ǯ */
	int m_nMoney;

	/* ��ȾͼƬ */
	string m_strPic;
};

// ��ɫ���ݹ�����
class CRoleDtMgr :public CBaseDtMgr
{
public:
	CRoleDtMgr() {}

	~CRoleDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);
};

// ��ͼ����
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

	/* ������ */
	int m_nRowCount;

	/* ������ */
	int m_nColCount;

	/* ��ҳ�ʼ���� */
	int m_nPlayerRow;

	/* ��ҳ�ʼ���� */
	int m_nPlayerCol;

	/* ��ͼ���� */
	int m_arrMap[100][100];
};

// ��ͼ���ݹ�����
class CMapDtMgr :public CBaseDtMgr
{
public:
	CMapDtMgr() {}
	~CMapDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);
};

// NPC����
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

	/* ��ȾͼƬ */
	string m_strPic;

	/* NPC������ */
	int m_nRow;

	/* NPC������ */
	int m_nCol;

	/* ������ͼID */
	int m_nMapID;

	/* NPC���� */
	int m_nType;
};

// NPC���ݹ�����
class CNpcDtMgr :public CBaseDtMgr
{
public:
	CNpcDtMgr() {}
	~CNpcDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);
};

// װ������������
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

	/* Ѫ�� */
	int m_nHP;

	/* ���� */
	int m_nMP;

	/* ������ */
	int m_nAtk;

	/* ������ */
	int m_nDef;

	/* ��Ǯ */
	int m_nMoney;

	/* ����NPC ID */
	int m_nNpcID;

	/* ���� */
	int m_nType;

	/* ���� */
	int m_nCount;
};

// װ�����������ݹ�����
class CItemDtMgr :public CBaseDtMgr
{
public:
	CItemDtMgr() {}
	~CItemDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);
};

// ��������
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

	/* ��ȾͼƬ */
	string m_strPic;

	/* Ѫ�� */
	int m_nHP;

	/* ���� */
	int m_nMP;

	/* ������ */
	int m_nAtk;

	/* ������ */
	int m_nDef;

	/* ���������� */
	int m_nRow;

	/* ���������� */
	int m_nCol;

	/* ������ͼID */
	int m_nMapID;

	/* ������ */
	int m_nMoney;
};

// �������ݹ�����
class CEnemyDtMgr :public CBaseDtMgr
{
public:
	CEnemyDtMgr() {}
	~CEnemyDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);
};

// ��������
struct SSkillDt :public SBaseDt
{
	SSkillDt()
	{
		m_nHP = 0;
		m_nAtk = 0;
		m_nMP = 0;
		memset(m_arrRoles, 0, sizeof(m_arrRoles));
	}

	/* ��Ѫ�� */
	int m_nHP;

	/* �����˺� */
	int m_nAtk;

	/* ���ĵ����� */
	int m_nMP;

	/* ӵ�иü��ܵĽ�ɫ�� */
	int m_nRoleCount;

	/* ӵ�м��ܵĽ�ɫ */
	int m_arrRoles[100];
};

// �������ݹ�����
class CSkillDtMgr :public CBaseDtMgr
{
public:
	CSkillDtMgr() {}
	~CSkillDtMgr() {}

	// ��������
	virtual void loadData(const string& strPath);

	// ���ݽ�ɫID��ȡ��Ӧ�ļ���
	vector<SSkillDt*> getSkillByRoleID(int nRoleID);
};
