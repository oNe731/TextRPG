#include "pch.h"
#include "Player.h"
// #include "Define.h"

/*CPlayer::CPlayer()
{
	m_Player = nullptr;
	m_PlayerSkill = nullptr;
	m_PlayerInven_Equip = nullptr;
	m_PlayerInven_Have = nullptr;
}*/

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	this->m_PlayerSkill = new SkillInfo[3];
	m_PlayerSkill[0].iUseCoint = 0;

	this->m_PlayerInven_Equip = new InvenInfo[3];
	m_PlayerInven_Equip[0].iCount = 0;
	this->m_PlayerInven_Have = new InvenInfo[3];
	m_PlayerInven_Have[0].iCount = 0;
}

void CPlayer::Release()
{
	DELETE_MEMORY_Arr(this->m_PlayerSkill);
	DELETE_MEMORY_Arr(this->m_PlayerInven_Equip);
	DELETE_MEMORY_Arr(this->m_PlayerInven_Have);
}

void CPlayer::Select_PlayerInfo()
{
	int iInput(0);
	bool bSelet(false);

	while (!bSelet)
	{
		system("cls");
		cout << "���Ͻô� ������ �������ּ���." << endl;
		cout << "1) �ΰ�. 2) ����. 3) ���� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "�ΰ�");
			m_Player.iMaxHp = 100;
			m_Player.iCurrHp = 100;
			bSelet = true;
			break;
		case 2:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "����");
			m_Player.iMaxHp = 130;
			m_Player.iCurrHp = 130;
			bSelet = true;
			break;
		case 3:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "����");
			m_Player.iMaxHp = 150;
			m_Player.iCurrHp = 150;
			bSelet = true;
			break;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
	}
	iInput = 0;
	bSelet = false;
	
	while (!bSelet)
	{
		system("cls");
		cout << "���Ͻô� ������ �������ּ���." << endl;
		cout << "1) ����. 2) ���� : ";
		cin >> iInput;

		if (iInput == 1)
		{
			strcpy_s(m_Player.sGender, sizeof(m_Player.sGender), "����");
			m_Player.iDefense = 10;
			bSelet = true;
		}
		else if (iInput == 2)
		{
			strcpy_s(m_Player.sGender, sizeof(m_Player.sGender), "����");
			m_Player.iDefense = 20;
			bSelet = true;
		}
		else
		{
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
		}
	}
	iInput = 0;
	bSelet = false;

	while (!bSelet)
	{
		system("cls");
		cout << "���Ͻô� ������ �������ּ���." << endl;
		cout << "1) ����. 2) ������. 3) ���� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "����");
			m_Player.iAttack = 10;
			bSelet = true;
			break;
		case 2:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "������");
			m_Player.iAttack = 20;
			bSelet = true;
			break;
		case 3:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "����");
			m_Player.iAttack = 30;
			bSelet = true;
			break;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
	}
	
	system("cls");
	cout << "����� �÷��̾� �̸��� �Է��ϼ��� : ";
	cin >> m_Player.sName;

	m_Player.iLv = 1;
	m_Player.iEx = 0;
	m_Player.iCoin = 1000;

	system("cls");
	Output_Info();
	system("pause");
}

void CPlayer::Load_PlayerInfo()
{
	FILE* fStream = nullptr;
	PlayerInfo* pInfo = &m_Player;

	int itrue = fopen_s(&fStream, "../SaveData/PlayerSaveInfo.txt", "rb");

	if (itrue == 0)
	{
		cout << "����� ������ �ҷ��ɴϴ�." << endl;
		fread(pInfo, sizeof(PlayerInfo), 1, fStream);
		fread(m_PlayerSkill, sizeof(SkillInfo), 3, fStream);
		fread(m_PlayerInven_Equip, sizeof(InvenInfo), 3, fStream);
		fread(m_PlayerInven_Have, sizeof(InvenInfo), 3, fStream);

		system("pause");
		system("cls");
		fclose(fStream);
	}
	else
	{
		cout << "����� ������ �����ϴ�." << endl;
		system("pause");
		system("cls");
	}
	
	Output_Info();
	system("pause");
}

