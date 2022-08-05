#pragma once

// 玩家背包
class CBag
{
public:
	CBag();

	~CBag();

	// 数据更新
	void update();

	// 数据渲染
	void render();

	/* 是否编辑装备 */
	CC_SYNTHESIZE(bool, m_bIsEditEquip, IsEditEquip)

private:
	/* 选择索引 */
	int m_nSelectIndex;
};
