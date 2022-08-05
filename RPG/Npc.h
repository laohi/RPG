#pragma once

// NPC
class CNpc
{
public:
	CNpc();
	
	CNpc(SNpcDt* pData);

	~CNpc();

	// �ڵ�ͼĳ��ĳ���Ƿ����
	bool isExist(int nRow, int nCol, int nMapID);

	/* NPC ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* ��ȾͼƬ */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* NPC���� */
	CC_SYNTHESIZE_READONLY(int, m_nType, Type)
	
private:
	/* NPC���� */
	string m_strName;

	/* NPC������ */
	int m_nRow;

	/* NPC������ */
	int m_nCol;

	/* ������ͼID */
	int m_nMapID;
};
