#include "stdafx.h"
#include "Pet.h"

CPet::CPet()
{
}

CPet::CPet(int nRow, int nCol)
{
	m_nRow = nRow;
	m_nCol = nCol;
	m_nRowBk = m_nRow;
	m_nColBk = m_nCol;
}

CPet::~CPet()
{
}

bool CPet::isExist(int nRow, int nCol)
{
	if (nRow == m_nRow && nCol == m_nCol)
	{
		return true;
	}
	return false;
}

void CPet::setPos(int nRow, int nCol)
{
	m_nRowBk = m_nRow;
	m_nColBk = m_nCol;
	m_nRow = nRow;
	m_nCol = nCol;
}

void CPet::setPosBak()
{
	m_nRow = m_nRowBk;
	m_nCol = m_nColBk;
}