void CPlayer::Save_PlayerInfo()
{
	FILE* fStream = nullptr;
	PlayerInfo* pInfo = &m_Player;

	int itrue = fopen_s(&fStream, "../SaveData/PlayerSaveInfo.txt", "wb");

	if (0 == itrue)
	{
		cout << "�÷��̾� ������ �����մϴ�." << endl;
		fwrite(pInfo, sizeof(PlayerInfo), 1, fStream);
		fwrite(m_PlayerSkill, sizeof(SkillInfo), 3, fStream);
		fwrite(m_PlayerInven_Equip, sizeof(InvenInfo), 3, fStream);
		fwrite(m_PlayerInven_Have, sizeof(InvenInfo), 3, fStream);

		system("pause");
		system("cls");
		fclose(fStream);
	}
	else
	{
		cout << "�÷��̾� ���� ���� ����" << endl;
		system("pause");
	}
}

void CPlayer::LvUp_PlayerInfo()
{
	switch (m_Player.iLv)
	{
	case 1:
		if (m_Player.iEx >= 500)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 50;
			m_Player.iCurrHp += 50;
			m_Player.iAttack += 20;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;
		}
		break;
	case 2:
		if (m_Player.iEx >= 1000)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 50;
			m_Player.iCurrHp += 50;
			m_Player.iAttack += 20;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;

			strcpy_s(m_PlayerSkill[0].sName, sizeof(m_PlayerSkill[0].sName), "[ ȸ���� ���� ]");
			m_PlayerSkill[0].iSkillLv = 1;
			m_PlayerSkill[0].iDamage = 5;
			m_PlayerSkill[0].iDefense = 2;
			m_PlayerSkill[0].iRecovery = 0;
			m_PlayerSkill[0].iUseCoint = 1;
		}
		break;
	case 3:
		if (m_Player.iEx >= 1500)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 50;
			m_Player.iCurrHp += 50;
			m_Player.iAttack += 20;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;
		}
		break;
	case 4:
		if (m_Player.iEx >= 2000)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 50;
			m_Player.iCurrHp += 50;
			m_Player.iAttack += 20;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;
		}
		break;
	case 5:
		if (m_Player.iEx >= 2500)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 100;
			m_Player.iCurrHp += 100;
			m_Player.iAttack += 25;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;
			
			strcpy_s(m_PlayerSkill[1].sName, sizeof(m_PlayerSkill[1].sName), "[ ���м� ���� ]");
			m_PlayerSkill[1].iSkillLv = 1;
			m_PlayerSkill[1].iDamage = 10;
			m_PlayerSkill[1].iDefense = 5;
			m_PlayerSkill[1].iRecovery = 0;
			m_PlayerSkill[0].iUseCoint = 2;
		}
		break;
	case 6:
		if (m_Player.iEx >= 3000)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 100;
			m_Player.iCurrHp += 100;
			m_Player.iAttack += 30;
			m_Player.iDefense += 10;
			m_Player.iCoin += 500;
		}
		break;
	case 7:
		if (m_Player.iEx >= 3500)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 100;
			m_Player.iCurrHp += 100;
			m_Player.iAttack += 30;
			m_Player.iDefense += 20;
			m_Player.iCoin += 500;
		}
		break;
	case 8:
		if (m_Player.iEx >= 4000)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 100;
			m_Player.iCurrHp += 100;
			m_Player.iAttack += 30;
			m_Player.iDefense += 20;
			m_Player.iCoin += 500;
			
			strcpy_s(m_PlayerSkill[2].sName, sizeof(m_PlayerSkill[2].sName), "[ ����� ȸ�� ]");
			m_PlayerSkill[2].iSkillLv = 1;
			m_PlayerSkill[2].iDamage = 0;
			m_PlayerSkill[2].iDefense = 0;
			m_PlayerSkill[2].iRecovery = 50;
			m_PlayerSkill[0].iUseCoint = 3;
		}
		break;
	case 9:
		if (m_Player.iEx >= 5000)
		{
			m_Player.iLv += 1;
			m_Player.iMaxHp += 100;
			m_Player.iCurrHp += 100;
			m_Player.iAttack += 50;
			m_Player.iDefense += 30;
			m_Player.iCoin += 1000;
		}
		break;
	default:
		break;
	}
}

