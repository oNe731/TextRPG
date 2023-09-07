#include "pch.h"
#include "HuntingGround.h"
#include "Monster.h"

/*CHuntingGround::CHuntingGround()
{
	m_Player = nullptr;
	m_Monster = nullptr;
}*/

CHuntingGround::~CHuntingGround()
{
	Release();
}

void CHuntingGround::Update()
{
	int iInput(0);
	bool bSelet = false;

	while (!bSelet)
	{
		m_Copy_Player->Output_Info();
		cout << "===========================================================" << endl;
		cout << "사냥터 입구]" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << "1) 초급 사냥터. 2) 중급 사냥터. 3) 고급 사냥터. 4) 메인화면: ";
		cin >> iInput;

		system("cls");
		switch (iInput)
		{
		case 1:
			this->m_Monster = new CMonster(1);
			Battle();
			Release();
			break;
		case 2:
			this->m_Monster = new CMonster(2);
			Battle();
			Release();
			break;
		case 3:
			this->m_Monster = new CMonster(3);
			Battle();
			Release();
			break;
		case 4:
			bSelet = true;
			break;
		default:
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void CHuntingGround::Battle() const
{
	int iInput(0), iCount(0), iRanNum(0), iRanTrue(0), i_Input(0);
	
	while (true)
	{
		system("cls");
		m_Copy_Player->Output_Info();
		m_Monster->Output_Info();

		cout << "1) 공격. 2) 도망 : ";
		cin >> iInput;

		iRanNum = rand() % 2 + 1;
		if (iInput == 1) // 공격
		{
			iCount++;
			if (iCount % 5 == 0 && m_Copy_Player->Get_PlayerSkillCount() >= 1)
			{
				// 보유 스킬 목록 출력 및 사용
				dynamic_cast<CPlayer*>(m_Copy_Player)->Skill_Output();
				cout << "1) 사용할 스킬 선택: ";
				cin >> i_Input;
				system("cls");

				switch (i_Input)
				{
				case 1:
					if (m_Copy_Player->Get_PlayerSkillCount() >= 1)
					{
						m_Monster->Damage_HP((m_Copy_Player->Get_Attack() + m_Copy_Player->Get_PlayerSkillEffectNum(1)));
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "회심의 공격 성공!" << endl;
					}
					break;
				case 2:
					if (m_Copy_Player->Get_PlayerSkillCount() >= 2)
					{
						// m_Monster->Damage_MonsterHP((m_Copy_Player->m_Player.iAttack + m_Copy_Player->m_PlayerSkill[1].iDamage)); // friend로 privat 변수 접근.
						m_Monster->Damage_HP((m_Copy_Player->Get_Attack() + m_Copy_Player->Get_PlayerSkillEffectNum(2)));
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "스페셜 어택 성공!" << endl;
					}
					break;
				case 3:
					if (m_Copy_Player->Get_PlayerSkillCount() == 3)
					{
						m_Copy_Player->Set_AddPlayerHP(m_Copy_Player->Get_PlayerSkillEffectNum(3));
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "플레이어 생명력 회복 성공!" << endl;
					}
					break;
				default:
					cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
					break;
				}
				system("pause");
			}
			else
			{
				system("cls");
				if (iRanNum == 1) // 플레이어가 몬스터 공격
				{
					m_Monster->Damage_HP(m_Copy_Player->Get_Attack());
					m_Copy_Player->Output_Info();
					m_Monster->Output_Info();
					cout << "플레이어 -> 몬스터 공격 성공!" << endl;
					cout << "몬스터 -> 플레이어 공격 실패!" << endl;
				}
				else // 몬스터가 플레이어 공격
				{
					iRanTrue = rand() % 10 + 1;
					if (iRanTrue < 3) // 몬스터 공격 방어 성공
					{
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "몬스터의 공격 방어 성공!" << endl;
					}
					else // 방어 실패
					{
						m_Copy_Player->Damage_HP(m_Monster->Get_Attack());
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "플레이어 -> 몬스터 공격 실패!" << endl;
						cout << "몬스터 -> 플레이어 공격 성공!" << endl;
					}
				}
				system("pause");
			}

			if (m_Monster->Get_HP() <= 0) 
			{
				cout << "몬스터 사망" << endl;
				m_Copy_Player->Set_PlayerEX(m_Monster->Get_MonsterEx());
				m_Copy_Player->Set_PlayerCoin(m_Monster->Get_MonsterCoin());
				dynamic_cast<CPlayer*>(m_Copy_Player)->LvUp_PlayerInfo();
				system("pause");
				system("cls");
				return;
			}
			if (m_Copy_Player->Get_HP() <= 0)
			{
				cout << "플레이어 사망" << endl;
				m_Copy_Player->Set_PlayerHP();
				system("pause");
				system("cls");
				return;
			}
		}
		else if (iInput == 2) // 도망
		{
			if (iRanNum == 1)
			{
				cout << "도망 성공!" << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{
				cout << "도망 실패!" << endl;
				system("pause");
			}
		}
		system("cls"); 
	}
}

void CHuntingGround::Release()
{
	DELETE_MEMORY(this->m_Monster);
}