#pragma once

// ��ұ���
class CBag
{
public:
	CBag();

	~CBag();

	// ���ݸ���
	void update();

	// ������Ⱦ
	void render();

	/* �Ƿ�༭װ�� */
	CC_SYNTHESIZE(bool, m_bIsEditEquip, IsEditEquip)

private:
	/* ѡ������ */
	int m_nSelectIndex;
};