void CPlayer::Skill_Update()
{
	int iInput(0);

	while (true)
	{
		Skill_Output();
		cout << "���� ���� : " << m_Player.iCoin << endl << endl;
		cout << "1) ��ų��ȭ. 2) ����ȭ�� : ";
		cin >> iInput;

		if (iInput == 1)
		{
			if (m_PlayerSkill[0].iUseCoint <= 0)
			{
				cout << "�����ϰ� �ִ� ��ų�� �����ϴ�." << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "��ȭ�ϰ� ���� ��ų ��ȣ ���� : ";
				cin >> iInput;

				if (iInput == 1)
				{
					if (m_Player.iCoin >= 200)
					{
						m_Player.iCoin -= 200;
						m_PlayerSkill[0].iSkillLv += 1;
						m_PlayerSkill[0].iDamage += 3;
						cout << "��ų ��ȭ ����!" << endl;
						system("pause");
					}
					else
					{
						cout << "������ �����մϴ�." << endl;
						system("pause");
					}
				}
				else if (iInput == 2)
				{
					if (m_Player.iCoin >= 200)
					{
						m_Player.iCoin -= 200;
						m_PlayerSkill[1].iSkillLv += 1;
						m_PlayerSkill[1].iDamage += 10;
						m_PlayerSkill[1].iDefense += 5;
						cout << "��ų ��ȭ ����!" << endl;
						system("pause");
					}
					else
					{
						cout << "������ �����մϴ�." << endl;
						system("pause");
					}
				}
				else if (iInput == 3)
				{
					if (m_Player.iCoin >= 200)
					{
						m_Player.iCoin -= 200;
						m_PlayerSkill[2].iSkillLv += 1;
						m_PlayerSkill[2].iRecovery += 10;
						cout << "��ų ��ȭ ����!" << endl;
						system("pause");
					}
					else
					{
						cout << "������ �����մϴ�." << endl;
						system("pause");
					}
				}
				else
				{
					cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
					system("pause");
				}
				system("cls");
			}
		}
		else if (iInput == 2)
		{
			system("cls");
			return;
		}
		else
		{
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			system("cls");
		}
			
	}
}

void CPlayer::Skill_Output() const
{
	cout << "[���� ��ų]" << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i < m_PlayerSkill[0].iUseCoint; ++i)
	{
		cout << "��ų ��ȣ : " << i + 1 << " ��" << endl;
		cout << "��ų �̸� : " << m_PlayerSkill[i].sName << endl;
		cout << "��ų ���� : " << m_PlayerSkill[i].iSkillLv << " ����" << endl;
		cout << "��ų ȿ�� : ���ݷ� " << m_PlayerSkill[i].iDamage << " ����" << endl;
		cout << "��ų ȿ�� : ���� " << m_PlayerSkill[i].iDefense << " ����" << endl;
		cout << "��ų ȿ�� : ����� " << m_PlayerSkill[i].iRecovery << " ����" << endl;
		cout << "---------------------------" << endl;
	}
}

