#pragma once
#include "DataBase.h"

// ѡ���ɫ
class CSelectRole
{
public:
	CSelectRole();

	~CSelectRole();

	// ���ݳ�ʼ��
	void init();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

private:
	/* �������еĽ�ɫ */
	vector<SBaseDt*> m_vecRoles;

	/* ѡ������ */
	int m_nSelectIndex;
};
