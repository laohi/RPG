#pragma once
#include "DataClass.h"
#include "Pet.h"

// ���
class CPlayer
{
public:
	CPlayer();

	CPlayer(int nRow, int nCol);

	~CPlayer();

	// ��ʼ���������
	void initWithData(SRoleDt* pData);

	// ���ݸ���
	void update();

	// �Ƿ���ĳ��ĳ��
	bool isExist(int nRow, int nCol);

	// ��ȡ��ұ���
	vector<SItemDt*> getBag();

	// ���װ��������
	void addItemToBag(SItemDt* pItem);

	// ���������ӱ����Ƴ�װ��
	void removeItemFromBag(int nIndex);

	// ����ID�ӱ����Ƴ�װ��
	void removeItemFromBagByID(int nID);

	// ��������ʹ�õ���
	void useItem(int nIndex);

	// ʹ�õ���
	void useItem(SItemDt* pItem);

	// ��װ����ӵ�װ��������װ����
	void addItemToEquip(SItemDt* pEquip);

	// ��װ����װ�����Ƴ���������ж��װ����
	void removeItemFromEquip(int nIndex);

	// ����������ȡװ��
	SItemDt* getEquipByIndex(int nIndex);

	/* ���ID */
	CC_SYNTHESIZE_READONLY(int, m_nID, ID)

	/* ������� */
	CC_SYNTHESIZE_READONLY(string, m_strName, Name)

	/* ���Ѫ�� */
	CC_SYNTHESIZE(int, m_nHP, HP)

	/* ������� */
	CC_SYNTHESIZE(int, m_nMP, MP)

	/* ��ҹ����� */
	CC_SYNTHESIZE_READONLY(int, m_nAtk, Atk)

	/* ��ҷ����� */
	CC_SYNTHESIZE_READONLY(int, m_nDef, Def)

	/* ��ҽ�Ǯ */
	CC_SYNTHESIZE(int, m_nMoney, Money)

	/* ��ȾͼƬ */
	CC_SYNTHESIZE_READONLY(string, m_strPic, Pic)

	/* ��ҳ��� */
	CC_SYNTHESIZE_READONLY(CPet*, m_pPet, Pet)

private:
	// ���ó���λ��
	void setPetPos(int nRow, int nCol);

	// ��ԭ����λ��
	void setPetPosBak();

	/* ��������� */
	int m_nRow;

	/* ��������� */
	int m_nCol;

	/* ��������У����ݣ� */
	int m_nRowBk;

	/* ��������У����ݣ� */
	int m_nColBk;

	/* ��ұ��� */
	vector<SItemDt*> m_vecBag;

	/* ���װ���� */
	SItemDt* m_arrEquip[4];
};
