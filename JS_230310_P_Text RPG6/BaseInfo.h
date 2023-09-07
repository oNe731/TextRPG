#pragma once
#include "pch.h"
#include "Define.h"

class BaseInfo
{
public:
	BaseInfo() : m_PlayerSkill(nullptr), m_PlayerInven_Equip(nullptr), m_PlayerInven_Have(nullptr)
	{
		memset(&m_Player, 0, sizeof(PlayerInfo));
		memset(&m_Monster, 0, sizeof(MonsterInfo));
	}
	virtual ~BaseInfo();
public:
	void Set_PlayerHP() { m_Player.iCurrHp = m_Player.iMaxHp; }
	void Set_AddPlayerHP(int _AddHp)
	{
		m_Player.iCurrHp += _AddHp;
		if (m_Player.iCurrHp > m_Player.iMaxHp)
			m_Player.iCurrHp = m_Player.iMaxHp;
	}
	int Get_PlayerSkillCount() const { return m_PlayerSkill[0].iUseCoint; }
	int Get_PlayerSkillEffectNum(int _SkillNum) const
	{
		switch (_SkillNum)
		{
		case 1:
			return m_PlayerSkill[0].iDamage;
			break;
		case 2:
			return m_PlayerSkill[1].iDamage;
			break;
		case 3:
			return m_PlayerSkill[2].iRecovery;
			break;
		}
	}

	int Get_MonsterEx() const { return m_Monster.iEx; }
	void Set_PlayerEX(int _Ex) { m_Player.iEx += _Ex; }
	int Get_MonsterCoin() const { return m_Monster.iCoin; }
	int Get_PlayerCoin() const { return m_Player.iCoin; }
	void Set_PlayerCoin(int _Coin) { m_Player.iCoin += _Coin; }
	void Set_PlayerCoin_(int _Coin) { m_Player.iCoin -= _Coin; }

public:
	virtual void Output_Info() = 0;
	virtual int Get_Attack() const = 0;
	virtual int Get_HP() const = 0;
	virtual void Damage_HP(int _Damage) = 0;

protected:
	PlayerInfo m_Player;
	MonsterInfo m_Monster;

	SkillInfo* m_PlayerSkill;
	InvenInfo* m_PlayerInven_Equip;
	InvenInfo* m_PlayerInven_Have;
};