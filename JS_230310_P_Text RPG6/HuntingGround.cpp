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
		cout << "����� �Ա�]" << endl;
		cout << "-----------------------------------------------------------" << endl;
		cout << "1) �ʱ� �����. 2) �߱� �����. 3) ��� �����. 4) ����ȭ��: ";
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
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
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

		cout << "1) ����. 2) ���� : ";
		cin >> iInput;

		iRanNum = rand() % 2 + 1;
		if (iInput == 1) // ����
		{
			iCount++;
			if (iCount % 5 == 0 && m_Copy_Player->Get_PlayerSkillCount() >= 1)
			{
				// ���� ��ų ��� ��� �� ���
				dynamic_cast<CPlayer*>(m_Copy_Player)->Skill_Output();
				cout << "1) ����� ��ų ����: ";
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
						cout << "ȸ���� ���� ����!" << endl;
					}
					break;
				case 2:
					if (m_Copy_Player->Get_PlayerSkillCount() >= 2)
					{
						// m_Monster->Damage_MonsterHP((m_Copy_Player->m_Player.iAttack + m_Copy_Player->m_PlayerSkill[1].iDamage)); // friend�� privat ���� ����.
						m_Monster->Damage_HP((m_Copy_Player->Get_Attack() + m_Copy_Player->Get_PlayerSkillEffectNum(2)));
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "����� ���� ����!" << endl;
					}
					break;
				case 3:
					if (m_Copy_Player->Get_PlayerSkillCount() == 3)
					{
						m_Copy_Player->Set_AddPlayerHP(m_Copy_Player->Get_PlayerSkillEffectNum(3));
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "�÷��̾� ����� ȸ�� ����!" << endl;
					}
					break;
				default:
					cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
					break;
				}
				system("pause");
			}
			else
			{
				system("cls");
				if (iRanNum == 1) // �÷��̾ ���� ����
				{
					m_Monster->Damage_HP(m_Copy_Player->Get_Attack());
					m_Copy_Player->Output_Info();
					m_Monster->Output_Info();
					cout << "�÷��̾� -> ���� ���� ����!" << endl;
					cout << "���� -> �÷��̾� ���� ����!" << endl;
				}
				else // ���Ͱ� �÷��̾� ����
				{
					iRanTrue = rand() % 10 + 1;
					if (iRanTrue < 3) // ���� ���� ��� ����
					{
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "������ ���� ��� ����!" << endl;
					}
					else // ��� ����
					{
						m_Copy_Player->Damage_HP(m_Monster->Get_Attack());
						m_Copy_Player->Output_Info();
						m_Monster->Output_Info();
						cout << "�÷��̾� -> ���� ���� ����!" << endl;
						cout << "���� -> �÷��̾� ���� ����!" << endl;
					}
				}
				system("pause");
			}

			if (m_Monster->Get_HP() <= 0) 
			{
				cout << "���� ���" << endl;
				m_Copy_Player->Set_PlayerEX(m_Monster->Get_MonsterEx());
				m_Copy_Player->Set_PlayerCoin(m_Monster->Get_MonsterCoin());
				dynamic_cast<CPlayer*>(m_Copy_Player)->LvUp_PlayerInfo();
				system("pause");
				system("cls");
				return;
			}
			if (m_Copy_Player->Get_HP() <= 0)
			{
				cout << "�÷��̾� ���" << endl;
				m_Copy_Player->Set_PlayerHP();
				system("pause");
				system("cls");
				return;
			}
		}
		else if (iInput == 2) // ����
		{
			if (iRanNum == 1)
			{
				cout << "���� ����!" << endl;
				system("pause");
				system("cls");
				return;
			}
			else
			{
				cout << "���� ����!" << endl;
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