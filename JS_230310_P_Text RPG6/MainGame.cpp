#include "pch.h"
#include "MainGame.h"
#include "HuntingGround.h"

/*CMainGame::CMainGame()
{
	m_Player = nullptr;
	m_Ground = nullptr;
}*/

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	this->m_Player = new CPlayer;
	dynamic_cast<CPlayer*>(m_Player)->Initialize();
	// p_Player = m_Player;

	this->m_Ground = new CHuntingGround;

	this->m_Store = new CStore;
	m_Store->Initialize();

	m_PlayerInven = new CInventory;
	m_PlayerInven->Initialize();
	m_PlayerInven->PlayerInfo_Set(m_Player);
}

void CMainGame::Update() const
{
	int iInput(0);
	bool bSelet(false);

	while (!bSelet)
	{
		cout << "Text RPG�� ���� ���� ȯ���մϴ�." << endl << endl;
		cout << "1) ���ӽ���. 2) �ҷ����� : ";
		cin >> iInput;
		
		switch (iInput)
		{
		case 1:
			dynamic_cast<CPlayer*>(m_Player)->Select_PlayerInfo();
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			bSelet = true;
			break;
		case 2:
			dynamic_cast<CPlayer*>(m_Player)->Load_PlayerInfo();
			bSelet = true;
			break;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
		system("cls");
	}
	iInput = 0;
	bSelet = false;

	while (!bSelet)
	{
		cout << "[����ȭ��]" << endl;
		cout << "---------------------------------------------------------------" << endl;
		cout << "1) ������. 2) ������ų. 3) array����ǰ. 4) vector����ǰ. 5) array����. 6) vector����  7) �����. 8) ����. : ";
		cin >> iInput;
		system("cls");

		switch (iInput)
		{
		case 1:
			m_Player->Output_Info();
			system("pause");
			break;
		case 2:
			dynamic_cast<CPlayer*>(m_Player)->Skill_Update();
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			break;
		case 3: 
			dynamic_cast<CPlayer*>(m_Player)->Inven_Update();
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			break;
		case 4:
			m_PlayerInven->Update();
			break;
		case 5:
			dynamic_cast<CPlayer*>(m_Player)->Store_Update();
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			break;
		case 6:
			m_Store->PlayerInfo_Set(m_Player);
			m_Store->PlayerInven_Set(m_PlayerInven);
			m_Store->Update();
			//dynamic_cast<CPlayer*>(m_Player)->Homework_Store_Update();
			//dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			break;
		case 7:
			m_Ground->PlayerInfo_Set(m_Player); 
			m_Ground->Update();
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			break;
		case 8:
			dynamic_cast<CPlayer*>(m_Player)->Save_PlayerInfo();
			bSelet = true;
			break;
		default:
			cout << " [Error] �������� �ʴ� �Է� �� �Դϴ�." << endl;
			system("pause");
			break;
		}
		system("cls");
	}
}

void CMainGame::Release()
{
	DELETE_MEMORY(this->m_Player);
	DELETE_MEMORY(this->m_Ground);
	DELETE_MEMORY(this->m_Store);
	DELETE_MEMORY(this->m_PlayerInven);
}