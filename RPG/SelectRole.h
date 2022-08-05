#pragma once
#include "DataBase.h"

// 选择角色
class CSelectRole
{
public:
	CSelectRole();

	~CSelectRole();

	// 数据初始化
	void init();

	// 数据更新
	void update();

	// 数据渲染
	void render();

private:
	/* 保存所有的角色 */
	vector<SBaseDt*> m_vecRoles;

	/* 选择索引 */
	int m_nSelectIndex;
};
