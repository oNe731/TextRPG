#pragma once
#include "Player.h"
#include "Item.h"

class CInventory
{
public:
	CInventory();
	~CInventory();

public:
	void Initialize();
	void Update();
	void Release();

	void Inven_Output();
	void PlayerInfo_Set(BaseInfo* pPlayer) { this->m_Copy_Player = pPlayer; }
	vector<CItem*>& ItemVec_HaveGet() { return m_Item_Have; }

private:
	BaseInfo* m_Copy_Player;
	vector<CItem*>::iterator iter;
	vector<CItem*>::iterator iter2;
	vector<CItem*> m_Item_Have;
	vector<CItem*> m_Item_Equip;
};