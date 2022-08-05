#pragma once

// NPC
class CNpc
{
public:
	CNpc();
	
	CNpc(SNpcDt* pData);

	~CNpc();

	// 在地图某行某列是否存在
	bool isExist(int nRow, int nCol, int nMapID);

	/* NPC ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* 渲染图片 */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* NPC类型 */
	CC_SYNTHESIZE_READONLY(int, m_nType, Type)
	
private:
	/* NPC名称 */
	string m_strName;

	/* NPC所在行 */
	int m_nRow;

	/* NPC所在列 */
	int m_nCol;

	/* 所属地图ID */
	int m_nMapID;
};
