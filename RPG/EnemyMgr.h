#pragma once
#include "Enemy.h"

// 敌人管理者
class CEnemyMgr
{
public:
	CEnemyMgr();

	~CEnemyMgr();

	// 创建所有敌人
	void createEnemy();

	// 在地图某行某列是否存在
	CEnemy* isExist(int nRow, int nCol, int nMapID);

	/* 根据ID获取敌人 */
	CEnemy* getEnemyByID(int nID);

	/* 根据ID移除敌人 */
	void removeEnemyByID(int nID);

	/* 根据地图ID随机创建某种敌人 */
	void createRoundEnemy(int nEnemyID);

private:
	/* 保存所有的敌人 */
	vector<CEnemy*> m_vecEnemys;
};
