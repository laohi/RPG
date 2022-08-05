#pragma once

enum
{
	E_BATTLE_ATK,
	E_BATTLE_SKILL,
	E_BATTLE_ITEM,
	E_BATTLE_EXIT
};

// 战斗场景
class CBattle
{
public:
	CBattle();

	~CBattle();

	// 数据初始化
	void initEnemy(CEnemy* pEnemy);

	// 数据更新
	void update();

	// 数据渲染
	void render();

	/* 敌人 */
	CC_SYNTHESIZE_READONLY(CEnemy*, m_pEnemy, Enemy);

private:
	/* 一级操作索引 */
	int m_nOperateIndex;

	/* 打开二级菜单 */
	bool m_bOpenSecondMenu;

	/* 二级索引 */
	int m_nSecondIndex;
};
