#pragma once

// 战斗对话
class CBattleDialog
{
public:
	CBattleDialog();

	~CBattleDialog();

	// 数据初始化，nType：操作类型
	void init(CEnemy* pEnemy, int nType);

	// 数据初始化，pItem:道具，nType：操作类型
	void init(CEnemy* pEnemy, SItemDt* pItem, int nType);

	// 数据初始化，pSkill:技能，nType：操作类型
	void init(CEnemy* pEnemy, SSkillDt* pSkill, int nType);

	// 数据更新
	void update();

	// 数据渲染
	void render();

private:
	/* 操作处理 */
	void operateHandle();

	/* 扣血处理 */
	int atkHandler(int nAtk, int nDef);

	/* 玩家 */
	CPlayer* m_pPlayer;

	/* 敌人 */
	CEnemy* m_pEnemy;

	/* 对话类型 */
	int m_nType;

	/* 敌人的攻击 */
	int m_nEnemyAtk;

	/* 玩家的攻击 */
	int m_nPlayerAtk;

	/* 道具 */
	SItemDt* m_pItem;

	/* 技能 */
	SSkillDt* m_pSkill;

	/* 是否能够使用技能 */
	bool m_bIsEnableSkill;

	/* 是否逃跑成功 */
	bool m_bIsExitSuccess;
};