void CPlayer::Inven_Update()
{
	int iInput(0), i_Input(0);

	while (true)
	{
		Inven_Output();
		cout << "1) ������ ����. 2) ������ ���� ����. 3) ������ �Ǹ�. 4) ����ȭ�� : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1: // ������ ���� : ������ �ִ� �迭 -> ���� �迭
			if (m_PlayerInven_Have[0].iCount > 0)
			{
				cout << "������ ������ ��ȣ �Է�: ";
				cin >> i_Input;
				switch (i_Input)
				{
				case 1:
					if (m_PlayerInven_Have[0].iCount > 0 && m_PlayerInven_Equip[0].iCount < 3)
					{
						// ������ ������ ȿ�� �÷��̾�� ������Ʈ
						Update_PlayerInfo(m_PlayerInven_Have, 0, true);
						// �̵��� �迭 �ʱ�ȭ �� ����
						Inven_ArrSort(1, m_PlayerInven_Equip, m_PlayerInven_Have);
					}
					break;
				case 2:
					if (m_PlayerInven_Have[0].iCount > 1 && m_PlayerInven_Equip[0].iCount < 3)
					{
						Update_PlayerInfo(m_PlayerInven_Have, 1, true);
						Inven_ArrSort(2, m_PlayerInven_Equip, m_PlayerInven_Have);
					}
					break;
				case 3:
					if (m_PlayerInven_Have[0].iCount > 2 && m_PlayerInven_Equip[0].iCount < 3)
					{
						Update_PlayerInfo(m_PlayerInven_Have, 2, true);
						Inven_ArrSort(3, m_PlayerInven_Equip, m_PlayerInven_Have);
					}
					break;
				default:
					break;
				}
			}
			else
			{
				cout << " [Error] �����ϰ� �ִ� �������� �����ϴ�." << endl;
				system("pause");
			}
			break;
		case 2:
			if (m_PlayerInven_Equip[0].iCount > 0)
			{
				cout << "���� ������ ������ ��ȣ �Է�: ";
				cin >> i_Input;
				switch (i_Input)
				{
				case 1:
					if (m_PlayerInven_Have[0].iCount < 3 && m_PlayerInven_Equip[0].iCount > 0)
					{
						Update_PlayerInfo(m_PlayerInven_Equip, 0, false);
						Inven_ArrSort(1, m_PlayerInven_Have, m_PlayerInven_Equip);
					}
					break;
				case 2:
					if (m_PlayerInven_Have[0].iCount < 3 && m_PlayerInven_Equip[0].iCount > 1)
					{
						Update_PlayerInfo(m_PlayerInven_Equip, 1, false);
						Inven_ArrSort(2, m_PlayerInven_Have, m_PlayerInven_Equip);
					}
					break;
				case 3:
					if (m_PlayerInven_Have[0].iCount < 3 && m_PlayerInven_Equip[0].iCount > 2)
					{
						Update_PlayerInfo(m_PlayerInven_Equip, 2, false);
						Inven_ArrSort(3, m_PlayerInven_Have, m_PlayerInven_Equip);
					}
					break;
				default:
					break;
				}
			}
			else
			{
				cout << " [Error] �����ϰ� �ִ� �������� �����ϴ�." << endl;
				system("pause");
			}
			break;
		case 3:
			if (m_PlayerInven_Have[0].iCount > 0)
			{
				cout << "�Ǹ��� ������ ��ȣ �Է�: ";
				cin >> i_Input;
				switch (i_Input)
				{
				case 1:
					if (m_PlayerInven_Have[0].iCount > 0)
					{
						m_Player.iCoin += m_PlayerInven_Have[0].iCoin;
						// �������� ������ �迭 �ʱ�ȭ �� �迭 ����
						if (m_PlayerInven_Have[0].iCount == 1)
						{
							strcpy_s(m_PlayerInven_Have[0].sName, sizeof(m_PlayerInven_Have[0].sName), "������");
							strcpy_s(m_PlayerInven_Have[0].sItemEffect, sizeof(m_PlayerInven_Have[0].sItemEffect), "");
							m_PlayerInven_Have[0].iEffectNum = 0;
							m_PlayerInven_Have[0].iNum = 0;
							m_PlayerInven_Have[0].iCoin = 0;

							m_PlayerInven_Have[0].iCount -= 1;
						}
						else if (m_PlayerInven_Have[0].iCount == 2)
						{
							strcpy_s(m_PlayerInven_Have[0].sName, sizeof(m_PlayerInven_Have[0].sName), m_PlayerInven_Have[1].sName);
							strcpy_s(m_PlayerInven_Have[0].sItemEffect, sizeof(m_PlayerInven_Have[0].sItemEffect), m_PlayerInven_Have[1].sItemEffect);
							m_PlayerInven_Have[0].iEffectNum = m_PlayerInven_Have[1].iEffectNum;
							m_PlayerInven_Have[0].iNum = m_PlayerInven_Have[1].iNum;
							m_PlayerInven_Have[0].iCoin = m_PlayerInven_Have[1].iCoin;

							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), "������");
							strcpy_s(m_PlayerInven_Have[1].sItemEffect, sizeof(m_PlayerInven_Have[1].sItemEffect), "");
							m_PlayerInven_Have[1].iEffectNum = 0;
							m_PlayerInven_Have[1].iNum = 0;
							m_PlayerInven_Have[1].iCoin = 0;

							m_PlayerInven_Have[0].iCount -= 1;
						}
						else if (m_PlayerInven_Have[0].iCount == 3)
						{
							strcpy_s(m_PlayerInven_Have[0].sName, sizeof(m_PlayerInven_Have[0].sName), m_PlayerInven_Have[1].sName);
							strcpy_s(m_PlayerInven_Have[0].sItemEffect, sizeof(m_PlayerInven_Have[0].sItemEffect), m_PlayerInven_Have[1].sItemEffect);
							m_PlayerInven_Have[0].iEffectNum = m_PlayerInven_Have[1].iEffectNum;
							m_PlayerInven_Have[0].iNum = m_PlayerInven_Have[1].iNum;
							m_PlayerInven_Have[0].iCoin = m_PlayerInven_Have[1].iCoin;

							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), m_PlayerInven_Have[2].sName);
							strcpy_s(m_PlayerInven_Have[1].sItemEffect, sizeof(m_PlayerInven_Have[1].sItemEffect), m_PlayerInven_Have[2].sItemEffect);
							m_PlayerInven_Have[1].iEffectNum = m_PlayerInven_Have[2].iEffectNum;
							m_PlayerInven_Have[1].iNum = m_PlayerInven_Have[2].iNum;
							m_PlayerInven_Have[1].iCoin = m_PlayerInven_Have[2].iCoin;

							strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "������");
							strcpy_s(m_PlayerInven_Have[2].sItemEffect, sizeof(m_PlayerInven_Have[2].sItemEffect), "");
							m_PlayerInven_Have[2].iEffectNum = 0;
							m_PlayerInven_Have[2].iNum = 0;
							m_PlayerInven_Have[2].iCoin = 0;

							m_PlayerInven_Have[0].iCount -= 1;
						}
					}
					break;
				case 2:
					if (m_PlayerInven_Have[0].iCount > 1)
					{
						m_Player.iCoin += m_PlayerInven_Have[1].iCoin;
						if (m_PlayerInven_Have[0].iCount == 2)
						{
							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), "������");
							strcpy_s(m_PlayerInven_Have[1].sItemEffect, sizeof(m_PlayerInven_Have[1].sItemEffect), "");
							m_PlayerInven_Have[1].iEffectNum = 0;
							m_PlayerInven_Have[1].iNum = 0;
							m_PlayerInven_Have[1].iCoin = 0;

							m_PlayerInven_Have[0].iCount -= 1;
						}
						else if (m_PlayerInven_Have[0].iCount == 3)
						{
							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), m_PlayerInven_Have[2].sName);
							strcpy_s(m_PlayerInven_Have[1].sItemEffect, sizeof(m_PlayerInven_Have[1].sItemEffect), m_PlayerInven_Have[2].sItemEffect);
							m_PlayerInven_Have[1].iEffectNum = m_PlayerInven_Have[2].iEffectNum;
							m_PlayerInven_Have[1].iNum = m_PlayerInven_Have[2].iNum;
							m_PlayerInven_Have[1].iCoin = m_PlayerInven_Have[2].iCoin;

							strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "������");
							strcpy_s(m_PlayerInven_Have[2].sItemEffect, sizeof(m_PlayerInven_Have[2].sItemEffect), "");
							m_PlayerInven_Have[2].iEffectNum = 0;
							m_PlayerInven_Have[2].iNum = 0;
							m_PlayerInven_Have[2].iCoin = 0;

							m_PlayerInven_Have[0].iCount -= 1;
						}
					}
					break;
				case 3:
					if (m_PlayerInven_Have[0].iCount > 2)
					{
						m_Player.iCoin += m_PlayerInven_Have[2].iCoin;

						strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "������");
						strcpy_s(m_PlayerInven_Have[2].sItemEffect, sizeof(m_PlayerInven_Have[2].sItemEffect), "");
						m_PlayerInven_Have[2].iEffectNum = 0;
						m_PlayerInven_Have[2].iNum = 0;
						m_PlayerInven_Have[2].iCoin = 0;

						m_PlayerInven_Have[0].iCount -= 1;
					}
					break;
				default:
					break;
				}
			}
			else
			{
			    cout << " [Error] �����ϰ� �ִ� �������� �����ϴ�." << endl;
			    system("pause");
			}
			break;
		case 4:
			system("cls");
			return;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
		system("cls");
	}
}

