#pragma once

// ����
class CPet
{
public:
	CPet();

	CPet(int nRow, int nCol);

	~CPet();

	// �Ƿ���ĳ��ĳ��
	bool isExist(int nRow, int nCol);

	/* ���ó���λ�� */
	void setPos(int nRow, int nCol);

	/* ��ԭ��һ�ε�λ�� */
	void setPosBak();

private:
	/* ���������� */
	int m_nRow;

	/* ���������� */
	int m_nCol;

	/* ���������У����ݣ� */
	int m_nRowBk;

	/* ���������У����ݣ� */
	int m_nColBk;
};
