#pragma once

// 敌人
class CEnemy
{
public:
	CEnemy();

	CEnemy(SEnemyDt* pData);

	~CEnemy();

	// 在地图某行某列是否存在
	bool isExist(int nRow, int nCol, int nMapID);

	// 设置敌人的位置
	void setPosition(int nRow, int nCol);

	/* 敌人ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* 敌人名称 */
	CC_SYNTHESIZE_READONLY(string, m_strName, Name)

	/* 渲染图片 */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* 敌人血量 */
	CC_SYNTHESIZE(int, m_nHP, HP)

	/* 敌人蓝量 */
	CC_SYNTHESIZE_READONLY(int, m_nMP, MP)

	/* 敌人攻击力 */
	CC_SYNTHESIZE_READONLY(int, m_nAtk, Atk)

	/* 敌人防御力 */
	CC_SYNTHESIZE_READONLY(int, m_nDef, Def)

	/* 敌人掉落金钱 */
	CC_SYNTHESIZE_READONLY(int, m_nMoney, Money)

private:
	/* 敌人所在行 */
	int m_nRow;

	/* 敌人所在列 */
	int m_nCol;

	/* 所属地图ID */
	int m_nMapID;
};