void CPlayer::Inven_Output() const
{
	cout << "=============================================" << endl;
	cout << "[������ ������]" << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < m_PlayerInven_Equip[0].iCount; ++i)
	{
		cout << "������ ������: " << i + 1 << " ��" << endl;
		cout << "������ �̸� : " << m_PlayerInven_Equip[i].sName << endl;
		cout << "������ ȿ�� : " << m_PlayerInven_Equip[i].sItemEffect << m_PlayerInven_Equip[i].iEffectNum << "����" << endl;
		cout << "---------------------------------------------" << endl;
	}
	cout << "=============================================" << endl;
	cout << "[�������� ������]" << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < m_PlayerInven_Have[0].iCount; ++i)
	{
		cout << "�������� ������: " << i + 1 << " ��" << endl;
		cout << "������ �̸� : " << m_PlayerInven_Have[i].sName << endl;
		cout << "������ ȿ�� : " << m_PlayerInven_Have[i].sItemEffect << m_PlayerInven_Have[i].iEffectNum << "����" << endl;
		cout << "---------------------------------------------" << endl;
	}
	cout << "�������� : " << m_Player.iCoin << endl;
	cout << "=============================================" << endl;
}

void CPlayer::Inven_ArrSort(int _iInputNum, InvenInfo _tlocation[], InvenInfo _tDatamove[]) const
{
	switch (_iInputNum)
	{
	case 1:
		// ���ϴ� �迭�� �̵�
		strcpy_s(_tlocation[_tlocation[0].iCount].sName, sizeof(_tlocation[_tlocation[0].iCount].sName), _tDatamove[0].sName);
		strcpy_s(_tlocation[_tlocation[0].iCount].sItemEffect, sizeof(_tlocation[_tlocation[0].iCount].sItemEffect), _tDatamove[0].sItemEffect);
		_tlocation[_tlocation[0].iCount].iEffectNum = _tDatamove[0].iEffectNum;
		_tlocation[_tlocation[0].iCount].iNum = _tDatamove[0].iNum;
		_tlocation[_tlocation[0].iCount].iCoin = _tDatamove[0].iCoin;
		_tlocation[0].iCount++;

		// �̵��� ������ �迭 �ʱ�ȭ �� �迭 ����
		if (_tDatamove[0].iCount == 1)
		{
			strcpy_s(_tDatamove[0].sName, sizeof(_tDatamove[0].sName), "������");
			strcpy_s(_tDatamove[0].sItemEffect, sizeof(_tDatamove[0].sItemEffect), "");
			_tDatamove[0].iEffectNum = 0;
			_tDatamove[0].iNum = 0;
			_tDatamove[0].iCoin = 0;
			_tDatamove[0].iCount -= 1;
		}
		else if (_tDatamove[0].iCount == 2)
		{
			strcpy_s(_tDatamove[0].sName, sizeof(_tDatamove[0].sName), _tDatamove[1].sName);
			strcpy_s(_tDatamove[0].sItemEffect, sizeof(_tDatamove[0].sItemEffect), _tDatamove[1].sItemEffect);
			_tDatamove[0].iEffectNum = _tDatamove[1].iEffectNum;
			_tDatamove[0].iNum = _tDatamove[1].iNum;
			_tDatamove[0].iCoin = _tDatamove[1].iCoin;

			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), "������");
			strcpy_s(_tDatamove[1].sItemEffect, sizeof(_tDatamove[1].sItemEffect), "");
			_tDatamove[1].iEffectNum = 0;
			_tDatamove[1].iNum = 0;
			_tDatamove[1].iCoin = 0;
			_tDatamove[0].iCount -= 1;
		}
		else if (_tDatamove[0].iCount == 3)
		{
			strcpy_s(_tDatamove[0].sName, sizeof(_tDatamove[0].sName), _tDatamove[1].sName);
			strcpy_s(_tDatamove[0].sItemEffect, sizeof(_tDatamove[0].sItemEffect), _tDatamove[1].sItemEffect);
			_tDatamove[0].iEffectNum = _tDatamove[1].iEffectNum;
			_tDatamove[0].iNum = _tDatamove[1].iNum;
			_tDatamove[0].iCoin = _tDatamove[1].iCoin;

			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), _tDatamove[2].sName);
			strcpy_s(_tDatamove[1].sItemEffect, sizeof(_tDatamove[1].sItemEffect), _tDatamove[2].sItemEffect);
			_tDatamove[1].iEffectNum = _tDatamove[2].iEffectNum;
			_tDatamove[1].iNum = _tDatamove[2].iNum;
			_tDatamove[1].iCoin = _tDatamove[2].iCoin;

			strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "������");
			strcpy_s(_tDatamove[2].sItemEffect, sizeof(_tDatamove[2].sItemEffect), "");
			_tDatamove[2].iEffectNum = 0;
			_tDatamove[2].iNum = 0;
			_tDatamove[2].iCoin = 0;
			_tDatamove[0].iCount -= 1;
		}
		break;
	case 2:
		strcpy_s(_tlocation[_tlocation[0].iCount].sName, sizeof(_tlocation[_tlocation[0].iCount].sName), _tDatamove[1].sName);
		strcpy_s(_tlocation[_tlocation[0].iCount].sItemEffect, sizeof(_tlocation[_tlocation[0].iCount].sItemEffect), _tDatamove[1].sItemEffect);
		_tlocation[_tlocation[0].iCount].iEffectNum = _tDatamove[1].iEffectNum;
		_tlocation[_tlocation[0].iCount].iNum = _tDatamove[1].iNum;
		_tlocation[_tlocation[0].iCount].iCoin = _tDatamove[1].iCoin;
		_tlocation[0].iCount++;

		if (_tDatamove[0].iCount == 2)
		{
			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), "������");
			strcpy_s(_tDatamove[1].sItemEffect, sizeof(_tDatamove[1].sItemEffect), "");
			_tDatamove[1].iEffectNum = 0;
			_tDatamove[1].iNum = 0;
			_tDatamove[1].iCoin = 0;
			_tDatamove[0].iCount -= 1;
		}
		else if (_tDatamove[0].iCount == 3)
		{
			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), _tDatamove[2].sName);
			strcpy_s(_tDatamove[1].sItemEffect, sizeof(_tDatamove[1].sItemEffect), _tDatamove[2].sItemEffect);
			_tDatamove[1].iEffectNum = _tDatamove[2].iEffectNum;
			_tDatamove[1].iNum = _tDatamove[2].iNum;
			_tDatamove[1].iCoin = _tDatamove[2].iCoin;

			strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "������");
			strcpy_s(_tDatamove[2].sItemEffect, sizeof(_tDatamove[2].sItemEffect), "");
			_tDatamove[2].iEffectNum = 0;
			_tDatamove[2].iNum = 0;
			_tDatamove[2].iCoin = 0;
			_tDatamove[0].iCount -= 1;
		}
		break;
	case 3:
		strcpy_s(_tlocation[_tlocation[0].iCount].sName, sizeof(_tlocation[_tlocation[0].iCount].sName), _tDatamove[2].sName);
		strcpy_s(_tlocation[_tlocation[0].iCount].sItemEffect, sizeof(_tlocation[_tlocation[0].iCount].sItemEffect), _tDatamove[2].sItemEffect);
		_tlocation[_tlocation[0].iCount].iEffectNum = _tDatamove[2].iEffectNum;
		_tlocation[_tlocation[0].iCount].iNum = _tDatamove[2].iNum;
		_tlocation[_tlocation[0].iCount].iCoin = _tDatamove[2].iCoin;
		_tlocation[0].iCount++;

		strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "������");
		strcpy_s(_tDatamove[2].sItemEffect, sizeof(_tDatamove[2].sItemEffect), "");
		_tDatamove[2].iEffectNum = 0;
		_tDatamove[2].iNum = 0;
		_tDatamove[2].iCoin = 0;
		_tDatamove[0].iCount -= 1;
		break;
	default:
		break;
	}
}

