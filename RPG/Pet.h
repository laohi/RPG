#pragma once

// 宠物
class CPet
{
public:
	CPet();

	CPet(int nRow, int nCol);

	~CPet();

	// 是否在某行某列
	bool isExist(int nRow, int nCol);

	/* 设置宠物位置 */
	void setPos(int nRow, int nCol);

	/* 还原上一次的位置 */
	void setPosBak();

private:
	/* 宠物所在行 */
	int m_nRow;

	/* 宠物所在列 */
	int m_nCol;

	/* 宠物所在行（备份） */
	int m_nRowBk;

	/* 宠物所在列（备份） */
	int m_nColBk;
};
