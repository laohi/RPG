#pragma once
#include "DataClass.h"
#include "Pet.h"

// 玩家
class CPlayer
{
public:
	CPlayer();

	CPlayer(int nRow, int nCol);

	~CPlayer();

	// 初始化玩家数据
	void initWithData(SRoleDt* pData);

	// 数据更新
	void update();

	// 是否在某行某列
	bool isExist(int nRow, int nCol);

	// 获取玩家背包
	vector<SItemDt*> getBag();

	// 添加装备到背包
	void addItemToBag(SItemDt* pItem);

	// 根据索引从背包移除装备
	void removeItemFromBag(int nIndex);

	// 根据ID从背包移除装备
	void removeItemFromBagByID(int nID);

	// 根据索引使用道具
	void useItem(int nIndex);

	// 使用道具
	void useItem(SItemDt* pItem);

	// 将装备添加到装备栏（穿装备）
	void addItemToEquip(SItemDt* pEquip);

	// 将装备从装备栏移除到背包（卸下装备）
	void removeItemFromEquip(int nIndex);

	// 根据索引获取装备
	SItemDt* getEquipByIndex(int nIndex);

	/* 玩家ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* 玩家名字 */
	CC_SYNTHESIZE_READONLY(string, m_strName, Name)

	/* 玩家血量 */
	CC_SYNTHESIZE(int, m_nHP, HP)

	/* 玩家蓝量 */
	CC_SYNTHESIZE(int, m_nMP, MP)

	/* 玩家攻击力 */
	CC_SYNTHESIZE_READONLY(int, m_nAtk, Atk)

	/* 玩家防御力 */
	CC_SYNTHESIZE_READONLY(int, m_nDef, Def)

	/* 玩家金钱 */
	CC_SYNTHESIZE(int, m_nMoney, Money)

	/* 渲染图片 */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* 玩家宠物 */
	CC_SYNTHESIZE_READONLY(CPet*, m_pPet, Pet)

private:
	// 设置宠物位置
	void setPetPos(int nRow, int nCol);

	// 还原宠物位置
	void setPetPosBak();

	/* 玩家所在行 */
	int m_nRow;

	/* 玩家所在列 */
	int m_nCol;

	/* 玩家所在行（备份） */
	int m_nRowBk;

	/* 玩家所在列（备份） */
	int m_nColBk;

	/* 玩家背包 */
	vector<SItemDt*> m_vecBag;

	/* 玩家装备栏 */
	SItemDt* m_arrEquip[4];
};
