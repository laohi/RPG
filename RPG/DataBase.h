#pragma once

// ���ݻ���
struct SBaseDt
{
	SBaseDt()
	{
		m_nID = 0;
		m_strName = "";
	}

	virtual ~SBaseDt() {}

	/* ����ID */
	int m_nID;

	/* �������� */
	string m_strName;
};

// ���ݹ����߻���
class CBaseDtMgr
{
public:
	CBaseDtMgr() {}

	virtual ~CBaseDtMgr();

	// ��������
	virtual void loadData(const string& strPath) = 0;

	// ����ID��ȡ����
	SBaseDt* getDataByID(int nID);

	// ��ȡȫ������
	vector<SBaseDt*> getAllDatas();

	// ��ȡ���ݵ�������
	int getDataSize();

protected:
	/* �������е����� */
	vector<SBaseDt*> m_vecDatas;
};
