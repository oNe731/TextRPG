#pragma once
#include "Define.h"

class CItem
{
public:
	CItem();
	CItem(char* _sName, char* _sItemEffect, int _iEffectNum, int _iCoin, int _iNum, int _iCount) : m_ItemInfo(_sName, _sItemEffect, _iEffectNum, _iCoin, _iNum, _iCount) {}
	~CItem();

public:
	void Item_Output();
	int ItemCoin_Get() { return m_ItemInfo.iCoin; }
	InvenInfo ItemInfo_Get() { return m_ItemInfo; }

private:
	InvenInfo m_ItemInfo;
};

