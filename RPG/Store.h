#pragma once

// �̵�
class CStore
{
public:
	CStore();

	~CStore();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

	// ����NPC ID��ʼ���̵���Ʒ
	void initItemWithNpcID(int nNpcID);

private:
	vector<SItemDt*> m_vecItems;

	/* ѡ������ */
	int m_nSelectIndex;
};
