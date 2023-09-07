#pragma once
#include "Player.h"
//#include "Monster.h"
class CMonster;

class CHuntingGround
{
public:
	explicit CHuntingGround() : m_Copy_Player(nullptr), m_Monster(nullptr) {}
	~CHuntingGround();

public:
	void Update();
	void Battle() const;
	void Release();

	void PlayerInfo_Set(BaseInfo* pPlayer) { this->m_Copy_Player = pPlayer; }
	// void PlayerInfo_Set(CMainGame pPlayer) { this->m_Player = pPlayer.m_Player; }

private:
	BaseInfo* m_Copy_Player;
	BaseInfo* m_Monster;
};