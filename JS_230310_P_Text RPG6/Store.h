#pragma once
#include "Define.h"
#include "Item.h"
#include "Player.h"
#include "Inventory.h"

class CStore
{
public:
	CStore();
	~CStore();
	void PlayerInfo_Set(BaseInfo* pPlayer) { this->m_Copy_Player = pPlayer; }
	void PlayerInven_Set(CInventory* pInven) { this->m_Copy_PlayerInven = pInven; }

public:
	void Initialize();
	void Update() ;
	void Release();
	void MiniStore(ITEM_GRADE _int);

private:
	CItem* m_Item[TYPE_End][GRADE_End];
	BaseInfo* m_Copy_Player;
	CInventory* m_Copy_PlayerInven;
};