void CPlayer::Update_PlayerInfo(InvenInfo _tlocation[], int iNum, bool _btrue)
{
	if (_btrue)
	{
		// �����Ҷ����� ���� ������Ʈ
		if (_tlocation[iNum].iNum == 1)
		{
			m_Player.iAttack += _tlocation[iNum].iEffectNum;
		}
		else if (_tlocation[iNum].iNum == 2)
		{
			m_Player.iDefense += _tlocation[iNum].iEffectNum;
		}
		else if (_tlocation[iNum].iNum == 3)
		{
			m_Player.iCurrHp += _tlocation[iNum].iEffectNum;
			if (m_Player.iCurrHp > m_Player.iMaxHp)
				m_Player.iCurrHp = m_Player.iMaxHp;
		}
	}
	else if (!_btrue)
	{
		// ���������Ҷ����� ���� ������Ʈ
		if (_tlocation[iNum].iNum == 1)
		{
			m_Player.iAttack -= _tlocation[iNum].iEffectNum;
		}
		else if (_tlocation[iNum].iNum == 2)
		{
			m_Player.iDefense -= _tlocation[iNum].iEffectNum;
		}
	}
}

void CPlayer::Store_Update()
{
	int iInput(0), i_Input(0);

	while (true)
	{
		system("cls");
		cout << "=====================================" << endl;
		cout << "[������ ����]" << endl;
		cout << "-------------------------------------" << endl;
		cout << "1��. ���� �� ( 300 ���� )" << endl;
		cout << "   - ���ݷ� 30 ���� ! " << endl << endl;

		cout << "2��. ���� ���� ( 500 ���� )" << endl;
		cout << "   - ���� 20 ���� ! " << endl << endl;

		cout << "3��. ü�� ȸ��_1ȸ�� ( 1000 ���� )" << endl;
		cout << "   - ü��ȸ�� 100 ���� ! _1ȸ " << endl;
		cout << "-------------------------------------" << endl;
		cout << "�������� : " << m_Player.iCoin << endl;
		cout << "=====================================" << endl;
		cout << "1) ������ ����. 2) ����ȭ�� : ";
		cin >> iInput;

		if (iInput == 1)
		{
			cout << "������ ������ ��ȣ �Է�: ";
			cin >> i_Input;

			switch (i_Input)
			{
			case 1:
				if (m_Player.iCoin >= 300 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 1;

					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "���� ��");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "���ݷ�");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 30;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 300;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 300;
					cout << "���� ����!" << endl;
				}
				else
				{
					cout << "���� ����!" << endl;
				}
				break;
			case 2:
				if (m_Player.iCoin >= 500 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 2;
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "���� ����");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "����");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 20;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 500;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 500;
					cout << "���� ����!" << endl;
				}
				else
				{
					cout << "���� ����!" << endl;
				}
				break;
			case 3:
				if (m_Player.iCoin >= 1000 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 3;
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "ü�� ȸ��_1ȸ��");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "ü��");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 100;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 1000;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 1000;
					cout << "���� ����!" << endl;
				}
				else
				{
					cout << "���� ����!" << endl;
				}
				break;
			default:
				cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
				break;
			}
		}
		else if (iInput == 2)
		{
			system("cls");
			return;
		}
		else
		{
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
		}
		system("pause");
		system("cls");
	}
}

