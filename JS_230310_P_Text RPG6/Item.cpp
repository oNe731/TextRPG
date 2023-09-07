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
	cout << "아이템 이름 : " << m_ItemInfo.sName << endl;
	cout << "아이템 효과 : " << m_ItemInfo.sItemEffect << " " << m_ItemInfo.iEffectNum << " 증가!" << endl;
	cout << "아이템 금액 : " << m_ItemInfo.iCoin << " 원" << endl;
	cout << "---------------------------------------------" << endl;
}
