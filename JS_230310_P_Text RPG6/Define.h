#pragma once

#define DELETE_MEMORY(p) if(p){ delete p; p = nullptr;}
#define DELETE_MEMORY_Arr(p) if(p){ delete[] p; p = nullptr;}

enum ITEM_TYPE { TYPE_Sword, TYPE_Shield, TYPE_End };
enum ITEM_GRADE { GRADE_Beginner, GRADE_Intermediate, GRADE_Advanced, GRADE_End };

struct PlayerInfo
{
	char sName[34];
	char sGender[34];
	char sSpecies[34];
	char sJob[34];
	int iLv;

	int iMaxHp;
	int iCurrHp;
	int iAttack;
	int iDefense;

	int iEx;
	int iCoin;
};
struct MonsterInfo
{
	char sName[34];
	char sProperty[34];
	int iLv;

	int iHp;
	int iAttack;

	int iEx;
	int iCoin;
};
struct SkillInfo
{
	char sName[34];
	int iSkillLv;

	int iDamage;
	int iDefense;
	int iRecovery;

	int iUseCoint;
};
struct InvenInfo
{
	InvenInfo() {}
	InvenInfo(char* _sName, char* _sItemEffect, int _iEffectNum, int _iCoin, int _iNum, int _iCount)
		: iEffectNum(_iEffectNum), iCoin(_iCoin), iNum(_iNum), iCount(_iCount)
	{
		strcpy_s(sName, sizeof(sName), _sName);
		strcpy_s(sItemEffect, sizeof(sItemEffect), _sItemEffect);

	}
	char sName[34];
	char sItemEffect[34];

	int iEffectNum;
	int iCoin;

	int iNum;
	int iCount;
};