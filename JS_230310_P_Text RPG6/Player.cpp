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
		cout << "원하시는 종족을 선택해주세요." << endl;
		cout << "1) 인간. 2) 엘프. 3) 수인 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "인간");
			m_Player.iMaxHp = 100;
			m_Player.iCurrHp = 100;
			bSelet = true;
			break;
		case 2:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "엘프");
			m_Player.iMaxHp = 130;
			m_Player.iCurrHp = 130;
			bSelet = true;
			break;
		case 3:
			strcpy_s(m_Player.sSpecies, sizeof(m_Player.sSpecies), "수인");
			m_Player.iMaxHp = 150;
			m_Player.iCurrHp = 150;
			bSelet = true;
			break;
		default:
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
			break;
		}
	}
	iInput = 0;
	bSelet = false;
	
	while (!bSelet)
	{
		system("cls");
		cout << "원하시는 성별을 선택해주세요." << endl;
		cout << "1) 여자. 2) 남자 : ";
		cin >> iInput;

		if (iInput == 1)
		{
			strcpy_s(m_Player.sGender, sizeof(m_Player.sGender), "여자");
			m_Player.iDefense = 10;
			bSelet = true;
		}
		else if (iInput == 2)
		{
			strcpy_s(m_Player.sGender, sizeof(m_Player.sGender), "남자");
			m_Player.iDefense = 20;
			bSelet = true;
		}
		else
		{
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
		}
	}
	iInput = 0;
	bSelet = false;

	while (!bSelet)
	{
		system("cls");
		cout << "원하시는 직업을 선택해주세요." << endl;
		cout << "1) 전사. 2) 마법사. 3) 도적 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "전사");
			m_Player.iAttack = 10;
			bSelet = true;
			break;
		case 2:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "마법사");
			m_Player.iAttack = 20;
			bSelet = true;
			break;
		case 3:
			strcpy_s(m_Player.sJob, sizeof(m_Player.sJob), "도적");
			m_Player.iAttack = 30;
			bSelet = true;
			break;
		default:
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
			break;
		}
	}
	
	system("cls");
	cout << "사용할 플레이어 이름을 입력하세요 : ";
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
		cout << "저장된 정보를 불러옵니다." << endl;
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
		cout << "저장된 정보가 없습니다." << endl;
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
		cout << "플레이어 정보를 저장합니다." << endl;
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
		cout << "플레이어 정보 저장 실패" << endl;
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

			strcpy_s(m_PlayerSkill[0].sName, sizeof(m_PlayerSkill[0].sName), "[ 회심의 공격 ]");
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
			
			strcpy_s(m_PlayerSkill[1].sName, sizeof(m_PlayerSkill[1].sName), "[ 스패셜 어택 ]");
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
			
			strcpy_s(m_PlayerSkill[2].sName, sizeof(m_PlayerSkill[2].sName), "[ 생명력 회복 ]");
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
		cout << "보유 코인 : " << m_Player.iCoin << endl << endl;
		cout << "1) 스킬강화. 2) 메인화면 : ";
		cin >> iInput;

		if (iInput == 1)
		{
			if (m_PlayerSkill[0].iUseCoint <= 0)
			{
				cout << "보유하고 있는 스킬이 없습니다." << endl;
				system("pause");
				system("cls");
			}
			else
			{
				cout << "강화하고 싶은 스킬 번호 선택 : ";
				cin >> iInput;

				if (iInput == 1)
				{
					if (m_Player.iCoin >= 200)
					{
						m_Player.iCoin -= 200;
						m_PlayerSkill[0].iSkillLv += 1;
						m_PlayerSkill[0].iDamage += 3;
						cout << "스킬 강화 성공!" << endl;
						system("pause");
					}
					else
					{
						cout << "코인이 부족합니다." << endl;
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
						cout << "스킬 강화 성공!" << endl;
						system("pause");
					}
					else
					{
						cout << "코인이 부족합니다." << endl;
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
						cout << "스킬 강화 성공!" << endl;
						system("pause");
					}
					else
					{
						cout << "코인이 부족합니다." << endl;
						system("pause");
					}
				}
				else
				{
					cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
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
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
			system("cls");
		}
			
	}
}

void CPlayer::Skill_Output() const
{
	cout << "[보유 스킬]" << endl;
	cout << "---------------------------" << endl;
	for (int i = 0; i < m_PlayerSkill[0].iUseCoint; ++i)
	{
		cout << "스킬 번호 : " << i + 1 << " 번" << endl;
		cout << "스킬 이름 : " << m_PlayerSkill[i].sName << endl;
		cout << "스킬 레벨 : " << m_PlayerSkill[i].iSkillLv << " 레벨" << endl;
		cout << "스킬 효과 : 공격력 " << m_PlayerSkill[i].iDamage << " 증가" << endl;
		cout << "스킬 효과 : 방어력 " << m_PlayerSkill[i].iDefense << " 증가" << endl;
		cout << "스킬 효과 : 생명력 " << m_PlayerSkill[i].iRecovery << " 증가" << endl;
		cout << "---------------------------" << endl;
	}
}

