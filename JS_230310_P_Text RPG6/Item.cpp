#include "pch.h"
#include "Item.h"

CItem::CItem()
{
}

CItem::~CItem()
{
}

void CItem::Item_Output()
{
	cout << "---------------------------------------------" << endl;
	cout << "������ �̸� : " << m_ItemInfo.sName << endl;
	cout << "������ ȿ�� : " << m_ItemInfo.sItemEffect << " " << m_ItemInfo.iEffectNum << " ����!" << endl;
	cout << "������ �ݾ� : " << m_ItemInfo.iCoin << " ��" << endl;
	cout << "---------------------------------------------" << endl;
}