void CPlayer::Output_Info()
{
	if (m_Player.iCurrHp <= 0)
		m_Player.iCurrHp = 0;

	cout << "=============================================" << endl;
	cout << "[SYSTEM] �÷��̾� ������" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "�̸� : " << m_Player.sName << "\t" << "���� : " << m_Player.sGender << endl;
	cout << "���� : " << m_Player.iLv << "\t" << "����ġ : " << m_Player.iEx << endl;
	cout << "���� : " << m_Player.sSpecies << "\t" << "���� : " << m_Player.sJob << endl;
	cout << "ü�� : " << m_Player.iCurrHp << "\t" << "���ݷ� : " << m_Player.iAttack << "\t" << "���� : " << m_Player.iDefense << endl;
	cout << "---------------------------------------------" << endl;
	cout << "�������� : " << m_Player.iCoin << endl;
	cout << "=============================================" << endl;
}

//void CPlayer::Homework_Store_Update()
//{
//	int iInput(0);
//
//	while (true)
//	{
//		system("cls");
//		cout << "=====================================" << endl;
//		cout << "[������ ���� 2]" << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "1) �ʱ� ����. 2) �߱� ����. 3) ��� ����. 4) ����ȭ��: ";
//		cin >> iInput;
//
//		switch (iInput)
//		{
//		case 1:
//			_Homework_Store("�ʱ�", 10, 10, 100);
//			break;
//		case 2:
//			_Homework_Store("�߱�", 20, 20, 200);
//			break;
//		case 3:
//			_Homework_Store("���", 30, 30, 300);
//			break;
//		case 4:
//			return;
//			break;
//		default:
//			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
//			system("pause");
//			break;
//		}
//	}
//}
//
//void CPlayer::_Homework_Store(string _sName, int _iAttack, int _iDefense, int _iCoin)
//{
//	int iInput(0);
//
//	while (true)
//	{
//		system("cls");
//		cout << "=====================================" << endl;
//		cout << "[" << _sName << " ������ ���� 2]" << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "1��) " << _sName << " ����   _" << _iCoin << " ��" << endl;
//		cout << "   - ���ݷ� " << _iAttack << " ���� ! " << endl << endl;
//		cout << "2��) " << _sName << " �� _" << _iCoin << " ��" << endl;
//		cout << "   - ���� " << _iDefense << " ���� ! " << endl << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "�������� : " << m_Player.iCoin << endl;
//		cout << "=====================================" << endl;
//		cout << "1) ������ ����. 2) ����ȭ�� : ";
//		cin >> iInput;
//
//		if (iInput == 1)
//		{
//			cout << "������ ���ű�� ���� ���� ����" << endl;
//			system("pause");
//		}
//		else if (iInput == 2)
//		{
//			return;
//		}
//		else
//		{
//			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
//			system("pause");
//		}
//	}
//}