void CPlayer::Inven_Update()
{
	int iInput(0), i_Input(0);

	while (true)
	{
		Inven_Output();
		cout << "1) 아이템 장착. 2) 아이템 장착 해제. 3) 아이템 판매. 4) 메인화면 : ";
		cin >> iInput;

		switch (iInput)
		{
		case 1: // 아이템 장착 : 가지고 있는 배열 -> 장착 배열
			if (m_PlayerInven_Have[0].iCount > 0)
			{
				cout << "장착할 아이템 번호 입력: ";
				cin >> i_Input;
				switch (i_Input)
				{
				case 1:
					if (m_PlayerInven_Have[0].iCount > 0 && m_PlayerInven_Equip[0].iCount < 3)
					{
						// 장착한 아이템 효과 플레이어에게 업데이트
						Update_PlayerInfo(m_PlayerInven_Have, 0, true);
						// 이동한 배열 초기화 및 정렬
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
				cout << " [Error] 보유하고 있는 아이템이 없습니다." << endl;
				system("pause");
			}
			break;
		case 2:
			if (m_PlayerInven_Equip[0].iCount > 0)
			{
				cout << "장착 해제할 아이템 번호 입력: ";
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
				cout << " [Error] 장착하고 있는 아이템이 없습니다." << endl;
				system("pause");
			}
			break;
		case 3:
			if (m_PlayerInven_Have[0].iCount > 0)
			{
				cout << "판매할 아이템 번호 입력: ";
				cin >> i_Input;
				switch (i_Input)
				{
				case 1:
					if (m_PlayerInven_Have[0].iCount > 0)
					{
						m_Player.iCoin += m_PlayerInven_Have[0].iCoin;
						// 보유중인 아이템 배열 초기화 및 배열 당기기
						if (m_PlayerInven_Have[0].iCount == 1)
						{
							strcpy_s(m_PlayerInven_Have[0].sName, sizeof(m_PlayerInven_Have[0].sName), "미장착");
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

							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), "미장착");
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

							strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "미장착");
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
							strcpy_s(m_PlayerInven_Have[1].sName, sizeof(m_PlayerInven_Have[1].sName), "미장착");
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

							strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "미장착");
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

						strcpy_s(m_PlayerInven_Have[2].sName, sizeof(m_PlayerInven_Have[2].sName), "미장착");
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
			    cout << " [Error] 보유하고 있는 아이템이 없습니다." << endl;
			    system("pause");
			}
			break;
		case 4:
			system("cls");
			return;
		default:
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
			system("pause");
			break;
		}
		system("cls");
	}
}

void CPlayer::Inven_Output() const
{
	cout << "=============================================" << endl;
	cout << "[장착된 아이템]" << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < m_PlayerInven_Equip[0].iCount; ++i)
	{
		cout << "장착된 아이템: " << i + 1 << " 번" << endl;
		cout << "아이템 이름 : " << m_PlayerInven_Equip[i].sName << endl;
		cout << "아이템 효과 : " << m_PlayerInven_Equip[i].sItemEffect << m_PlayerInven_Equip[i].iEffectNum << "증가" << endl;
		cout << "---------------------------------------------" << endl;
	}
	cout << "=============================================" << endl;
	cout << "[보유중인 아이템]" << endl;
	cout << "---------------------------------------------" << endl;
	for (int i = 0; i < m_PlayerInven_Have[0].iCount; ++i)
	{
		cout << "보유중인 아이템: " << i + 1 << " 번" << endl;
		cout << "아이템 이름 : " << m_PlayerInven_Have[i].sName << endl;
		cout << "아이템 효과 : " << m_PlayerInven_Have[i].sItemEffect << m_PlayerInven_Have[i].iEffectNum << "증가" << endl;
		cout << "---------------------------------------------" << endl;
	}
	cout << "보유코인 : " << m_Player.iCoin << endl;
	cout << "=============================================" << endl;
}

