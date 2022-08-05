#pragma once
#include "DataBase.h"

// ���ݹ����߹�����
class CDataMgr
{
public:
	~CDataMgr();

	// ��ȡ���ݹ����߹�����
	static CDataMgr* getInstance();

	// ������ݹ�����
	void addDtMgr(string strName, CBaseDtMgr* pDtMgr);

	// �������ֻ�ȡ���ݹ�����
	CBaseDtMgr* getDtMgr(string strName);

private:
	CDataMgr() {}

	/* ���ݹ����߹����ࣨ������ */
	static CDataMgr* m_psInstance;

	/* �������е����ݹ����� */
	map<string, CBaseDtMgr*> m_mapDtMgrs;
};
