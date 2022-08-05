#pragma once

// 商店
class CStore
{
public:
	CStore();

	~CStore();

	// 数据更新
	void update();

	// 数据渲染
	void render();

	// 根据NPC ID初始化商店物品
	void initItemWithNpcID(int nNpcID);

private:
	vector<SItemDt*> m_vecItems;

	/* 选择索引 */
	int m_nSelectIndex;
};
