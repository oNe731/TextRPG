#pragma once
#include "Player.h"
#include "Store.h"
#include "Inventory.h"
class CHuntingGround;

// CPlayer* p_Player;

class CMainGame
{
public:
	explicit CMainGame() : m_Player(nullptr), m_Ground(nullptr) {}
	~CMainGame();
	// friend class CHuntingGround;
	// friend CPlayer* CHuntingGround::Get_PlayerClass();

public:
	void Initialize();
	void Update() const;
	void Release();

private:
	BaseInfo* m_Player;
	CHuntingGround* m_Ground;
	CStore* m_Store;
	CInventory* m_PlayerInven;
};