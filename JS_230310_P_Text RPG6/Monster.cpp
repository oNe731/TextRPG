#include "pch.h"
#include "Monster.h"
// #include "Define.h"

/*CMonster::CMonster()
{
	m_Monster = nullptr;
}*/

CMonster::CMonster(int _iMonLv) 
{
	int iMonsLv = rand() % 10 + 1;

	switch (_iMonLv)
	{
	case 1:
		strcpy_s(m_Monster.sName, sizeof(m_Monster.sName), "슬라임");
		strcpy_s(m_Monster.sProperty, sizeof(m_Monster.sProperty), "물속성");
		m_Monster.iLv = iMonsLv;
		m_Monster.iHp = 2 * iMonsLv;
		m_Monster.iAttack = 2 * iMonsLv;
		m_Monster.iEx = 10 * iMonsLv;
		m_Monster.iCoin = 10 * iMonsLv;
		break;
	case 2:
		strcpy_s(m_Monster.sName, sizeof(m_Monster.sName), "고블린");
		strcpy_s(m_Monster.sProperty, sizeof(m_Monster.sProperty), "풀속성");
		m_Monster.iLv = iMonsLv + 10;
		m_Monster.iHp = 10 * iMonsLv;
		m_Monster.iAttack = 10 * iMonsLv;
		m_Monster.iEx = 30 * iMonsLv;
		m_Monster.iCoin = 20 * iMonsLv;
		break;
	case 3:
		strcpy_s(m_Monster.sName, sizeof(m_Monster.sName), "드래곤");
		strcpy_s(m_Monster.sProperty, sizeof(m_Monster.sProperty), "불속성");
		m_Monster.iLv = iMonsLv + 20;
		m_Monster.iHp = 200 * iMonsLv;
		m_Monster.iAttack = 15 * iMonsLv;
		m_Monster.iEx = 100 * iMonsLv;
		m_Monster.iCoin = 50 * iMonsLv;
		break;
	default:
		break;
	}
}

CMonster::~CMonster()
{
}

void CMonster::Output_Info()
{
	if (m_Monster.iHp <= 0)
		m_Monster.iHp = 0;
	cout << "=============================================" << endl;
	cout << "[생성된 몬스터]" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "이름 : " << m_Monster.sName << "\t" << "속성 : " << m_Monster.sProperty << "\t" << "레벨 : " << m_Monster.iLv << endl;
	cout << "체력 : " << m_Monster.iHp << "\t" << "공격력 : " << m_Monster.iAttack << endl;
	cout << "=============================================" << endl;
}