void CPlayer::Inven_ArrSort(int _iInputNum, InvenInfo _tlocation[], InvenInfo _tDatamove[]) const
{
	switch (_iInputNum)
	{
	case 1:
		// 원하는 배열로 이동
		strcpy_s(_tlocation[_tlocation[0].iCount].sName, sizeof(_tlocation[_tlocation[0].iCount].sName), _tDatamove[0].sName);
		strcpy_s(_tlocation[_tlocation[0].iCount].sItemEffect, sizeof(_tlocation[_tlocation[0].iCount].sItemEffect), _tDatamove[0].sItemEffect);
		_tlocation[_tlocation[0].iCount].iEffectNum = _tDatamove[0].iEffectNum;
		_tlocation[_tlocation[0].iCount].iNum = _tDatamove[0].iNum;
		_tlocation[_tlocation[0].iCount].iCoin = _tDatamove[0].iCoin;
		_tlocation[0].iCount++;

		// 이동한 아이템 배열 초기화 및 배열 당기기
		if (_tDatamove[0].iCount == 1)
		{
			strcpy_s(_tDatamove[0].sName, sizeof(_tDatamove[0].sName), "미장착");
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

			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), "미장착");
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

			strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "미장착");
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
			strcpy_s(_tDatamove[1].sName, sizeof(_tDatamove[1].sName), "미장착");
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

			strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "미장착");
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

		strcpy_s(_tDatamove[2].sName, sizeof(_tDatamove[2].sName), "미장착");
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
		// 장착할때마다 스탯 업데이트
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
		// 장착해제할때마다 스탯 업데이트
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
		cout << "[아이템 상점]" << endl;
		cout << "-------------------------------------" << endl;
		cout << "1번. 멋진 검 ( 300 코인 )" << endl;
		cout << "   - 공격력 30 증가 ! " << endl << endl;

		cout << "2번. 멋진 방패 ( 500 코인 )" << endl;
		cout << "   - 방어력 20 증가 ! " << endl << endl;

		cout << "3번. 체력 회복_1회용 ( 1000 코인 )" << endl;
		cout << "   - 체력회복 100 증가 ! _1회 " << endl;
		cout << "-------------------------------------" << endl;
		cout << "보유코인 : " << m_Player.iCoin << endl;
		cout << "=====================================" << endl;
		cout << "1) 아이템 구매. 2) 메인화면 : ";
		cin >> iInput;

		if (iInput == 1)
		{
			cout << "구매할 아이템 번호 입력: ";
			cin >> i_Input;

			switch (i_Input)
			{
			case 1:
				if (m_Player.iCoin >= 300 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 1;

					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "멋진 검");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "공격력");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 30;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 300;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 300;
					cout << "구매 성공!" << endl;
				}
				else
				{
					cout << "구매 실패!" << endl;
				}
				break;
			case 2:
				if (m_Player.iCoin >= 500 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 2;
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "멋진 방패");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "방어력");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 20;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 500;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 500;
					cout << "구매 성공!" << endl;
				}
				else
				{
					cout << "구매 실패!" << endl;
				}
				break;
			case 3:
				if (m_Player.iCoin >= 1000 && m_PlayerInven_Have[0].iCount < 3)
				{
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iNum = 3;
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sName), "체력 회복_1회용");
					strcpy_s(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect, sizeof(m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].sItemEffect), "체력");
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iEffectNum = 100;
					m_PlayerInven_Have[m_PlayerInven_Have[0].iCount].iCoin = 1000;
					m_PlayerInven_Have[0].iCount++;

					m_Player.iCoin -= 1000;
					cout << "구매 성공!" << endl;
				}
				else
				{
					cout << "구매 실패!" << endl;
				}
				break;
			default:
				cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
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
			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
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
	cout << "[SYSTEM] 플레이어 프로필" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "이름 : " << m_Player.sName << "\t" << "성별 : " << m_Player.sGender << endl;
	cout << "레벨 : " << m_Player.iLv << "\t" << "경험치 : " << m_Player.iEx << endl;
	cout << "종족 : " << m_Player.sSpecies << "\t" << "직업 : " << m_Player.sJob << endl;
	cout << "체력 : " << m_Player.iCurrHp << "\t" << "공격력 : " << m_Player.iAttack << "\t" << "방어력 : " << m_Player.iDefense << endl;
	cout << "---------------------------------------------" << endl;
	cout << "보유코인 : " << m_Player.iCoin << endl;
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
//		cout << "[아이템 상점 2]" << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "1) 초급 상점. 2) 중급 상점. 3) 고급 상점. 4) 메인화면: ";
//		cin >> iInput;
//
//		switch (iInput)
//		{
//		case 1:
//			_Homework_Store("초급", 10, 10, 100);
//			break;
//		case 2:
//			_Homework_Store("중급", 20, 20, 200);
//			break;
//		case 3:
//			_Homework_Store("고급", 30, 30, 300);
//			break;
//		case 4:
//			return;
//			break;
//		default:
//			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
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
//		cout << "[" << _sName << " 아이템 상점 2]" << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "1번) " << _sName << " 무기   _" << _iCoin << " 원" << endl;
//		cout << "   - 공격력 " << _iAttack << " 증가 ! " << endl << endl;
//		cout << "2번) " << _sName << " 방어구 _" << _iCoin << " 원" << endl;
//		cout << "   - 방어력 " << _iDefense << " 증가 ! " << endl << endl;
//		cout << "-------------------------------------" << endl;
//		cout << "보유코인 : " << m_Player.iCoin << endl;
//		cout << "=====================================" << endl;
//		cout << "1) 아이템 구매. 2) 이전화면 : ";
//		cin >> iInput;
//
//		if (iInput == 1)
//		{
//			cout << "아이템 구매기능 추후 구현 예정" << endl;
//			system("pause");
//		}
//		else if (iInput == 2)
//		{
//			return;
//		}
//		else
//		{
//			cout << " [Error] 지원하지 않는 입력 값 입니다." << endl;
//			system("pause");
//		}
//	}
//}