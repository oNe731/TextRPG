#pragma once
// #include "Define.h"
#include "BaseInfo.h"

class CMonster : public BaseInfo
{
public:
	explicit CMonster() {}
	explicit CMonster(int _iMonLv);
	virtual ~CMonster();

	void Output_Info();
	int Get_Attack() const { return m_Monster.iAttack; }
	int Get_HP() const { return m_Monster.iHp; }
	void Damage_HP(int _Damage) { m_Monster.iHp -= _Damage; }
};