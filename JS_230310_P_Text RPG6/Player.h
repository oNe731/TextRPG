#pragma once
// #include "Define.h"
#include "BaseInfo.h"

class CPlayer: public BaseInfo
{
public:
	explicit CPlayer() { }
	virtual ~CPlayer();
	friend class CHuntingGround;

public:
	void Initialize();
	void Release();

	void Select_PlayerInfo();
	void Load_PlayerInfo();
	void Save_PlayerInfo();
	void LvUp_PlayerInfo();

	void Skill_Update();
	void Skill_Output() const;

	void Inven_Update();
	void Inven_Output() const;
	void Inven_ArrSort(int _iInputNum, InvenInfo _tlocation[], InvenInfo _tDatamove[]) const;
	void Update_PlayerInfo(InvenInfo _tlocation[], int iNum, bool _btrue);

	void Store_Update();

	void Output_Info();
	int Get_Attack() const { return m_Player.iAttack; }
	int Get_HP() const { return m_Player.iCurrHp; }
	void Damage_HP(int _Damage) { m_Player.iCurrHp -= _Damage; }

	//void Homework_Store_Update();
	//void _Homework_Store(string _sName, int _iAttack, int _iDefense, int _iCoin);
};